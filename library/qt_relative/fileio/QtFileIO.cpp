#include "QtFileIO.h"
#include <QDir>
#include <QFileInfo>
bool QtFileIOUtils::checkPathAndPermission(const QString& path, PermissionType permission) {
    // 1. Create a QFileInfo object to get information about the path.
    const QFileInfo fileInfo(path);

    // 2. Check if the path exists.
    if (!fileInfo.exists()) {
        qWarning() << "Check failed: Path does not exist -" << path;
        return false;
    }

    // 3. Check for the specified permission.
    switch (permission) {
    case PermissionType::Read:
        // Check if the application has read permission for this path.
        return fileInfo.isReadable();
    case PermissionType::Write:
        // Check if the application has write permission for this path.
        if (fileInfo.isDir()) {
            QDir dir(fileInfo.absoluteFilePath());
            if (!dir.exists()) {
                return false;
            }
            // make attempts to create file
            QString testFilePath = dir.filePath(".qt_permission_test");

            QFile testFile(testFilePath);
            bool success = testFile.open(QIODevice::WriteOnly);
            if (success) {
                testFile.close();
                testFile.remove();
            }
            return success;
        } else {
            return fileInfo.isWritable();
        }
    }

    // Default case (should not be reached).
    return false;
}

bool QtFileIOUtils::createDirectoryIfNotExsit(const QString& path) {
    // Create a QDir object representing the directory path.
    QDir dir(path);

    // Check if the directory already exists.
    if (dir.exists()) {
        qInfo() << "dirent path " << path << " is exsited! pass the check";
        return true;
    }

    // If it doesn't exist, try to create it.
    // mkpath will create all necessary parent directories.
    // The "." argument means "create the path represented by this QDir object".
    if (dir.mkpath(".")) {
        qInfo() << "Successfully created directory:" << path;
        return true;
    } else {
        qWarning() << "Failed to create directory:" << path;
        return false;
    }
}

bool QtFileIOUtils::createFileIfNotExists(const QString& filePath) {
    QFile file(filePath);

    // Check if the file already exists
    if (file.exists()) {
        qInfo() << "File already exists:" << filePath;
        return true;
    } else {
        // If the file does not exist, try to create it
        // QIODevice::WriteOnly will create the file if it doesn't exist.
        if (file.open(QIODevice::WriteOnly)) {
            qInfo() << "File created successfully:" << filePath;
            file.close(); // Close the file immediately after creation
            return true;
        } else {
            qWarning() << "Failed to create file:" << filePath << "Error:" << file.errorString();
            return false;
        }
    }
}
