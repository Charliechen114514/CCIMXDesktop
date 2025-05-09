#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
class VideoPlayer;
class QMediaPlayer;
class QAudioOutput;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:

	void on_btn_open_clicked();

	void on_btn_play_clicked();

	void on_btn_stop_clicked();

private:
	static constexpr const unsigned short MAX_MISTCH = 80;
	Ui::MainWindow* ui;
	VideoPlayer* video_player { nullptr };
	QMediaPlayer* audio_player { nullptr };
	QAudioOutput* audio_output { nullptr };
};
#endif // MAINWINDOW_H
