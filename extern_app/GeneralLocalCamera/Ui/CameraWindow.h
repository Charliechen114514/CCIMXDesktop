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
	void fresh_cameralists();
	void redirect(const QString path);
	~CameraWindow();

private slots:
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
