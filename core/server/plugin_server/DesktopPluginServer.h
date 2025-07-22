/**
 * @file DesktopPluginServer.h
 * @brief Defines the DesktopWidgetPluginServer class for managing dynamic loading and unloading of widget plugins.
 */

#ifndef DESKTOPPLUGINSERVER_H
#define DESKTOPPLUGINSERVER_H

#include "core/server/DesktopServerBase.h" // Base class for server-like functionalities
#include <QHash> // For storing a map of plugin names to QPluginLoader instances

// Forward declarations to avoid heavy includes and circular dependencies
class QPluginLoader;
class FileMonitor;
class DesktopMainWindow;
class QWidget; // Required for queryWidget return type

/**
 * @class DesktopWidgetPluginServer
 * @brief Manages the lifecycle of dynamically loaded QWidget-based plugins.
 *
 * This class extends DesktopServerBase and provides functionalities to load, unload,
 * and manage plugins that expose QWidget instances. It can monitor a specified
 * directory for new or removed plugin DLLs and automatically manage them.
 *
 * It emits signals to notify about the success or failure of plugin operations.
 */
class DesktopWidgetPluginServer : public DesktopServerBase {
    Q_OBJECT

public:
    /**
     * @brief Constructs a DesktopWidgetPluginServer instance.
     * @param monitoring_dll The path to the directory or specific DLL to monitor for plugins.
     * @param parent A pointer to the DesktopMainWindow instance that this server is associated with.
     * This window might be the parent for the loaded widgets.
     */
    explicit DesktopWidgetPluginServer(const QString& monitoring_dll, DesktopMainWindow* parent);

    /**
     * @brief Destroys the DesktopWidgetPluginServer object.
     * 	 * This destructor ensures all loaded plugins are properly unloaded and
     * resources are released.
     */
    ~DesktopWidgetPluginServer() override;

    /**
     * @brief Inserts (loads) a plugin into the server.
     * 	 * This method attempts to load a plugin from the given path and associates
     * it with a unique plugin name. If the plugin is successfully loaded,
     * the `pluginLoaded` signal is emitted. Otherwise, `pluginFailed` is emitted.
     * @param pluginName A unique name to identify the plugin.
     * @param plugin_path The absolute file path to the plugin (DLL/shared library).
     */
    void insertPlugin(const QString& pluginName, const QString& plugin_path);

    /**
     * @brief Unloads a plugin identified by its name.
     * 	 * This method unloads the specified plugin, removing it from memory.
     * If successful, `pluginUnloaded` is emitted. If unloading fails,
     * `pluginUnloadedFailed` is emitted.
     * @param plugin_name The unique name of the plugin to unload.
     * @return True if the plugin was successfully unloaded, false otherwise.
     */
    bool unloadPlugin(const QString& plugin_name);

    /**
     * @brief Scans the target directory for new or updated plugin DLLs.
     * 	 * This method is typically called to discover plugins that have been added
     * or modified in the `monitoring_dll` path since the last scan or initialization.
     * It will load any new plugins found.
     */
    void scanTargetDirent();

    /**
     * @brief Unloads and removes all currently loaded plugins.
     * 	 * This method iterates through all managed plugins, unloads them, and clears
     * the internal plugin map.
     */
    void removeAllPlugins();

    /**
     * @brief Queries and instantiates a QWidget from a loaded plugin.
     * 	 * This method attempts to create an instance of a widget provided by the
     * specified plugin. The plugin must expose a creatable QWidget.
     * @param pluginName The unique name of the plugin from which to query the widget.
     * @param expected_parent The parent QWidget for the newly created plugin widget.
     * @return A pointer to the newly created QWidget instance, or nullptr if the plugin
     * is not found or the widget cannot be created.
     */
    QWidget* queryWidget(const QString& pluginName, QWidget* expected_parent);

    /**
     * @brief Returns a pointer to the associated DesktopMainWindow.
     * @return A pointer to the DesktopMainWindow instance that this server is hooked to.
     */
    DesktopMainWindow* hooked_window() const { return window; };

signals:
    /**
     * @brief Signal emitted when a plugin has been successfully loaded.
     * @param pluginName The name of the loaded plugin.
     * @param pluginPath The file path from which the plugin was loaded.
     */
    void pluginLoaded(const QString& pluginName, const QString& pluginPath);

    /**
     * @brief Signal emitted when a plugin fails to load.
     * @param pluginName The name of the plugin that failed to load.
     * @param pluginPath The file path of the plugin that failed.
     * @param pluginErrorString A descriptive string detailing the error.
     */
    void pluginFailed(const QString& pluginName,
                      const QString& pluginPath,
                      const QString& pluginErrorString);

    /**
     * @brief Signal emitted when a plugin has been successfully unloaded.
     * @param pluginName The name of the unloaded plugin.
     */
    void pluginUnloaded(const QString& pluginName);

    /**
     * @brief Signal emitted when a plugin fails to unload.
     * @param pluginName The name of the plugin that failed to unload.
     * @param pluginErrorString A descriptive string detailing the error.
     */
    void pluginUnloadedFailed(const QString& pluginName,
                              const QString& pluginErrorString);

private:
    /**
     * @brief A hash map storing mappings from plugin names to their QPluginLoader instances.
     * 	 * This map allows quick access to the QPluginLoader object for managing
     * the lifecycle of each loaded plugin.
     */
    QHash<QString, QPluginLoader*> plugin_map;

    /**
     * @brief A pointer to the main desktop window.
     * 	 * This is the DesktopMainWindow instance that this plugin server is associated with,
     * potentially serving as the parent for widgets loaded from plugins.
     */
    DesktopMainWindow* window;

    /**
     * @brief A pointer to the FileMonitor instance.
     * 	 * This monitor is used to detect changes (e.g., new, modified, or deleted DLLs)
     * in the `monitoring_dll` path, enabling hot-loading capabilities.
     */
    FileMonitor* hot_loaded;
};

#endif // DESKTOPPLUGINSERVER_H
