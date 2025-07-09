#ifndef FILEIOUTILS_H
#define FILEIOUTILS_H
#include "library/FileDefs.h"
#include <string>

namespace StdFileIOUtils {
/**
 * @brief Checks if a path exists and has the specified permission.
 *
 * @param path The absolute or relative path of the file or directory.
 * @param permission The permission to check for (PathPermission::Read or PathPermission::Write).
 * @return bool Returns true if the path exists and the specified permission is granted, otherwise returns false.
 *
 * @note This function is effective for both files and directories.
 */
bool checkFileExsitence(
    const std::string& path,
    PermissionType type = PermissionType::Read);

/**
 * @brief Ensures a directory exists at the given path using the C++17 standard library.
 *
 * If the directory (or any of its parents) does not exist, it will be created.
 * This function will fail if a regular file with the same name already exists at the path.
 *
 * @param path The path object of the directory to check/create.
 * @return bool Returns true if the directory exists or was successfully created,
 * false otherwise (e.g., permission error or a file exists at the path).
 */
bool createDirectoryIfNotExsit(const std::string& path);

/**
 * @brief Checks if a file exists, and if not, creates it.
 *
 * This function takes a file path as input. It first checks if the file
 * specified by the path already exists using std::filesystem. If the file
 * does not exist, it attempts to create it by opening an output file stream.
 *
 * @param filePath The absolute or relative path to the file.
 * @return true if the file already exists or was successfully created; false otherwise.
 */
bool createFileIfNotExists(const std::string& filePath);

}

#endif // FILEIOUTILS_H
