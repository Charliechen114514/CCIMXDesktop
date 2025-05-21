#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>

namespace Ui {
class HomePage;
}

/* Home Pages */
class HomePage : public QWidget {
	Q_OBJECT

public:
	explicit HomePage(QWidget* parent = nullptr);

	/**
	 * @brief expected_appcards_widgets
	 * @return appcards holding widgets, iterate this for all app cards
	 */
	QWidget* expected_appcards_widgets() const;

	~HomePage();

private:
	Ui::HomePage* ui;
};

#endif // HOMEPAGE_H
