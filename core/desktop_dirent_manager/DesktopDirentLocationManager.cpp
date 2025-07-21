#include "DesktopDirentLocationManager.h"
#include "library/qt_relative/fileio/QtFileIO.h"
#include "ui/desktopmainwindow.h"
#include <QDir>
namespace {

QString typeToFolderName(const DesktopDirentType type) {
    switch (type) {
    case DesktopDirentType::Documents:
        return "Documents";
    case DesktopDirentType::Downloads:
        return "Downloads";
    case DesktopDirentType::Music:
        return "Music";
    case DesktopDirentType::Pictures:
        return "Pictures";
    case DesktopDirentType::Videos:
        return "Videos";
    case DesktopDirentType::Binaries:
        return "Binaries";
    case DesktopDirentType::Config:
        return "Config";
    case DesktopDirentType::Cache:
        return "Cache";
    case DesktopDirentType::Runtime:
        return "RunTime";
    case DesktopDirentType::Trash:
        return "Trash";
    }
    throw std::invalid_argument("What the fuck???");
}

QString fromServerType(const DesktopServerType t) {
    switch (t) {
    case DesktopServerType::TOAST_SUMMON:
        return TOAST_SUMMON_DIRENT;
        break;
    case DesktopServerType::PLUGIN_WIDGET_PLACED:
        return PLUGIN_WIDGET_PLACED;
        break;
    }
    throw std::invalid_argument("What the fuck of the server type???");
}

QString getConfigPath(const QString& rootPath, int index = 0) {
    const auto& pair = configs_dirent_name_pair[index];
    QDir dir(rootPath);
    dir.cd(QString::fromUtf8(pair.first));
    return dir.filePath(QString::fromUtf8(pair.second));
}

}

DesktopDirentLocationManager::DesktopDirentLocationManager(
    const QString& root_path, DesktopMainWindow* parent)
    : QObject { parent }
    , root_path(root_path)
    , bindingWindow(parent) {
    checkSelfOnce();
}

void DesktopDirentLocationManager::checkSelfOnce() {
    check_root_path_sessions();

    for (int i = 0; i < DesktopDirentTypeMAX; i++) {
        iterate_check_basefolder_components(
            static_cast<const DesktopDirentType>(i),
            DesktopDirentTypeMETAS[i]);
    }

    for (int i = 0; i < DesktopServerTypeMAX; i++) {
        iterate_check_server_components(
            static_cast<const DesktopServerType>(i),
            DesktopServerTypeMETAS[i]);
    }
}

QString DesktopDirentLocationManager::queryFromType(const DesktopDirentType type) {
    return QDir(root_path).filePath(typeToFolderName(type));
}

QString DesktopDirentLocationManager::queryFromType(const DesktopServerType serverType) {
    return QDir(queryFromType(DesktopDirentType::Runtime))
        .filePath(fromServerType(serverType));
}

bool DesktopDirentLocationManager::checkComponentFolder(const DesktopDirentType type) {
    QString folder = queryFromType(type);
    return QtFileIOUtils::checkPathAndPermission(folder, PermissionType::Write);
}

bool DesktopDirentLocationManager::checkServerFolder(const DesktopServerType serverType) {
    QString folder = queryFromType(serverType);
    return QtFileIOUtils::checkPathAndPermission(folder, PermissionType::Write);
}

QString DesktopDirentLocationManager::queryConfigType(const ConfigureFileName name) {
    return getConfigPath(queryFromType(DesktopDirentType::Config),
                         static_cast<int>(name));
}

bool DesktopDirentLocationManager::checkConfigExsited(const ConfigureFileName name) {
    QString file = queryConfigType(name);
    return QtFileIOUtils::checkPathAndPermission(file, PermissionType::Write);
}

void DesktopDirentLocationManager::check_root_path_sessions() {
    if (QtFileIOUtils::checkPathAndPermission(root_path, PermissionType::Write)) {
        if (QFileInfo(root_path).isDir()) {
            qInfo() << "Scan the exsited locatable path in " << root_path
                    << "This will be the desktop rootpath";
        } else {
            // Application Dumped
            qFatal() << "Root Path you submit is not dirent path! "
                        "Application Dumped!";
        }
    } else {
        qCritical() << "Root Path you submit is not exsited or Permission denied! "
                       "Application will create in auto way in: "
                    << root_path;
        if (!QtFileIOUtils::createDirectoryIfNotExsit(root_path)) {
            qFatal() << "Root path you submit is sadly unable to create, "
                        "Application Dumped!";
        }
    }
}

void DesktopDirentLocationManager::iterate_check_basefolder_components(
    const DesktopDirentType t, const QString& metaMessage) {
    QString this_dirent = queryFromType(t);
    if (!QtFileIOUtils::createDirectoryIfNotExsit(this_dirent)) {
        qCritical() << "When issuing the " << metaMessage
                    << "We found creating target dirent: "
                    << this_dirent << " failed!"
                    << "Some functionalities maybe limited!";
        emit missingDirentFolder(this_dirent, t);
    }
}

void DesktopDirentLocationManager::iterate_check_server_components(
    const DesktopServerType t, const QString& metaMessage) {
    QString this_dirent = queryFromType(t);
    if (!QtFileIOUtils::createDirectoryIfNotExsit(this_dirent)) {
        qCritical() << "When issuing the " << metaMessage
                    << "We found creating target dirent: "
                    << this_dirent << " failed!"
                    << "Some functionalities maybe limited!";
        emit missingServerFolder(this_dirent, t);
    }
}
