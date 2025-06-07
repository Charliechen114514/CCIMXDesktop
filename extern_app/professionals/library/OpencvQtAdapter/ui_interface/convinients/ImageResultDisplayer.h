#ifndef IMAGERESULTDISPLAYER_H
#define IMAGERESULTDISPLAYER_H

#include <QWidget>
class ImageLabel;
class QLabel;
namespace Ui {
class ImageResultDisplayer;
}

class ImageResultDisplayer : public QWidget {
	Q_OBJECT

public:
    explicit ImageResultDisplayer(QWidget* parent = nullptr);
	~ImageResultDisplayer();
    ImageLabel* rawImageLabel();
    ImageLabel* processedImageLabel();
public slots:
    void setRawImage(const QImage& image);
    void setProcessedImage(const QImage& image);

private:
    Ui::ImageResultDisplayer* ui;
};

#endif // IMAGERESULTDISPLAYER_H
