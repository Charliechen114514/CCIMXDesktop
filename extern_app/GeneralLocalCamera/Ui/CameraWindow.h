#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
class CameraCapture;
class PhotoSaver;
class DesktopToast;
QT_BEGIN_NAMESPACE
namespace Ui {
class CameraWindow;
}
QT_END_NAMESPACE

class CameraWindow : public QMainWindow {
	Q_OBJECT

public:
	CameraWindow(QWidget* parent = nullptr);

	/**
	 * @brief fresh_cameralists refresh the camera lists
	 * @note this will change the current selected camera, so
	 * make sense when camera list is freshed
	 */
	void fresh_cameralists();
	/**
	 * @brief redirect to the save path
	 * @param path the path to save
	 */
	void redirect(const QString path);
	~CameraWindow();

private slots:
	/**
	 * @brief on_btn_oppose_camera_clicked start/stop the camera sessions
	 */
	void on_btn_oppose_camera_clicked();

private:
	void setup_internal();
	void select(int index);
	void process_oppose_state(bool prev_opened);
	void capture_photo_once();
	Ui::CameraWindow* ui;
	CameraCapture* camera_capture;
	DesktopToast* toast;
	QString cached_path; /* cached saving dirent */
};
#endif // CAMERAWINDOW_H
