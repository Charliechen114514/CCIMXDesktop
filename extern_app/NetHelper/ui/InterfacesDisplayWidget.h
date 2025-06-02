#ifndef INTERFACESDISPLAYWIDGET_H
#define INTERFACESDISPLAYWIDGET_H
class InterfacesQuery;
class QNetworkInterface;
#include <QWidget>

namespace Ui {
class InterfacesDisplayWidget;
}

/**
 * @brief The InterfacesDisplayWidget class
 */
class InterfacesDisplayWidget : public QWidget {
	Q_OBJECT

public:
	/**
	 * @brief creator
	 * @param parent
	 */
	explicit InterfacesDisplayWidget(QWidget* parent = nullptr);
	/**
	 * @brief display the target details network card
	 */
	void show_details();
	/**
	 * @brief show_lists the sum lists show
	 */
	void show_lists();
	~InterfacesDisplayWidget();
public slots:

private:
	Ui::InterfacesDisplayWidget* ui; ///< ui handle
	InterfacesQuery* query; ///< query instance
	/**
	 * @brief setup_memory
	 */
	void setup_memory();
	/**
	 * @brief install_interface_details install details to the table widgets
	 * @param interfaces for installs
	 */
	void install_interface_details(const QNetworkInterface& interfaces);
};

#endif // INTERFACESDISPLAYWIDGET_H
