#ifndef DESKTOPCARDHOOK_H
#define DESKTOPCARDHOOK_H
#include "core/server/DesktopServerHookBase.h"
#include <QHash>
#include <QObject>
class DesktopWidgetPluginServer;
class HomeCardManager;
class DesktopCardHook : public QObject, public DesktopServerHookBase {
	Q_OBJECT
public:
    explicit DesktopCardHook(HomeCardManager* manager,
                             DesktopWidgetPluginServer* parent = nullptr);
    void process_unloaded_widget(const QString& what_plugin_widget);

private slots:
    void hooked_the_plugin_widget(const QString& what_plugin_widget);

private:
    HomeCardManager* manager;
    DesktopWidgetPluginServer* server_monitoring;
    QHash<QString, QWidget*> mappings;
};

#endif // DESKTOPCARDHOOK_H
