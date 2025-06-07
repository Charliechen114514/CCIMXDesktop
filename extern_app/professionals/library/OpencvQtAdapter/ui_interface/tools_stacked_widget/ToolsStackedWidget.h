#ifndef TOOLSSTACKEDWIDGET_H
#define TOOLSSTACKEDWIDGET_H
#include <QWidget>

namespace Ui {
class ToolsStackedWidget;
}

/**
 * @brief The ToolsStackedWidget class
 */
class ToolsStackedWidget : public QWidget {
	Q_OBJECT

public:
    /**
     * @brief ToolsStackedWidget
     * @param parent
     */
    explicit ToolsStackedWidget(QWidget* parent = nullptr);
	~ToolsStackedWidget();
    /**
     * @brief manage the init of the page initer
     */
    struct PagePackage {
        QString name; ///< toolbutton name
        QIcon icon; ///< toolbutton icon, can pass default icon
        QWidget* widget; ///< widget if button is pressed to switch show
    };
    /**
     * @brief add_switchable_page
     * @param package package for install
     * @see PagePackage
     */
    void add_switchable_page(const PagePackage& package);

private:
    Ui::ToolsStackedWidget* ui;
};

#endif // TOOLSSTACKEDWIDGET_H
