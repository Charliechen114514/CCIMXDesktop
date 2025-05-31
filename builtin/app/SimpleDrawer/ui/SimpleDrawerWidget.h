#ifndef SIMPLEDRAWERWIDGET_H
#define SIMPLEDRAWERWIDGET_H

#include <QWidget>

class SimpleDrawingScene;
namespace Ui {
class SimpleDrawerWidget;
}

class SimpleDrawerWidget : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Simple Drawer Widget object
	 * 
	 * @param parent 
	 */
	explicit SimpleDrawerWidget(QWidget* parent = nullptr);
	~SimpleDrawerWidget();
	/**
	 * @brief scene_instance fetch scene instance
	 * @return scene instance
	 */
	SimpleDrawingScene* scene_instance() { return scene; }

private:
	Ui::SimpleDrawerWidget* ui;
	SimpleDrawingScene* scene;
};

#endif // SIMPLEDRAWERWIDGET_H
