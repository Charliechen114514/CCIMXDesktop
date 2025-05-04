#ifndef PAGESETUPER_H
#define PAGESETUPER_H

/* page setuper helps setup the page quickly */
#include <QList>
class QStackedWidget;
class QWidget;
class DesktopMainWindow;
class ApplicationWrapper;
class AppWidget;
class DownDockWidget;

namespace PageSetuper
{

/* sessions required */
struct PageSetupSessionRequest{
    QString                 pixmap_addr{};
    QString                 app_name{};
    ApplicationWrapper*     app{nullptr};
};

static constexpr const unsigned int APP_ICON_SZ = 48;

/* shell make a page request */
QList<AppWidget*>   create_one_app_only_page_append(
    QStackedWidget* widget, DesktopMainWindow *mainWindow,
    const QList<PageSetupSessionRequest>& sessionRequest);

QList<AppWidget*>   create_real_app(DesktopMainWindow *mainWindow);


/* this create a page specified for user defined */
void                create_specified_page(
    QStackedWidget* widget, QWidget* paged_widget
);


void   add_to_dock(DownDockWidget* downdock, DesktopMainWindow *mainWindow, const QList<AppWidget*>& widgets);

};

#endif // PAGESETUPER_H
