#ifndef MEDIAINFOWINDOW_H
#define MEDIAINFOWINDOW_H
#include "base/MediaPlayer.h"
#include <QMainWindow>

namespace Ui {
class MediaInfoWindow;
}

class MediaInfoWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MediaInfoWindow(QWidget* parent = nullptr);
	~MediaInfoWindow();

public slots:
	void filled_metainfo(const MediaInfo info);

private:
	Ui::MediaInfoWindow* ui;
};

#endif // MEDIAINFOWINDOW_H
