/**
 * @file DesktopUserInfo.h
 * @brief Defines the DesktopUserInfo class, responsible for managing and providing user information.
 */

#ifndef DESKTOPUSERINFO_H
#define DESKTOPUSERINFO_H

#include "UserInfo.h" // Includes the UserInfo struct/class definition
#include <QObject> // Base class for DesktopUserInfo, enabling signals/slots
#include <memory> // Required for std::unique_ptr

// Forward declaration to avoid heavy includes and circular dependencies
class DesktopDirentLocationManager;

/**
 * @class DesktopUserInfo
 * @brief Manages the retrieval and provision of user-specific information within the desktop environment.
 *
 * This class is responsible for initializing and holding a `UserInfo` object,
 * which contains details about the current user. It interacts with a
 * `DesktopDirentLocationManager` to potentially locate user-specific configuration
 * files or directories from where the `UserInfo` can be loaded.
 *
 * It provides a slot to trigger the initialization process and a signal to
 * indicate when the user information has been successfully loaded.
 */
class DesktopUserInfo : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a DesktopUserInfo object.
     * @param parent A pointer to the `DesktopDirentLocationManager` instance that this
     * `DesktopUserInfo` object might use to locate user data. This also serves as the
     * `QObject` parent for memory management. Defaults to `nullptr`.
     */
    explicit DesktopUserInfo(DesktopDirentLocationManager* parent = nullptr);

public slots:
    /**
     * @brief Initiates the user information initialization process.
     * 	 * This slot triggers a one-time scan of the target file (presumably a user info
     * configuration file or similar) to load the `UserInfo` data. After successful
     * initialization, the `user_init_ok` signal will be emitted.
     */
    void start_init(); ///< start init will scan the target file once

    /**
     * @brief Retrieves a pointer to the `UserInfo` object.
     * @warning The `UserInfo` object might not be fully initialized if `start_init()`
     * has not completed or failed. Callers should check for initialization status
     * or rely on the `user_init_ok` signal for certainty.
     * @return A raw pointer to the internal `UserInfo` object.
     */
    inline UserInfo* get_info() { return info.get(); } ///< get info, might be not inited!

signals:
    /**
     * @brief Signal emitted when the user information has been successfully initialized.
     * @param info A constant reference to the initialized `UserInfo` object.
     */
    void user_init_ok(const UserInfo& info);

private:
    /**
     * @brief A pointer to the `DesktopDirentLocationManager`.
     * 	 * This manager is used to determine the paths where user-specific configuration
     * or data files might be located, which are then used to populate `UserInfo`.
     */
    DesktopDirentLocationManager* manager;

    /**
     * @brief A unique pointer to the `UserInfo` object.
     * 	 * This `std::unique_ptr` manages the lifetime of the `UserInfo` object,
     * ensuring it is properly deallocated when no longer needed.
     */
    std::unique_ptr<UserInfo> info;
};

#endif // DESKTOPUSERINFO_H
