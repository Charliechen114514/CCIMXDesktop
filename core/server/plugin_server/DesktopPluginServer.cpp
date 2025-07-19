#include "DesktopPluginServer.h"
#include "PluginValidator.h"
#include "desktopmainwindow.h"
#include "library/qt_relative/file_monitor/FileMonitor.h"
#include "plugin_loader/plugin_base/DesktopPluginWidgetBase.h"
#include <QDir>
#include <QFileInfo>
#include <QPluginLoader>

DesktopWidgetPluginServer::DesktopWidgetPluginServer(const QString& monitoring_dll, DesktopMainWindow* parent)
    : DesktopServerBase { parent }
    , window(parent) {
    hot_loaded = new FileMonitor(monitoring_dll, this);
    connect(hot_loaded, &FileMonitor::newFiles,
            this, [this](const QStringList& l) {
                for (const auto& each : l) {
                    QFileInfo info(each);
                    this->insertPlugin(info.baseName(), each);
                }
            });
    connect(hot_loaded, &FileMonitor::deletedFiles,
            this, [this](const QStringList& l) {
                for (const auto& each : l) {
                    QFileInfo info(each);
                    this->unloadPlugin(info.baseName());
                }
            });
}

DesktopWidgetPluginServer::~DesktopWidgetPluginServer() {
    removeAllPlugins();
}

void DesktopWidgetPluginServer::insertPlugin(const QString& pluginName, const QString& plugin_path) {
    QFileInfo fileInfo(plugin_path);

    if (plugin_map.contains(pluginName)) {
        qWarning() << "Plugin: " << pluginName << " has been exsited! So we wont insert the session again!";
        return;
    }

    if (!fileInfo.exists()) {
        emit pluginFailed(pluginName, plugin_path, "Plugin is not exsited or searched!");
        return;
    }

    if (!PluginValidator::isValidPluginFile(plugin_path)) {
        emit pluginFailed(pluginName, plugin_path, "Invalid plugin file extension for current platform.");
        return;
    }

    QPluginLoader* loader = new QPluginLoader(plugin_path, this);
    QObject* attempted = loader->instance();

    if (!attempted) {
        QString errorString = loader->errorString();
        qWarning() << "Plugin failed to load:" << errorString;
        emit pluginFailed(pluginName, plugin_path, errorString);
        return;
    }

    plugin_map.insert(pluginName, loader);
    qDebug() << "Insert the plugin: " << pluginName;
    emit pluginLoaded(pluginName, plugin_path);
}

bool DesktopWidgetPluginServer::unloadPlugin(const QString& plugin_name) {
    if (plugin_map.contains(plugin_name)) {
        QPluginLoader* loader = plugin_map.value(plugin_name);
        qDebug() << "Unloading plugin:" << loader->fileName();
        loader->unload();
        loader->deleteLater();
        plugin_map.remove(plugin_name);
        emit pluginUnloaded(plugin_name);
        return true;
    } else {
        qWarning() << "Plugin not found with name:" << plugin_name;
        emit pluginUnloadedFailed(plugin_name, "Plugin not found");
        return false;
    }
}

void DesktopWidgetPluginServer::scanTargetDirent() {
    const QString scanDirent = hot_loaded->monitorDirent();
    QDir pluginDir(scanDirent);

    if (!pluginDir.exists()) {
        qWarning() << "[PluginLoader] Directory does not exist:" << scanDirent;
        return;
    }

    QFileInfoList fileList = pluginDir.entryInfoList(QDir::Files | QDir::NoSymLinks);

    if (fileList.size() == 0) {
        qInfo() << "There has been no plugins in dirent!";
        return;
    }

    for (const QFileInfo& fileInfo : std::as_const(fileList)) {
        const QString fileName = fileInfo.fileName();
        const QString fullPath = fileInfo.absoluteFilePath();

        if (!PluginValidator::isValidPluginFile(fileName)) {
            qWarning() << "PluginLoader: Skipped (invalid extension):" << fileName;
            continue;
        }

        QString pluginName = fileInfo.baseName();
        qInfo() << "PluginLoader: " << pluginName << " at " << fullPath << " will be attempted to insert!";
        insertPlugin(pluginName, fullPath);
    }
}

void DesktopWidgetPluginServer::removeAllPlugins() {
    const QList<QString> pluginNames = plugin_map.keys();

    for (const QString& name : pluginNames) {
        bool success = unloadPlugin(name);
        if (!success) {
            qWarning() << "Failed to unload plugin:" << name;
        }
    }
}

QWidget* DesktopWidgetPluginServer::queryWidget(
    const QString& pluginName, QWidget* expected_parent) {
    if (!plugin_map.contains(pluginName)) {
        qWarning() << "Plugin not found:" << pluginName;
        return nullptr;
    }

    QPluginLoader* loader = plugin_map.value(pluginName);
    QObject* pluginInstance = loader->instance();

    if (!pluginInstance) {
        qWarning() << "Plugin instance is null for:" << pluginName;
        return nullptr;
    }

    auto* plugin = qobject_cast<DesktopPluginWidgetBase*>(pluginInstance);
    if (!plugin) {
        qWarning() << "Plugin does not implement DesktopPluginWidgetBase:" << pluginName;
        return nullptr;
    }

    // create a new widget
    QWidget* widget = plugin->factorize_widget(expected_parent);
    if (!widget) {
        qWarning() << "Failed to create widget from plugin:" << pluginName;
        return nullptr;
    }

    return widget;
}
