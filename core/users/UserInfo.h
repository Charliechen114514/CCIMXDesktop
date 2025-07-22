/**
 * @file UserInfo.h
 * @brief Defines the UserInfo class and its nested UserInfoBuilder class for managing user profile data.
 */

#ifndef USERINFO_H
#define USERINFO_H

#include <QString> // For QString to hold string data
#include <memory> // For std::unique_ptr

/**
 * @class UserInfo
 * @brief Represents a user's profile information, including name, email, phone number, and avatar path.
 *
 * This class is designed to hold immutable user information once constructed,
 * promoting data integrity. It uses a nested `UserInfoBuilder` class to
 * facilitate the creation of `UserInfo` objects, especially when dealing with
 * multiple optional fields or deserialization from external sources like JSON.
 * Copying and assignment are explicitly deleted to ensure unique ownership.
 */
class UserInfo {
public:
    /**
     * @class UserInfo::UserInfoBuilder
     * @brief A builder class for constructing UserInfo objects.
     * 	 * This nested class provides a fluent API for setting individual user information
     * fields and then building a `UserInfo` object. It simplifies the construction
     * process, especially when not all fields are known at once or when parsing from
     * external data formats like JSON.
     */
    class UserInfoBuilder {
    public:
        /**
         * @brief Constructs a new UserInfoBuilder.
         * Initializes an internal `UserInfo` object that will be populated.
         */
        UserInfoBuilder();

        /**
         * @brief Sets the name for the UserInfo object being built.
         * @param name The user's name.
         * @return A reference to the current UserInfoBuilder instance for method chaining.
         */
        UserInfoBuilder& set_name(QString name);

        /**
         * @brief Sets the email for the UserInfo object being built.
         * @param email The user's email address.
         * @return A reference to the current UserInfoBuilder instance for method chaining.
         */
        UserInfoBuilder& set_email(QString email);

        /**
         * @brief Sets the phone number for the UserInfo object being built.
         * @param phone The user's phone number.
         * @return A reference to the current UserInfoBuilder instance for method chaining.
         */
        UserInfoBuilder& set_phone_number(QString phone);

        /**
         * @brief Sets the avatar path for the UserInfo object being built.
         * @param path The file path to the user's avatar image.
         * @return A reference to the current UserInfoBuilder instance for method chaining.
         */
        UserInfoBuilder& set_avatar(QString path);

        /**
         * @brief Builds and returns a unique pointer to the constructed UserInfo object.
         * @return A `std::unique_ptr<UserInfo>` containing the newly created UserInfo object.
         * Ownership of the `UserInfo` object is transferred to the caller.
         */
        std::unique_ptr<UserInfo> build();

        /**
         * @brief Static method to construct a UserInfo object from a JSON string.
         * 		 * This method parses the provided JSON string and attempts to populate
         * the fields of a new `UserInfo` object. It returns a `std::unique_ptr`
         * to the created object. Error handling for malformed JSON or missing fields
         * should be implemented internally.
         * @param jsonString The JSON string containing user information.
         * @return A `std::unique_ptr<UserInfo>` if parsing is successful, otherwise a nullptr.
         */
        static std::unique_ptr<UserInfo> fromJson(const QString jsonString);

    private:
        /**
         * @brief An internal unique pointer to the UserInfo object being built.
         * This holds the UserInfo instance until `build()` is called.
         */
        std::unique_ptr<UserInfo> internal_info;
    };

    /**
     * @brief Gets the user's name.
     * @return A constant reference to the user's name.
     */
    const QString& get_name() const;

    /**
     * @brief Gets the user's email address.
     * @return A constant reference to the user's email.
     */
    const QString& get_email() const;

    /**
     * @brief Gets the user's phone number.
     * @return A constant reference to the user's phone number.
     */
    const QString& get_phone_number() const;

    /**
     * @brief Gets the file path to the user's avatar.
     * @return A constant reference to the avatar file path.
     */
    const QString& get_avatar() const;

    /**
     * @brief Sets the file path for the user's avatar.
     * @param av_path The new file path to the avatar image.
     */
    void set_avator(const QString& av_path);

    /**
     * @brief Sets the user's name.
     * @param name The new name for the user.
     */
    void set_name(const QString& name);

    /**
     * @brief Sets the user's email address.
     * @param email The new email address for the user.
     */
    void set_email(const QString& email);

    /**
     * @brief Sets the user's phone number.
     * @param phone The new phone number for the user.
     */
    void set_phone(const QString& phone);

    /**
     * @brief Serializes the UserInfo object into a JSON string.
     * @return A QString containing the JSON representation of the user information.
     */
    QString serialized() const;

    // Delete copy constructor and copy assignment operator to prevent unintended copying.
    UserInfo(const UserInfo&) = delete;
    UserInfo& operator=(const UserInfo&) = delete;

    /**
     * @brief Default destructor for UserInfo.
     */
    ~UserInfo() = default;

private:
    /**
     * @brief Declares UserInfoBuilder as a friend class.
     * This allows UserInfoBuilder to access the private constructor and members of UserInfo
     * for construction purposes.
     */
    friend class UserInfoBuilder;

    /**
     * @brief Private default constructor.
     * This ensures that UserInfo objects can only be created via the UserInfoBuilder.
     */
    UserInfo() = default;

    QString name; ///< The user's full name.
    QString phone_number; ///< The user's phone number.
    QString email; ///< The user's email address.
    QString av_path; ///< The file path to the user's avatar image.
};

#endif // USERINFO_H
