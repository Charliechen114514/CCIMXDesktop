#ifndef TOPSIDEBARWIDGET_H
#define TOPSIDEBARWIDGET_H

#include <QWidget>
class IconEvent;
class StatusBarIconWidget;
class NetStatusStatusBarIconWidget;
class DesktopMainWindow;
namespace Ui {
class TopSideBarWidget;
}

/**
 * @brief Top sidebar container widget.
 * 
 * Holds and manages status bar icon widgets in the top sidebar area.
 */
class TopSideBarWidget : public QWidget {
	Q_OBJECT

public:
    /**
     * @brief Constructs the top sidebar widget.
     * @param parent Parent widget (optional)
     */
    explicit TopSideBarWidget(QWidget* parent = nullptr);
    
    /**
     * @brief Destroys the top sidebar widget.
     */
    ~TopSideBarWidget();
    
    /**
     * @brief Installs the main window reference for event handling.
     * @param mainWindow Pointer to the main window
     */
    void installHookedWindow(DesktopMainWindow* mainWindow);
    
    /**
     * @brief Append position specifier.
     */
    enum class AcceptPosition {
        LeftSide,  ///< Left side of the sidebar
        RightSide  ///< Right side of the sidebar
    };
    
    /**
     * @brief Appends a status bar widget to the sidebar.
     * @param src Widget to append
     * @param position Target side (left/right)
     */
    void append_to_toolside(StatusBarIconWidget* src, AcceptPosition position);

    /**
     * @brief Processes icon events.
     * @param events Event to handle
     */
    void handle_possibleEvent(IconEvent* events);

    /**
     * @brief Queries status icon widget by name.
     * @param name Name of the widget to find
     * @return Pointer to widget if found, nullptr otherwise
     */
    StatusBarIconWidget* queryFromName(const QString& name);

    /**
     * @brief Sets the sidebar height.
     * @param height New height value
     */
    void setHeight(const int height);

    /**
     * @brief Gets the minimum allowed height.
     * @return Minimum height value
     */
    int height_min() const;
    
    /**
     * @brief Gets the maximum allowed height.
     * @return Maximum height value
     */
    int height_max() const;
    
    /**
     * @brief Gets the current height.
     * @return Current height value
     */
    int height() const {
        return selfHeight;
    }

private:
    Ui::TopSideBarWidget* ui;
    
    /// Initializes left-hand side widgets
    void initLeftHandside();
    
    /// Initializes right-hand side widgets
    void initRightHandside();
    
    int selfHeight;  ///< Current sidebar height
    QList<StatusBarIconWidget*> iconsWidgets;  ///< List of managed icon widgets
    DesktopMainWindow* mainWindow;  ///< Reference to main application window
};

#endif // TOPSIDEBARWIDGET_H