#ifndef IMAGEPROCESSINGWIDGET_H
#define IMAGEPROCESSINGWIDGET_H
#include <QWidget>
class QLabel;
namespace Ui {
class ImageProcessingWidget;
}

class ImageProcessingWidget : public QWidget {
	Q_OBJECT
    static constexpr const char* filters[] = {
        "png", "jpg"
    };

public:
    explicit ImageProcessingWidget(QWidget* parent = nullptr);
	~ImageProcessingWidget();
    void displayed(QLabel* label);
signals:
    /**
     * @brief request_processing is just the signals
     * request processing
     */
    void request_processing();
    void image_loaded(const QImage& image);

private:
    Ui::ImageProcessingWidget* ui;
    QImage image_handling;
    void process_raw_load();
};

#endif // IMAGEPROCESSINGWIDGET_H
