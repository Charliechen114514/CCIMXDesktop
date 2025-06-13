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

namespace PageSetuper {

/**
 * @brief MAX_WIDTH: telling the maximum app numbers in a row of the page
 */
static constexpr int MAX_WIDTH = 4;
/**
 * @brief MAX_HEIGHT: telling the maximum app numbers in a column of the page
 */
static constexpr int MAX_HEIGHT = 4;
/**
 * @brief   This is a wrapper class for page setup basic informations,
 *          it is a simple interface of creating one page with
 *          bunchs of applications
 */
struct PageSetupSessionRequest {
	QString pixmap_addr {}; ///< external pixmap src addr
	QString app_name {}; ///< app name that will be displayed in desktop
	ApplicationWrapper* app { nullptr }; ///< app handler
};

static constexpr const unsigned int APP_ICON_SZ = 48;

/**
 * @brief This functions create pure app pages, which is a relatively
 * low level functions, currently,
 * @see create_real_app is the higher level to
 * create specified level applications
 * @param mainWindow: the MainWindow waiting for placing
 * @param sessionRequest
 * @param wrappers appwrapper for the bind
 * @param pageName indicate the page
 * @return the ui handles of the
 */
QList<AppWidget*> create_one_app_only_page_append(
    DesktopMainWindow* mainWindow,
    const QList<PageSetupSessionRequest>& sessionRequest,
    const QString& pageName);

/**
 * @brief create_real_app is the main function to create the real applications
 * @param mainWindow: the window apps are created
 * @return
 */
QList<AppWidget*> create_real_app(DesktopMainWindow* mainWindow);

/**
 * @brief create_builtin_apps creates the must build app, which shell create a single pages
 * @param mainWindow: the window apps created
 * @return
 */
QList<AppWidget*> create_builtin_apps(DesktopMainWindow* mainWindow);

/**
 * @brief create_internal_apps creates the internal apps like Settings, which do not launch apps
 * @param mainWindow the window apps created
 * @return
 */
QList<AppWidget*> create_internal_apps(DesktopMainWindow* mainWindow);

/**
 * @brief create_specified_page is the helper function to add a page
 * into the specified stacked widget, all the QWidget details should be premapped
 * @param widget: the stacked widget that will be added
 * @param paged_widget: the page that will be added
 */
void create_specified_page(
    QStackedWidget* widget, QWidget* paged_widget);

/**
 * @brief add_to_dock is the helper function to add widgets into the dock widgets
 * @param mainWindow the main window that will be added
 * @param widgets the widgets that will be added
 */
void add_to_dock(DesktopMainWindow* mainWindow, const QList<AppWidget*>& widgets);

/**
 * @brief setup a pesudo page, now in debug usage
 * 
 * @param pixpath the pix
 * @param how_many how many
 * @param mainWindow binding windows
 * @return QList<AppWidget*> with widgets
 */
QList<AppWidget*> build_pesudo_page(
    const QString& pixpath, int how_many, DesktopMainWindow* mainWindow);
};

#endif // PAGESETUPER_H
