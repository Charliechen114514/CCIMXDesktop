#include "ToastMetaProtocol.h"
#include <QJsonDocument>
#include <QJsonObject>

ToastMetaProtocol::ToastMetaProtocol(
    const QString meta_app,
    const QString displayMessage,
    const QDateTime t)
    : meta_appName(meta_app)
    , announceTime(t)
    , meta_displayMessage(displayMessage) {
}

ToastMetaProtocol::ToastMetaProtocol(const QString& json_string) {
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json_string.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qCritical() << "Error while parsing json file: " << error.errorString();
        return;
    }
    QJsonObject obj = doc.object();
    meta_appName = obj["meta_appName"].toString();
    announceTime = QDateTime::fromString(obj["announceTime"].toString(), Qt::ISODate);
    meta_displayMessage = obj["meta_displayMessage"].toString();
}

std::optional<ToastMetaProtocol> ToastMetaProtocol::from_json_string(const QString& json_string) {
    ToastMetaProtocol toast;
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json_string.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qCritical() << "Error while parsing json file: " << error.errorString();
        return {};
    }
    QJsonObject obj = doc.object();
    toast.meta_appName = obj["meta_appName"].toString();
    toast.announceTime = QDateTime::fromString(obj["announceTime"].toString(), Qt::ISODate);
    toast.meta_displayMessage = obj["meta_displayMessage"].toString();
    return toast;
}

QString ToastMetaProtocol::toString() const {
    QJsonObject obj;
    obj["meta_appName"] = meta_appName;
    obj["announceTime"] = announceTime.toString(Qt::ISODate);
    obj["meta_displayMessage"] = meta_displayMessage;
    return QJsonDocument(obj).toJson(QJsonDocument::Indented);
}
