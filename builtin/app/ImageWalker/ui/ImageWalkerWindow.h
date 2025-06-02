#ifndef IMAGEWALKERWINDOW_H
#define IMAGEWALKERWINDOW_H
#include "ImageBrowser.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ImageWalkerWindow;
}
QT_END_NAMESPACE

/**
 * @brief MainWindow of this applications
 * 
 */
class ImageWalkerWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief ImageWalkerWindow create window
	 * @param parent
	 */
	ImageWalkerWindow(QWidget* parent = nullptr);
	~ImageWalkerWindow();

private:
	void handle_error(const ImageBrowser::ErrorType e);
	Ui::ImageWalkerWindow* ui; ///< ui handle

	bool fileview_visiable_flag { true }; ///< is fileview avaiable?
	void init_connections(); ///< yeah, setup internal connections here
};
#endif // IMAGEWALKERWINDOW_H
