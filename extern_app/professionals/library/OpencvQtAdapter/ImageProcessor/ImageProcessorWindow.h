#ifndef IMAGEPROCESSORWINDOW_H
#define IMAGEPROCESSORWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class ImageProcessorWindow;
}
QT_END_NAMESPACE

class ImageProcessorWindow : public QMainWindow {
	Q_OBJECT

public:
    ImageProcessorWindow(QWidget* parent = nullptr);
	~ImageProcessorWindow();

private:
    Ui::ImageProcessorWindow* ui;
    void setup_panel();
};
#endif // IMAGEPROCESSORWINDOW_H
