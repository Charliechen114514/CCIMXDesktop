#ifndef QTFILEIO_H
#define QTFILEIO_H
#include <library/FileDefs.h>
class QString;
namespace QtFileIOUtils {
/**
 * @brief Checks if a path exists and has the specified permission.
 *
 * @param path The absolute or relative path of the file or directory.
 * @param permission The permission to check for (PathPermission::Read or PathPermission::Write).
 * @return bool Returns true if the path exists and the specified permission is granted, otherwise returns false.
 *
 * @note This function is effective for both files and directories.
 */
bool checkPathAndPermission(const QString& path, PermissionType permission);

/**
 * @brief Ensures a directory exists at the given path using Qt.
 *
 * If the directory (or any of its parents) does not exist, it will be created.
 *
 * @param path The absolute or relative path of the directory to check/create.
 * @return bool Returns true if the directory exists or was successfully created,
 * false otherwise.
 */
bool createDirectoryIfNotExsit(const QString& path);

/**
 * @brief Checks if a file exists, and if not, creates it.
 *
 * This function takes a file path as input. It first checks if the file
 * specified by the path already exists. If the file does not exist,
 * it attempts to create it.
 *
 * @param filePath The absolute or relative path to the file.
 * @return true if the file already exists or was successfully created; false otherwise.
 */
bool createFileIfNotExists(const QString& filePath);

/**
 * @brief composeDirentAndFile
 * @param folder
 * @param fileName
 * @return return filePath of folders
 */
QString composeDirentAndFile(const QString& folder, const QString& fileName);
};

#endif // QTFILEIO_H
