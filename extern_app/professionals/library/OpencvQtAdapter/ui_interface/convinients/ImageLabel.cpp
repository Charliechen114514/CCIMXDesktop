#include "ImageLabel.h"
#include <QPixmap>
#include <qpainter.h>

ImageLabel::ImageLabel(QWidget* parent)
    : QLabel(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setScaledContents(false);
}

void ImageLabel::setImage(const QImage& image) {
    currentImage = image;
    update();
}
void ImageLabel::paintEvent(QPaintEvent* event) {
    if (currentImage.isNull()) {
        QLabel::paintEvent(event);
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QSize size;
    size.setWidth(this->size().width() * 0.95);
    size.setHeight(this->size().height() * 0.95);
    QPixmap pix = QPixmap::fromImage(
        currentImage.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QPoint center = rect().center() - pix.rect().center();
    painter.drawPixmap(center, pix);
}

void ImageLabel::resizeEvent(QResizeEvent* event) {
    QLabel::resizeEvent(event);
    update();
}
