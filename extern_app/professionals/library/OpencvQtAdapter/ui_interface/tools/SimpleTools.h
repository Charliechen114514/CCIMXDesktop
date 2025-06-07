#ifndef SIMPLETOOLS_H
#define SIMPLETOOLS_H
#include <QString>
#include <stdexcept>
/**
 * @namespace SimpleTools creates the simple tools for the
 * ui interface library
 */
namespace SimpleTools {

/**
 * @brief The FailedReadFile class matches the failed load qss
 * errors
 */
class FailedReadFile : public std::runtime_error {
public:
    /**
     * @brief FailedReadFile
     * @param path which file failed to loaded?
     */
    explicit FailedReadFile(const std::string& path)
        : error("Can not process file:" + path)
        , std::runtime_error("Failed read files") { }
    /**
     * @brief what is descriptions of the exceptions
     * @return descriptions of the exceptions
     */
    const char* what() const noexcept {
        return error.c_str();
    }

    const std::string error;
};

/**
 * @brief   readQss read qss from src file,
 *          this may possibly throw FailedReadFile exception
 * @param filePath path to fetch the qss
 * @return qss string for set
 */
QString readQss(const QString& filePath);

};

#endif // SIMPLETOOLS_H
