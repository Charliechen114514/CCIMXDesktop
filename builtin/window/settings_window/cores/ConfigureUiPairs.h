#ifndef CONFIGUREUIPAIRS_H
#define CONFIGUREUIPAIRS_H

#include <QHash>
#include <QObject>

class QTreeWidget;
class QStackedWidget;
class QTreeWidgetItem;
class QWidget;

/**
 * @brief The ConfigureUiPairs struct
 * Manages the mapping between tree items and UI panels for configuration views.
 *
 * Allows installing mapping relationships between navigation tree items
 * and associated QWidget panels, and handles automatic switching.
 */
struct ConfigureUiPairs : public QObject {
    Q_OBJECT

public:
    ConfigureUiPairs() = delete;
    /**
     * @brief Disable copy move
     *
     */
    Q_DISABLE_COPY_MOVE(ConfigureUiPairs);

    /**
     * @brief Constructs the ConfigureUiPairs manager.
     * @param treeWidget The tree widget to act as navigation.
     * @param stackedWidget The stacked widget holding configuration panels.
     */
    ConfigureUiPairs(QTreeWidget* treeWidget, QStackedWidget* stackedWidget);

    /**
     * @brief Installs a new tree item and associates it with a UI widget.
     * @param itemName Name of the tree item.
     * @param parent Parent tree item (optional).
     * @param installed_widgets The associated widget.
     * @return The created QTreeWidgetItem.
     */
    QTreeWidgetItem* install_mappings(const QString& itemName, QTreeWidgetItem* parent, QWidget* installed_widgets);

private slots:
    /**
     * @brief Handles item change to switch UI panels.
     * @param item The newly selected item.
     */
    void process_switch_sessions(QTreeWidgetItem* item);

private:
    QHash<QTreeWidgetItem*, QWidget*> mappings; ///< Mapping from tree items to widgets.
    QTreeWidget* treeWidget; ///< Tree navigation component.
    QStackedWidget* stackedWidget; ///< Stacked UI widget.
};

#endif // CONFIGUREUIPAIRS_H
