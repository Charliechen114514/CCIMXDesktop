#ifndef DRAWERWINDOW_H
#define DRAWERWINDOW_H

#include <QMainWindow>
class SimpleDrawingScene;
QT_BEGIN_NAMESPACE
namespace Ui {
class DrawerWindow;
}
QT_END_NAMESPACE
class SaveWindow;
class DrawerWindow : public QMainWindow {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Drawer Window object
	 * 
	 * @param parent 
	 */
	DrawerWindow(QWidget* parent = nullptr);
	/**
	 * @brief scene_instance fetch scene instance
	 * @return scene instance
	 */
	SimpleDrawingScene* scene_instance();
	~DrawerWindow();

private:
	/**
	 * @brief setup connections
	 */
	void init_connections();
	/**
	 * @brief setup acceptable figures for drawings
	 */
	void setup_enable_drawings();
	/**
	 * @brief setup_settings setup settings issue
	 */
	void setup_settings();
	SaveWindow* saveWindow;
	Ui::DrawerWindow* ui;
};
#endif // DRAWERWINDOW_H
