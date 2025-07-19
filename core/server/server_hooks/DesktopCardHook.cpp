#include "DesktopCardHook.h"
#include "builtin/page/home_card_manager/HomeCardManager.h"
#include "core/server/plugin_server/DesktopPluginServer.h"
#include <QDebug>
DesktopCardHook::DesktopCardHook(HomeCardManager* manager, DesktopWidgetPluginServer* parent)
    : QObject { parent }
    , DesktopServerHookBase {}
    , manager(manager)
    , server_monitoring(parent) {

    if (!parent || !manager) {
        throw std::invalid_argument("Error in binding the manager and parent sessions");
    }

    connect(server_monitoring, &DesktopWidgetPluginServer::pluginLoaded,
            this, &DesktopCardHook::hooked_the_plugin_widget);
}

void DesktopCardHook::process_unloaded_widget(
    const QString& what_plugin_widget) {
    QWidget* removed_widget = mappings.value(what_plugin_widget);
    if (!removed_widget) {
        qCritical() << "Can not find the sessions for the " << what_plugin_widget << " Thus we can not unload widgets";
        return;
    }

    manager->removeWidget(removed_widget);
    mappings.remove(what_plugin_widget);
}

void DesktopCardHook::hooked_the_plugin_widget(
    const QString& what_plugin_widget) {

    qDebug() << "Plugins of " << what_plugin_widget
             << "Entering hooks sessions";

    QWidget* installedHooks = server_monitoring->queryWidget(what_plugin_widget, nullptr);
    if (!installedHooks) {
        qCritical() << "Although the plugin is valid, "
                       "but we can not query the widget valid here!"
                       "thus sadly, the session is abort...";
        return;
    }

    // accept the widgets
    manager->installWidget(installedHooks);
    mappings.insert(what_plugin_widget, installedHooks);
}
