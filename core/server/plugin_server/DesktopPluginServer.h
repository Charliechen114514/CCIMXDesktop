#ifndef DESKTOPPLUGINSERVER_H
#define DESKTOPPLUGINSERVER_H
#include "core/server/DesktopServerBase.h"
#include <QHash>
class QPluginLoader;
class FileMonitor;
class DesktopMainWindow;
class DesktopWidgetPluginServer : public DesktopServerBase {
	Q_OBJECT
public:
    explicit DesktopWidgetPluginServer(const QString& monitoring_dll, DesktopMainWindow* parent);
    ~DesktopWidgetPluginServer() override;
    void insertPlugin(const QString& pluginName, const QString& plugin_path);
    bool unloadPlugin(const QString& plugin_name);
    void scanTargetDirent();
    void removeAllPlugins();
    QWidget* queryWidget(const QString& pluginName, QWidget* expected_parent);
    DesktopMainWindow* hooked_window() const { return window; };
signals:
    void pluginLoaded(const QString& pluginName, const QString& pluginPath);
    void pluginFailed(const QString& pluginName,
                      const QString& pluginPath,
                      const QString& pluginErrorString);
    void pluginUnloaded(const QString& pluginName);
    void pluginUnloadedFailed(const QString& pluginName,
                              const QString& pluginErrorString);

private:
    QHash<QString, QPluginLoader*> plugin_map; ///< mappings
    DesktopMainWindow* window;
    FileMonitor* hot_loaded;
};

#endif // DESKTOPPLUGINSERVER_H
