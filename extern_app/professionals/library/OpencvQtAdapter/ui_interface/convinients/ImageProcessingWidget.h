#ifndef IMAGEPROCESSINGWIDGET_H
#define IMAGEPROCESSINGWIDGET_H
#include <QWidget>
class QLabel;
namespace Ui {
class ImageProcessingWidget;
}

/**
 * @brief ImageProcessingWidget
 * 
 */
class ImageProcessingWidget : public QWidget {
	Q_OBJECT
    /**
     * @brief filters means the filter accepts
     */
    static constexpr const char* filters[] = {
        "png", "jpg"
    };

public:
    /**
     * @brief ImageProcessingWidget
     * @param parent
     */
    explicit ImageProcessingWidget(QWidget* parent = nullptr);
	~ImageProcessingWidget();
    /**
     * @brief displayed will set the pixmap directly
     * @param label
     */
    void displayed(QLabel* label);
    /**
     * @brief image fetch the image handling
     * @return
     */
    QImage image() const noexcept { return image_handling; }
    /**
     * @brief process_direct_load load the sessions
     * @param path
     */
    void process_direct_load(const QString& path);
    /**
     * @brief process_raw_load opens the filedialog
     * and will actually turns to process_raw_load(const QString& path)
     */
    void process_raw_load();
    /**
     * @brief process_raw_load process actuall load
     * @param path
     */
    void process_raw_load(const QString& path);
signals:
    /**
     * @brief request_processing is just the signals
     * request processing
     */
    void request_processing();
    /**
     * @brief image load signals and carry the image for loading
     * 
     * @param image 
     */
    void image_loaded(const QImage& image);

private:
    Ui::ImageProcessingWidget* ui;
    QImage image_handling;
};

#endif // IMAGEPROCESSINGWIDGET_H
