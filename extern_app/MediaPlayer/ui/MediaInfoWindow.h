#ifndef MEDIAINFOWINDOW_H
#define MEDIAINFOWINDOW_H
#include "base/MediaPlayer.h"
#include <QMainWindow>

namespace Ui {
class MediaInfoWindow;
}

/**
 * @brief The MediaInfoWindow class provides the media info window
 * for display
 * @note this is the meta data of the media
 */
class MediaInfoWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Media Info Window object
	 * 
	 * @param parent 
	 */
	explicit MediaInfoWindow(QWidget* parent = nullptr);
	~MediaInfoWindow();

public slots:
	/**
	 * @brief filled_metainfo fill the media info
	 * @param info the media info to fill
	 */
	void filled_metainfo(const MediaInfo info);

private:
	Ui::MediaInfoWindow* ui;
};

#endif // MEDIAINFOWINDOW_H
