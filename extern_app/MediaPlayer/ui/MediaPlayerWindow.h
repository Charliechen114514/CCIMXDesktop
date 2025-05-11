#ifndef MEDIAPLAYERWINDOW_H
#define MEDIAPLAYERWINDOW_H

#include <QMainWindow>

class MediaPlayer;
class MediaInfoWindow;
QT_BEGIN_NAMESPACE
namespace Ui {
class MediaPlayerWindow;
}
QT_END_NAMESPACE

class MediaPlayerWindow : public QMainWindow {
	Q_OBJECT
public:
	friend class MediaPlayerWindowHelper;
	MediaPlayerWindow(QWidget* parent = nullptr);
	/* open media from dialog */
	void open_media();
	void toggle_playing_status();
	~MediaPlayerWindow();

private slots:
	/* handle the possible image */
	void handle_display_src(bool available, const QImage& image);
	void handle_imageDisplay(const QImage& image);
	/* if user press the sliders */
	void handle_new_durations(qint64 duration);
	/* handle the position chandged */
	void handle_position_changed(qint64 position);
	/* handle the media ends sessions */
	void handle_media_end();

	/* slider postion change handling */
	void handle_slider_position_changed(int position);
	void handle_slider_pressed();
	void handle_slider_released();

private:
	Ui::MediaPlayerWindow* ui;
	/* media player */
	MediaPlayer* mediaPlayer { nullptr };
	/* info Window */
	MediaInfoWindow* infoWindow { nullptr };

	bool manual_sliding { false };
	bool is_playing { false };
	bool video_available { false };
	void init_memories();
	void init_core_connections();
	void init_ui_connections();
	void init_connections();
	/* if the video is unavailable, thus we think it is music */
	void post_do_video_unavailable();
	void post_init_ui();
	void process_playing_status();
};
#endif // MEDIAPLAYERWINDOW_H
