#include "CameraCapture.h"
#include "CameraDisplayWidget.h"
#include <QImage>
#include <QMutex>
#include <QThread>
#include <QTimer>
#include <opencv.hpp>
CameraCapture::
    CameraCapture(const int index, QObject* parent)
    : QObject(parent) {
    current_index = index;
    capMutex = new QMutex();
}

CameraCapture::~CameraCapture() {
	close();
	delete capMutex;
	/* release resources */
	delete videoCaptureHandle;
}

void CameraCapture::bind_display_widget(CameraDisplayWidget* widget) {
	this->widget = widget;
}

void CameraCapture::set_capture_delay_time(const int gap_time) {
	this->msleep_time = gap_time;
}

bool CameraCapture::isActivate() const {
	return videoCaptureHandle && videoCaptureHandle->isOpened();
}

bool CameraCapture::start() {

	if (internal_running_state_holder) {
		emit errorOccur(Error::CAMERA_UNBIND_DISPLAY);
		return false;
	}

	/* cameras are supposed to make a display */
	if (!widget) {
		emit errorOccur(Error::CAMERA_UNBIND_DISPLAY);
		return false;
	}

	/* guard the process */
	capMutex->lock();
	if (!videoCaptureHandle) {
		videoCaptureHandle = new cv::VideoCapture(current_index);
	} else {
		videoCaptureHandle->open(current_index);
	}
	capMutex->unlock();
	/* unguard this */

	if (!videoCaptureHandle->isOpened()) {
		/* thus the camera is invalid */
		emit errorOccur(Error::CAMERA_UNEXSITED);
		return false;
	}

	/* camera is ready, thus creating thread is available */
	internal_running_state_holder = true;
	QTimer::singleShot(0, this, &CameraCapture::capture_internal);

	emit cameraOpened(current_index);
	return true;
}

bool CameraCapture::close() {
	if (!videoCaptureHandle) /* camera is not existed yet */
	{
		emit errorOccur(Error::CAMERA_UNEXSITED);
		return false;
	}

	internal_running_state_holder = false;
	/* --------- Locked -------------- */
	capMutex->lock();
	if (videoCaptureHandle->isOpened()) {
		videoCaptureHandle->release();
	}
	capMutex->unlock();
	/* --------- UnLocked ------------ */
	emit cameraClosed(current_index);
	return true;
}

/* timer based, as the capture body belongings to the MainWindow */
/* Thus, using timer based can make the invoke belongs to the event loop */
/* yet the quit can be available */
void CameraCapture::capture_internal() {
	cv::Mat frame;
	if (!internal_running_state_holder)
		return;

	/* Session I: fetch the frame */
	{
		QMutexLocker locker(capMutex);
		/* maybe we just short switch */
		if (!videoCaptureHandle->isOpened()) {
			QTimer::singleShot(msleep_time, this, &CameraCapture::capture_internal);
			return;
		}
		videoCaptureHandle->read(frame);
	}

	qDebug() << "Check frame";
	/* Session II: See if the frame empty */
	if (frame.empty()) {
		/* thus we fetch nothing */
		QTimer::singleShot(msleep_time, this, &CameraCapture::capture_internal);
		return;
	}

	qDebug() << "Check display";
	/* see if we have widget to display */
	if (!widget) {
		/* no, then sleep wait */
		QTimer::singleShot(msleep_time, this, &CameraCapture::capture_internal);
		return;
	}

	qDebug() << "make display";
	cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
	QImage img(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
	widget->setCurrentFrame(img);
	qDebug() << internal_running_state_holder;
	if (!internal_running_state_holder)
		return;
	QTimer::singleShot(msleep_time, this, &CameraCapture::capture_internal);
}
