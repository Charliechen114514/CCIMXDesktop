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
	/**
	 * @brief The Error enum provides the situations
	 * and cases of error types
	 */
	enum class Error {
		CAMERA_UNEXSITED, ///< camera is not exsited
		CAMERA_UNOPENED, ///< camera is not opened
		CAMERA_UNBIND_DISPLAY, ///< camera is not bind to display
		CAMERA_MULTI_OPENED ///< camera is already opened
	};

	CameraCapture() = delete;
	Q_DISABLE_COPY(CameraCapture);

	/**
	 * @brief CameraCapture
	 * @param index requires a valid index of cameras
	 * @param parent
	 */
	explicit CameraCapture(const int index, QObject* parent);
	~CameraCapture();
	/**
	 * @brief bind_display_widget bind the widgets to display
	 * @param CameraDisplayWidget the widget to display
	 */
	inline void bind_display_widget(CameraDisplayWidget* widget) {
		this->widget = widget;
	}
	/**
	 * @brief set_capture_delay_time set the delay time of capturings
	 * @param gap_time how long then?
	 */
	inline void set_capture_delay_time(const int gap_time) {
		this->msleep_time = gap_time;
	}
	/**
	 * @brief isActivate marks the camera's activation
	 * @return true if the camera is activated
	 */
	bool isActivate() const;

	/**
	 * @brief start start the camera capture sessions
	 * @return true if the camera is started successfully
	 */
	bool start();
	/**
	 * @brief close close the camera capture sessions
	 * @return true if the camera is closed successfully
	 */
	bool close();

signals:
	/**
	 * @brief cameraOpened the signal indicating the camera is opened
	 * @param index the index of the camera
	 */
	void cameraOpened(int index);
	/**
	 * @brief cameraClosed the signal indicating the camera is closed
	 * @param index the index of the camera
	 */
	void cameraClosed(int index);

	/**
	 * @brief cameraError the signal indicating the error
	 * @param e the error type
	 */
	void errorOccur(CameraCapture::Error e);

private:
	/* internal_handle */
	cv::VideoCapture* videoCaptureHandle { nullptr }; ///< the camera handle
	int current_index { -1 }; ///< the current index of the camera

	/* display issue */
	CameraDisplayWidget* widget { nullptr }; ///< the display widget

	/* para issues */
	QMutex* capMutex; ///< mutex for the capture, for the async safe
	std::atomic_bool internal_running_state_holder { false }; ///< the running state holder
	int msleep_time { 10 };
	/**
	 * @brief capture_internal is the core sessions
	 */
	void capture_internal();
};

#endif // CAMERACAPTURE_H
