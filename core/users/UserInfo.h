#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <memory>

class UserInfo {
public:
    class UserInfoBuilder {
    public:
        UserInfoBuilder();
        UserInfoBuilder& set_name(QString name);
        UserInfoBuilder& set_email(QString email);
        UserInfoBuilder& set_phone_number(QString phone);
        UserInfoBuilder& set_avatar(QString path);
        std::unique_ptr<UserInfo> build();
        static std::unique_ptr<UserInfo> fromJson(
            const QString jsonString);

    private:
        std::unique_ptr<UserInfo> internal_info;
    };

    const QString& get_name() const;
    const QString& get_email() const;
    const QString& get_phone_number() const;
    const QString& get_avatar() const;
    void set_avator(const QString& av_path);
    void set_name(const QString& name);
    void set_email(const QString& email);
    void set_phone(const QString& phone);
    QString serialized() const;

    UserInfo(const UserInfo&) = delete;
    UserInfo& operator=(const UserInfo&) = delete;
    ~UserInfo() = default;

private:
    friend class UserInfoBuilder;
    UserInfo() = default;

    QString name;
    QString phone_number;
    QString email;
    QString av_path;
};

#endif // USERINFO_H
