#include "FileIOUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <system_error>
bool StdFileIOUtils::checkFileExsitence(const std::string& path, PermissionType type) {
    std::error_code ec;

    if (!std::filesystem::exists(path, ec) || ec) {
        std::cerr << "File is not exsited!" << path << std::endl;
        return false;
    }

    bool is_directory = std::filesystem::is_directory(path, ec);
    if (ec) {
        std::cerr << "Check failed! we can not specified the type of " << path << std::endl;
        return false;
    }

    if (type == PermissionType::Read) {
        if (is_directory) {
            try {
                auto it = std::filesystem::directory_iterator(path);
                (void)it;
                return true;
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Directory read failed due to reason: " << e.what() << std::endl;
                return false;
            }
        } else {
            std::ifstream file(path);
            return file.is_open();
        }
    } else if (type == PermissionType::Write) {
        if (is_directory) {
            auto temp_file_path = path + "/_____temp_permission_check_file.tmp";
            std::ofstream temp_file(temp_file_path);
            if (!temp_file.is_open()) {
                return false;
            }
            temp_file.close();
            std::filesystem::remove(temp_file_path, ec);
            return !ec;
        } else {
            std::ofstream file(path, std::ios::app);
            return file.is_open();
        }
    }

    return false;
}

bool StdFileIOUtils::createDirectoryIfNotExsit(const std::string& path) {
    // Use error_code version of filesystem functions to prevent exceptions.
    std::error_code ec;

    // Check if the path exists.
    if (std::filesystem::exists(path, ec)) {
        // Path exists, now check if it's a directory.
        if (std::filesystem::is_directory(path, ec)) {
            // It's a directory, so our job is done.
            return true;
        } else {
            // It's a file, not a directory. This is an error condition.
            std::cerr << "Error: Path exists but is not a directory: " << path << std::endl;
            return false;
        }
    }

    // If we reach here, the path does not exist. Try to create it.
    // create_directories will create all necessary parent directories.
    if (std::filesystem::create_directories(path, ec)) {
        std::cout << "Successfully created directory: " << path << std::endl;
        return true;
    } else {
        // If creation failed, ec will contain the error information.
        std::cerr << "Error: Failed to create directory: " << path
                  << " - " << ec.message() << std::endl;
        return false;
    }
}

bool StdFileIOUtils::createFileIfNotExists(const std::string& filePath) {
    // Check if the file already exists using std::filesystem
    if (std::filesystem::exists(filePath)) {
        std::cout << "File already exists: " << filePath << std::endl;
        return true;
    } else {
        // If the file does not exist, try to create it
        // std::ios::out will create the file if it doesn't exist when opened.
        std::ofstream outputFile(filePath);

        // Check if the file was successfully opened (and thus created)
        if (outputFile.is_open()) {
            std::cout << "File created successfully: " << filePath << std::endl;
            outputFile.close(); // Close the file stream immediately after creation
            return true;
        } else {
            std::cerr << "Failed to create file: " << filePath << std::endl;
            return false;
        }
    }
}
