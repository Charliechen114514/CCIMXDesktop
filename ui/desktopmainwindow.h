#ifndef DESKTOPMAINWINDOW_H
#define DESKTOPMAINWINDOW_H

#include <QMainWindow>
#include "ui/appwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class DesktopMainWindow;
}
QT_END_NAMESPACE
/* App layouts */
class QGridLayout;
class QLabel;
class DesktopToast;
class ApplicationWrapper;
class QTimer;
class QStackedWidget;

class AppCardWidget;

class DesktopMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    friend class PageFactory;
    struct WallPaperGroup{
        QWidget*                shoule_be_lower;
        /* wall paper label is using in display the current */
        QLabel*                 wallpaperLabel{nullptr};
        /* bufferpaperLabel helps the animations */
        QLabel*                 bufferpaperLabel{nullptr};
        QTimer*                 invoke_switch_timer;
    };

    DesktopMainWindow(QWidget *parent = nullptr);
    /* for mainWindow, this is the global messages */
    void showToast(const QString& message);
    inline DesktopToast*   desktop_toast() const {return toast;}
    void to_next_page();
    void to_prev_page();
    ~DesktopMainWindow();
    void invoke_switch_bgpage();
    void inline install_remote_appwrapper(ApplicationWrapper* wrapper){app_wrapper << wrapper;}
    void handle_app_status(AppWidget::AppStatus status);
    QStackedWidget* stackedWidget() const;
    /* post inits do the job of emit signals for apps */
    void post_inits();

signals:
    /* To async init the app cards, signals will be sent */
    void deptach_app_cards_init();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::DesktopMainWindow *ui;
    DesktopToast*               toast;
    QList<ApplicationWrapper*>  app_wrapper;
    QList<AppWidget*>           app_widgets;
    void                        post_setupui();
    void                        setup_bg_image();
    void                        setup_apps();
    void                        slideToPage(int newIndex, bool toLeft);

    /* wall paper struct */
    WallPaperGroup wallPaperGroup;
    /* using in the image lists */
    QStringList                 image_lists;

    /* using in detect the mouse pos, and shell be used in <- -> */
    struct {
        QPoint                  press;
        QPoint                  release;
    }records;

    static constexpr const unsigned int switch_bg_time = 20000;

    /* Appcards */
    QList<AppCardWidget*>       app_cards;
    void                        invoke_appcards_init();
};
#endif // DESKTOPMAINWINDOW_H
