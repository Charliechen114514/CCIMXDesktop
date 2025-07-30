#ifndef COMMUNICATEMAINWINDOW_H
#define COMMUNICATEMAINWINDOW_H
#include "core/sessions/SessionInfo.h"
#include "ui/ToolSide/ToolsEnum.h"
#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class CommunicateMainWindow;
}
QT_END_NAMESPACE
class PeerConnection;
class SessionHub;
class InfoWidget;
class Session;
class HistoryManagerSchedular;
class SettingsWidget;
class CommunicateMainWindow : public QMainWindow {
	Q_OBJECT

public:
    CommunicateMainWindow(QWidget* parent = nullptr);
	~CommunicateMainWindow();

private slots:
    void onContactChanged(Session* session);
    void onSend(const QString& text);
    void switch_page(ToolsEnums::Functionality enumType);
    void process_new_connections(const QString& name, const QString& ip, const int port);

    void process_session_ready(Session* s, const SessionInfo& sessionInfo);
    void process_text_received(Session* s, const QString& text);

private:
    void init_message_page();
    void init_self_page();
    void init_settings_page();
    void init_connector_page();
    void init_history_manager();
    void init_session_hubs();
    std::vector<int> collect_activate_ports();
    Ui::CommunicateMainWindow* ui;
    QPixmap pixmap;
    QMap<ToolsEnums::Functionality, QWidget*> router;
    InfoWidget* info_page;
    SettingsWidget* settings_widget;
    SessionInfo local_info;
    SessionHub* sessionHub;
    HistoryManagerSchedular* history_manager;
};
#endif // COMMUNICATEMAINWINDOW_H
