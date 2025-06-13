#ifndef IMAGELISTVIEWWIDGET_H
#define IMAGELISTVIEWWIDGET_H

#include <QWidget>

class QGridLayout;
class QListWidget;

/**
 * @brief The ImageListViewer class
 * A widget that displays a list of images in a grid layout.
 * 
 * Supports dynamic image list assignment and emits signals on image click.
 */
class ImageListViewer : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the ImageListViewer widget.
     * @param parent Optional parent QWidget.
     */
    explicit ImageListViewer(QWidget* parent = nullptr);

signals:
    /**
     * @brief Emitted when an image is clicked.
     * @param imagePath Path of the clicked image.
     */
    void imageClicked(const QString& imagePath);

public slots:
    /**
     * @brief Sets and displays a new list of images.
     * @param pixPaths List of image paths.
     */
    void setImageLists(const QStringList& pixPaths);

private:
    QGridLayout* imageLayout = nullptr; ///< Layout for image arrangement.
    QListWidget* listWidget;            ///< List widget to display images.
};

#endif // IMAGELISTVIEWWIDGET_H
