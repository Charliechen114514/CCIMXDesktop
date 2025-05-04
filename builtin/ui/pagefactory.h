#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H
#include <QList>
class QWidget;
class AppCardWidget;
class DesktopMainWindow;
class AppWidget;
/*
 * Page Factory produce pages for helping setup the pages :)
 */
class PageFactory
{
public:
    /* build a homepage to the Desktop */
    static QWidget* build_home_page(DesktopMainWindow* mainWindow);
    /* is using in build app pages */
    static QList<AppWidget*> build_app_page_1();
    /* using in build a pesudo pages */
    static QList<AppWidget*> build_pesudo_page(
        const QString& pixpath, int how_many, DesktopMainWindow* mainWindow);
private:
    /* app cards setups, invoke only in setups*/
    static QList<AppCardWidget*> place_appcards_in_empty_widgets(DesktopMainWindow *mainWindow, QWidget* placed);
};

#endif // PAGEFACTORY_H
