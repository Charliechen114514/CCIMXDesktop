#ifndef PAGEFACTORY_H
#define PAGEFACTORY_H
#include <QList>
class QWidget;
class AppCardWidget;
class DesktopMainWindow;
class AppWidget;
/**
 * @brief Page Factory produce pages for helping setup the pages :)
 */
class PageFactory {
public:
	/* build a homepage to the Desktop */

	/**
	 * @brief big front end to setup a home page
	 * @param mainWindow of the home page contains
	 * @return
	 */
	static QWidget* build_home_page(DesktopMainWindow* mainWindow);
	/* using in build a pesudo pages */

	/**
	 * @brief build a pesudo pages
	 * @param pixpath indicates the icon path
	 * @param how_many indicates how many pesudo apps are created
	 * @param mainWindow the main window
	 * @return the app widgets lists
	 * @note this will later be abolished until the finish release of the
	 * desktops
	 */
	static QList<AppWidget*> build_pesudo_page(
		const QString& pixpath, int how_many, DesktopMainWindow* mainWindow);

private:
	/**
	 * @brief actual netcards placings, rewrite in srccode level to deciding the init state of the cards places
	 * @param mainWindow the main window
	 * @param placed the widget that will be placed
	 * @return
	 */
	static QList<AppCardWidget*> place_appcards_in_empty_widgets(DesktopMainWindow* mainWindow, QWidget* placed);
};

#endif // PAGEFACTORY_H
