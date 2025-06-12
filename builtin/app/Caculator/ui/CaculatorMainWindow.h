#ifndef CACULATORMAINWINDOW_H
#define CACULATORMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class CaculatorMainWindow;
}
QT_END_NAMESPACE

/**
 * @brief MainWindow
 * 
 */
class CaculatorMainWindow : public QMainWindow {
	Q_OBJECT

public:
    /**
     * @brief Construct a new Caculator Main Window object
     * 
     * @param parent 
     */
    CaculatorMainWindow(QWidget* parent = nullptr);
	~CaculatorMainWindow();

protected:
    /**
     * @brief handle keypress sessions
     * 
     * @param event 
     */
    void keyPressEvent(QKeyEvent* event);

private:
    Ui::CaculatorMainWindow* ui; ///< ui handle
};
#endif // CACULATORMAINWINDOW_H
