#ifndef TOASTMETAPROTOCOL_H
#define TOASTMETAPROTOCOL_H

#include <QString>
#include <QTime>
struct ToastMetaProtocol {
    QString meta_appName;
    QDateTime announceTime;
    QString meta_displayMessage;
    ToastMetaProtocol() = default;
    ToastMetaProtocol(const QString meta_app, const QString displayMessage, const QDateTime t = QDateTime::currentDateTime());
    ToastMetaProtocol(const QString& json_string);
    static std::optional<ToastMetaProtocol> from_json_string(const QString& json_string);
    QString toString() const;
};

#endif // TOASTMETAPROTOCOL_H
