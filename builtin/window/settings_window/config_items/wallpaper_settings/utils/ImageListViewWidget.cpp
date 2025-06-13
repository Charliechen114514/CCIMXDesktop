#include "ImageListViewWidget.h"
#include <QEvent>
#include <QFileInfo>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPixmap>
ImageListViewer::ImageListViewer(QWidget* parent)
    : QWidget(parent) {
    imageLayout = new QGridLayout(this);
    imageLayout->setSpacing(10);
    setLayout(imageLayout);
    listWidget = new QListWidget(this);
    imageLayout->addWidget(listWidget);
    connect(listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        emit imageClicked(item->text());
    });
}

void ImageListViewer::setImageLists(const QStringList& pixPaths) {
    listWidget->clear();
    listWidget->addItems(pixPaths);
}
