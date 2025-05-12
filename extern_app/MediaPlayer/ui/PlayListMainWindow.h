#ifndef PLAYLISTMAINWINDOW_H
#define PLAYLISTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PlayListMainWindow;
}

class PlayListMainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit PlayListMainWindow(QWidget* parent = nullptr);
	void flip_edit_mode();
	~PlayListMainWindow();

signals:
	/*
	 * inform to flush the media list
	 * this is only when press the items
	 */
	void refresh_media_list();
	void play_media(const QString& media_src);
	void delete_media(const QString& media_src);
public slots:
	void from_media_list(const QStringList& l);
private slots:
	void process_select_delete();
	void process_item_click();

private:
	Ui::PlayListMainWindow* ui;
	bool in_edit_mode { false };
};

#endif // PLAYLISTMAINWINDOW_H
