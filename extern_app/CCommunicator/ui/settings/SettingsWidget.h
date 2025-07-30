#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H
#include "core/sessions/SessionInfo.h"
#include <QWidget>
class QLineEdit;

class SettingsWidget : public QWidget {
	Q_OBJECT
public:
    explicit SettingsWidget(QWidget* parent = nullptr);
    void register_localInfo(const SessionInfo& session);

signals:
    void nickNameChanged(const QString& newNickName);
private slots:
    void auth_new_nickname();

private:
    SessionInfo holding_info;
    QLineEdit* nickNameEdit;
};

#endif // SETTINGSWIDGET_H
