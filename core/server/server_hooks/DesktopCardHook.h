/**
 * @file DesktopCardHook.h
 * @brief Defines the DesktopCardHook class, which integrates desktop widget plugins with a card management system.
 */

#ifndef DESKTOPCARDHOOK_H
#define DESKTOPCARDHOOK_H

#include "core/server/DesktopServerHookBase.h" // Base class for server-related hooks
#include <QHash> // For mapping plugin names to QWidget instances
#include <QObject> // Base class for DesktopCardHook, enabling signals/slots

// Forward declarations to avoid heavy includes and circular dependencies
class DesktopWidgetPluginServer;
class HomeCardManager;
class QWidget; // Required for mappings

/**
 * @class DesktopCardHook
 * @brief Integrates a DesktopWidgetPluginServer with a HomeCardManager to display loaded plugin widgets as cards.
 *
 * This class acts as a bridge, listening for signals from a DesktopWidgetPluginServer when plugins
 * (which expose QWidgets) are loaded. Upon a successful plugin load, it takes the widget
 * and installs it into the HomeCardManager, effectively displaying it as a "card" in the UI.
 * It also handles the removal of widgets when plugins are unloaded.
 */
class DesktopCardHook : public QObject, public DesktopServerHookBase {
    Q_OBJECT

public:
    /**
     * @brief Constructs a DesktopCardHook instance.
     * @param manager A pointer to the HomeCardManager that will display the plugin widgets.
     * The hook does not take ownership of the manager.
     * @param parent A pointer to the DesktopWidgetPluginServer that this hook will monitor.
     * This is also the QObject parent for this hook, which means it manages
     * its lifetime. Defaults to nullptr.
     */
    explicit DesktopCardHook(HomeCardManager* manager,
                             DesktopWidgetPluginServer* parent = nullptr);

    /**
     * @brief Processes an unloaded widget, removing it from the HomeCardManager.
     * 	 * This method is called when a plugin widget is unloaded. It removes the corresponding
     * QWidget from the HomeCardManager, effectively taking the "card" off the display.
     * @param what_plugin_widget The name of the plugin whose widget is being unloaded.
     */
    void process_unloaded_widget(const QString& what_plugin_widget);

private slots:
    /**
     * @brief Slot that is called when a plugin widget is successfully hooked (loaded).
     * 	 * This slot connects to the `pluginLoaded` signal from the `DesktopWidgetPluginServer`.
     * It instantiates the widget from the loaded plugin and adds it to the `HomeCardManager`.
     * @param what_plugin_widget The name of the plugin whose widget has been loaded.
     */
    void hooked_the_plugin_widget(const QString& what_plugin_widget);

private:
    /**
     * @brief A pointer to the HomeCardManager instance.
     * 	 * This manager is responsible for visually organizing and displaying the QWidgets
     * loaded by the plugin server as "cards."
     */
    HomeCardManager* manager;

    /**
     * @brief A pointer to the DesktopWidgetPluginServer instance being monitored.
     * 	 * This server is the source of the dynamically loaded QWidget plugins.
     * The hook listens to its signals to manage the lifecycle of the cards.
     */
    DesktopWidgetPluginServer* server_monitoring;

    /**
     * @brief A hash map storing mappings from plugin names to their associated QWidget instances.
     * 	 * This map helps keep track of which widget belongs to which plugin,
     * allowing for proper removal when plugins are unloaded.
     */
    QHash<QString, QWidget*> mappings;
};

#endif // DESKTOPCARDHOOK_H
