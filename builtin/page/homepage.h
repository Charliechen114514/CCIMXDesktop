#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui {
class HomePage;
}

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
	explicit HomePage(QWidget* parent = nullptr);

	/**
	 * @brief expected_appcards_widgets
	 * @return appcards holding widgets, iterate this for all app cards
	 */
	QWidget* expected_appcards_widgets() const;
	/**
	 * @brief Destroy the Home Page object
	 * 
	 */
	~HomePage();

private:
	Ui::HomePage* ui;
};

#endif // HOMEPAGE_H
