#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include <QWidget>

namespace Ui {
class HomePage;
}
class ClockWidget;
class DigitalTimeWidget;
class DesktopMainWindow;
class CardStackWidget;
class HomeCardManager;

/**
 * @brief The HomePage class exactly, home page :)
 */
class HomePage : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief Construct a new Home Page object
     *
     * @param parent
	 */
    explicit HomePage(DesktopMainWindow* parent = nullptr);

	/**
	 * @brief expected_appcards_widgets
	 * @return appcards holding widgets, iterate this for all app cards
	 */
	QWidget* expected_appcards_widgets() const;

    /**
     * @brief clock_widget
     * @return
     */
    ClockWidget* clock_widget() const;
    /**
     * @brief digital_timeWidget fetch the digital time widgets
     * @return
     */
    DigitalTimeWidget* digital_timeWidget() const;

    /**
     * @brief homeCardManager return the managers
     * @return
     */
    HomeCardManager* homeCardManager() const;

	/**
	 * @brief Destroy the Home Page object
     *
	 */
	~HomePage();

private:
    Ui::HomePage* ui; ///< ui handle
    std::shared_ptr<HomeCardManager> _homeCardManager; ///< card manager
};

#endif // HOMEPAGE_H
