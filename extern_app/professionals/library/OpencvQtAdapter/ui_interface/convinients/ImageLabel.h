#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#pragma once

#include <QImage>
#include <QLabel>

/**
 * @brief Override of the default QLabel
 *
 */
class ImageLabel : public QLabel {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Image Label object
     *
     * @param parent
	 */
	explicit ImageLabel(QWidget* parent = nullptr);
	/**
	 * @brief Set the Image object
     *
     * @param image
	 */
	void setImage(const QImage& image);

protected:
	/**
	 * @brief handle the resizeEvent by ourselves
     *
     * @param event
	 */
	void resizeEvent(QResizeEvent* event) override;
    /**
     * @brief handle the paintEvent by ourselves
     * @param event
     */
    void paintEvent(QPaintEvent* event) override;

private:
	QImage currentImage;
};

#endif // IMAGELABEL_H
