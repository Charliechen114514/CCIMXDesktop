#ifndef TOPSIDEBARWIDGETCONFIGURES_H
#define TOPSIDEBARWIDGETCONFIGURES_H

#include <QWidget>

namespace Ui {
class TopSideBarWidgetConfigures;
}

class TopSideBarWidget;
class DesktopMainWindow;

/**
 * @brief Configuration widget for TopSideBarWidget.
 *
 * Provides user interface elements to configure the appearance and behavior
 * of the top sidebar widget in the application.
 */
class TopSideBarWidgetConfigures : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs a TopSideBarWidget configuration widget.
     * @param parent Pointer to the parent main window
     */
    explicit TopSideBarWidgetConfigures(DesktopMainWindow* parent = nullptr);
    
    /**
     * @brief Destroys the configuration widget.
     */
    ~TopSideBarWidgetConfigures();

private:
    Ui::TopSideBarWidgetConfigures* ui;  ///< UI components for the configuration widget
    TopSideBarWidget* toolsidebar;      ///< Reference to the top sidebar widget being configured
};

#endif // TOPSIDEBARWIDGETCONFIGURES_H