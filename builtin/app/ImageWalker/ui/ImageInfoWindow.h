#ifndef IMAGEINFOWINDOW_H
#define IMAGEINFOWINDOW_H

#include <QMainWindow>

namespace Ui {
class ImageInfoWindow;
}

/**
 * @brief ImageInfo Window class holds the display of image info
 * 
 */
class ImageInfoWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief ImageInfoWindow
	 * @param parent
	 */
	explicit ImageInfoWindow(QWidget* parent = nullptr);
	
	void set_image_path(const QString& path); ///< set the analysis image path
	QString get_image_path() { return image_path; } ///< get the analysis image path
	~ImageInfoWindow();

private:
	QString image_path {}; ///< cached image path
	Ui::ImageInfoWindow* ui; ///< ui handle
	ImageInfoWindow* infoWindow; ///< info window;
};

#endif // IMAGEINFOWINDOW_H
