/**
 * @file DesktopDirentLocationManager.h
 * @brief Defines the DesktopDirentLocationManager class for managing desktop directory entries and locations.
 */

#ifndef DESKTOPDIRENTLOCATIONMANAGER_H
#define DESKTOPDIRENTLOCATIONMANAGER_H

#include "DesktopDirentInfoSettings.h" // Assumed to contain DesktopDirentType, DesktopServerType, ConfigureFileName
#include <QObject> // Base class for DesktopDirentLocationManager

// Forward declaration to avoid circular dependencies and improve compilation time
class DesktopMainWindow;

/**
 * @class DesktopDirentLocationManager
 * @brief Manages the locations and existence of various desktop directory entries and configuration files.
 *
 * This class is responsible for verifying the presence of critical directories and files
 * related to desktop components and server types within a specified root path.
 * It provides methods to query paths based on types and to check for their existence.
 * Signals are emitted when expected folders or configuration files are missing.
 */
class DesktopDirentLocationManager : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs a DesktopDirentLocationManager object.
     * @param root_path The base directory path where all desktop directory entries are expected to reside.
     * @param parent A pointer to the parent QObject, typically the DesktopMainWindow. Defaults to nullptr.
     */
    explicit DesktopDirentLocationManager(const QString& root_path, DesktopMainWindow* parent = nullptr);

    /**
     * @brief Performs a one-time check of all critical directory entries and configurations.
     * 	 * This method initiates a comprehensive check of all expected component folders,
     * server folders, and configuration files under the `root_path`. It will emit
     * `missingDirentFolder` or `missingServerFolder` signals for any missing entries.
     */
    void checkSelfOnce();

    /**
     * @brief Queries the expected path for a given DesktopDirentType.
     * @param type The type of desktop directory entry to query for (e.g., applications, documents).
     * @return The absolute path string for the specified directory entry.
     */
    QString queryFromType(const DesktopDirentType type);

    /**
     * @brief Queries the expected path for a given DesktopServerType.
     * @param serverType The type of desktop server directory to query for (e.g., database, web server).
     * @return The absolute path string for the specified server directory.
     */
    QString queryFromType(const DesktopServerType serverType);

    /**
     * @brief Checks if a component folder of a specific type exists.
     * @param type The DesktopDirentType to check.
     * @return True if the folder exists, false otherwise.
     */
    bool checkComponentFolder(const DesktopDirentType type);

    /**
     * @brief Checks if a server folder of a specific type exists.
     * @param serverType The DesktopServerType to check.
     * @return True if the folder exists, false otherwise.
     */
    bool checkServerFolder(const DesktopServerType serverType);

    /**
     * @brief Queries the expected path for a given configuration file name.
     * @param name The ConfigureFileName to query for (e.g., main config, user settings).
     * @return The absolute path string for the specified configuration file.
     */
    QString queryConfigType(const ConfigureFileName name);

    /**
     * @brief Checks if a configuration file of a specific name exists.
     * @param name The ConfigureFileName to check.
     * @return True if the configuration file exists, false otherwise.
     */
    bool checkConfigExsited(const ConfigureFileName name);

signals:
    /**
     * @brief Signal emitted when an expected desktop directory entry folder is missing.
     * @param folder The full path of the missing folder.
     * @param type The DesktopDirentType of the missing folder.
     */
    void missingDirentFolder(const QString& folder, const DesktopDirentType type);

    /**
     * @brief Signal emitted when an expected server-related folder is missing.
     * @param folder The full path of the missing server folder.
     * @param type The DesktopServerType of the missing server folder.
     */
    void missingServerFolder(const QString& folder, const DesktopServerType type);

private:
    /**
     * @brief The root path where all desktop directory entries are managed.
     */
    QString root_path;

    /**
     * @brief A pointer to the main window, used for potential UI interactions or context.
     */
    DesktopMainWindow* bindingWindow;

    /**
     * @brief Private helper method to check the existence of core root path sessions.
     * This might involve checking for the root_path itself or essential subdirectories
     * at the top level.
     */
    void check_root_path_sessions();

    /**
     * @brief Private helper method to iterate and check the existence of base component folders.
     * @param t The DesktopDirentType to check.
     * @param metaMessage A descriptive message to be used in logs or error messages for this component.
     */
    void iterate_check_basefolder_components(const DesktopDirentType t, const QString& metaMessage);

    /**
     * @brief Private helper method to iterate and check the existence of server-related component folders.
     * @param t The DesktopServerType to check.
     * @param metaMessage A descriptive message to be used in logs or error messages for this server component.
     */
    void iterate_check_server_components(const DesktopServerType t, const QString& metaMessage);
};

#endif // DESKTOPDIRENTLOCATIONMANAGER_H
