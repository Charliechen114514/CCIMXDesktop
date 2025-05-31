#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include <QImage>
#include <QObject>
#include <QtClassHelperMacros>
#include <atomic>

class CameraDisplayWidget;
class QThread;
class QMutex;

namespace cv {
class VideoCapture;
}

/**
 * @brief The CameraCapture class handles camera video capturing.
 */
class CameraCapture : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Error enum lists possible camera error cases.
     */
    enum class Error {
        CAMERA_UNEXISTED,       ///< Camera does not exist
        CAMERA_UNOPENED,        ///< Camera not opened
        CAMERA_UNBIND_DISPLAY,  ///< Camera not bound to display widget
        CAMERA_MULTI_OPENED     ///< Camera already opened
    };

    CameraCapture() = delete;

    /**
     * @brief Q_DISABLE_COPY disables copy constructor and assignment operator.
     */
    Q_DISABLE_COPY(CameraCapture);

    /**
     * @brief Constructor with camera index.
     * @param index Valid index of the camera.
     * @param parent Optional QObject parent.
     */
    explicit CameraCapture(const int index, QObject* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~CameraCapture();

    /**
     * @brief Bind a display widget for camera output.
     * @param widget Pointer to CameraDisplayWidget.
     */
    inline void bind_display_widget(CameraDisplayWidget* widget) {
        this->widget = widget;
    }

    /**
     * @brief Set capture delay time in milliseconds.
     * @param gap_time Delay time in ms.
     */
    inline void set_capture_delay_time(const int gap_time) {
        this->msleep_time = gap_time;
    }

    /**
     * @brief Check if the camera is active.
     * @return True if active.
     */
    bool isActivate() const;

    /**
     * @brief Start the camera capture session.
     * @return True if started successfully.
     */
    bool start();

    /**
     * @brief Close the camera capture session.
     * @return True if closed successfully.
     */
    bool close();

signals:
    /**
     * @brief Signal emitted when camera is opened.
     * @param index Camera index.
     */
    void cameraOpened(int index);

    /**
     * @brief Signal emitted when camera is closed.
     * @param index Camera index.
     */
    void cameraClosed(int index);

    /**
     * @brief Signal emitted when an error occurs.
     * @param e Error type.
     */
    void errorOccur(CameraCapture::Error e);

private:
    cv::VideoCapture* videoCaptureHandle { nullptr }; ///< The camera handle
    int current_index { -1 }; ///< The current camera index

    CameraDisplayWidget* widget { nullptr }; ///< The display widget

    QMutex* capMutex; ///< Mutex for capture thread safety
    std::atomic_bool internal_running_state_holder { false }; ///< Running state flag
    int msleep_time { 10 }; ///< Capture delay time in milliseconds

    /**
     * @brief Internal capture processing function.
     */
    void capture_internal();
};

#endif // CAMERACAPTURE_H
