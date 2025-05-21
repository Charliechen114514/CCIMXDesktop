#ifndef CAMERADISPLAYWIDGET_H
#define CAMERADISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class CameraDisplayWidget;
}

class CameraDisplayWidget : public QWidget {
	Q_OBJECT

public:
	explicit CameraDisplayWidget(QWidget* parent = nullptr);

	/**
	 * @brief setCurrentFrame set the current frame
	 * @param image the image to set
	 */
	void setCurrentFrame(const QImage& image);

	/**
	 * @brief setCurrentFrame set the current frame
	 * @param image the image to set
	 */
	QPixmap current_captures() const;
	~CameraDisplayWidget();

private:
	Ui::CameraDisplayWidget* ui;
};

#endif // CAMERADISPLAYWIDGET_H
