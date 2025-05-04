#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H
#include <QImage>
#include <QObject>
#include <QtClassHelperMacros>
class CameraDisplayWidget;
class QThread;
class QMutex;
namespace cv {
class VideoCapture;
};

class CameraCapture : public QObject {
	Q_OBJECT
public:
	enum class Error {
		CAMERA_UNEXSITED, /* camera is not exsited */
		CAMERA_UNOPENED, /* camera is not opened */
		CAMERA_UNBIND_DISPLAY, /* no widgets bind */
		CAMERA_MULTI_OPENED /* duplicate open */
	};

	CameraCapture() = delete;
	Q_DISABLE_COPY(CameraCapture);

	explicit CameraCapture(const int index, QObject* parent);
	~CameraCapture();
	void bind_display_widget(CameraDisplayWidget* widget);
	void set_capture_delay_time(const int gap_time);
	bool isActivate() const;
	bool start();
	bool close();
	/* signals */
signals:
	/* camera index */
	void cameraOpened(int index);
	void cameraClosed(int index);
	/* the signal indicating errors */
	void errorOccur(CameraCapture::Error e);

private:
	/* internal_handle */
	cv::VideoCapture* videoCaptureHandle { nullptr };
	int current_index { -1 };

	/* display issue */
	CameraDisplayWidget* widget { nullptr };

	/* para issues */
	QMutex* capMutex;
	std::atomic_bool internal_running_state_holder { false };
	int msleep_time { 10 };
	void capture_internal();
};

#endif // CAMERACAPTURE_H
