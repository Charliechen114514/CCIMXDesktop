#include "UserInfo.h"

UserInfo::UserInfoBuilder::UserInfoBuilder()
    : internal_info(std::unique_ptr<UserInfo>(new UserInfo)) { }

UserInfo::UserInfoBuilder& UserInfo::UserInfoBuilder::set_avatar(QString path) {
    internal_info->av_path = path;
    return *this;
}

UserInfo::UserInfoBuilder& UserInfo::UserInfoBuilder::set_name(QString name) {
    internal_info->name = std::move(name);
    return *this;
}

UserInfo::UserInfoBuilder& UserInfo::UserInfoBuilder::set_email(QString email) {
    internal_info->email = std::move(email);
    return *this;
}

UserInfo::UserInfoBuilder& UserInfo::UserInfoBuilder::set_phone_number(QString phone) {
    internal_info->phone_number = std::move(phone);
    return *this;
}

std::unique_ptr<UserInfo> UserInfo::UserInfoBuilder::build() {
    return std::move(internal_info);
}

const QString& UserInfo::get_name() const {
    return name;
}

const QString& UserInfo::get_email() const {
    return email;
}

const QString& UserInfo::get_phone_number() const {
    return phone_number;
}

const QString& UserInfo::get_avatar() const {
    return av_path;
}

void UserInfo::set_avator(const QString& av_path) {
    this->av_path = av_path;
}

void UserInfo::set_name(const QString& name) {
    this->name = name;
}

void UserInfo::set_email(const QString& email) {
    this->email = email;
}

void UserInfo::set_phone(const QString& phone) {
    this->phone_number = phone;
}

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

std::unique_ptr<UserInfo>
UserInfo::UserInfoBuilder::fromJson(const QString jsonString) {
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(jsonString.toLocal8Bit(), &error);

    if (error.error != QJsonParseError::NoError) {
        qCritical() << "Fuck Off when parsing the jsonString in user" << error.errorString();
        return nullptr;
    }
    std::unique_ptr<UserInfo> info(new UserInfo);

    QJsonObject obj = document.object();
    info->email = obj["email"].toString();
    info->phone_number = obj["phone_number"].toString();
    info->name = obj["name"].toString();
    info->av_path = obj["av_path"].toString();
    return std::move(info);
}

QString UserInfo::serialized() const {
    QJsonObject obj;
    obj["email"] = email;
    obj["phone_number"] = phone_number;
    obj["name"] = name;
    obj["av_path"] = av_path;
    return QJsonDocument(obj).toJson(QJsonDocument::Indented);
}
