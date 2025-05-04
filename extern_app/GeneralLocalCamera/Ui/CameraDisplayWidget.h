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
	void setCurrentFrame(const QImage& image);
	QPixmap current_captures() const;
	~CameraDisplayWidget();

private:
	Ui::CameraDisplayWidget* ui;
};

#endif // CAMERADISPLAYWIDGET_H
