#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/* As Qt6 Support QMultiMeida, make things simple */
#include <QCamera>
#include <QMainWindow>
#include <QMediaCaptureSession>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QImageCapture;
class QVideoWidget;
class DesktopToast;

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	void fresh_available_camera_once();
	~MainWindow();

private slots:
	void on_btn_oppose_camera_clicked();

	void on_btn_exit_clicked();

	void on_btn_refresh_clicked();

	void on_camera_list_selector_textActivated(const QString& arg1);

	void on_btn_capture_once_clicked();

	void on_btn_redirect_clicked();

private:
	Ui::MainWindow* ui;
	std::unique_ptr<QCamera> camera;
	QMediaCaptureSession captureSession;
	/* bind to the mainWindow */
	QVideoWidget* videoWidget;
	/* image capture */
	QImageCapture* image_capture;
	/* desktop toast */
	DesktopToast* toast;
	/* functions behave as default behaviors */
	void process_post_refresh(const QList<QCameraDevice>& cameras);
	void process_once_switch(const bool current_state);
	void setup_window();
	void redirect_path();
	void connect_connections();
	QString cached_path {};
};
#endif // MAINWINDOW_H
