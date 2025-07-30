#include "CommunicateMainWindow.h"
#include "NetInfo.h"
#include "core/historyContainers/HistoryContainers.h"
#include "core/sessions/Session.h"
#include "core/sessions/SessionHub.h"
#include "settings/SettingsWidget.h"
#include "ui/communication_main/HistoryManagerSchedular.h"
#include "ui/connectors/ConnectorsWidget.h"
#include "ui/selfInfo/InfoWidget.h"
#include "ui_CommunicateMainWindow.h"

CommunicateMainWindow::CommunicateMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::CommunicateMainWindow) {
	ui->setupUi(this);
    resize(1200, 760);
    connect(ui->toolbars, &ToolPanel::function_activate,
            this, &CommunicateMainWindow::switch_page);
    local_info.nickName = "Charlie";
    init_session_hubs();
    init_history_manager();
    init_message_page();
    init_self_page();
    init_connector_page();
    init_settings_page();

    sessionHub->passiveSessionListen();
}

void CommunicateMainWindow::init_message_page() {
    router.insert(ToolsEnums::Functionality::MESSAGE,
                  ui->message_main_page);
    ui->chatMainPanel->setEditWidgetEditable(false);
    connect(ui->chatListPanel, &ChatListPanel::currentContactChanged, this,
            &CommunicateMainWindow::onContactChanged);
    connect(ui->chatMainPanel, &ChatMainPanel::sendMessage,
            this, &CommunicateMainWindow::onSend);
}

void CommunicateMainWindow::init_self_page() {
    info_page = new InfoWidget(this);
    router.insert(ToolsEnums::Functionality::MINE,
                  info_page);
    ui->stackedWidget->addWidget(info_page);
    connect(sessionHub, &SessionHub::next_available_port,
            info_page, &InfoWidget::show_current_port);
}

void CommunicateMainWindow::init_settings_page() {
    settings_widget = new SettingsWidget(this);
    settings_widget->register_localInfo(local_info);
    router.insert(ToolsEnums::Functionality::SETTINGS,
                  settings_widget);
    ui->stackedWidget->addWidget(settings_widget);
    connect(settings_widget, &SettingsWidget::nickNameChanged,
            this, [this](const QString& name) {
                local_info.nickName = name;
            });
}

void CommunicateMainWindow::init_connector_page() {
    ConnectorsWidget* cList = new ConnectorsWidget(this);
    ui->stackedWidget->addWidget(cList);
    router.insert(ToolsEnums::Functionality::CONNECTORS,
                  cList);
    connect(cList, &ConnectorsWidget::contactClicked,
            this, [&](const QString& name, const QPixmap& avatar) {
                qInfo() << "选中联系人:" << name;
            });
    connect(cList, &ConnectorsWidget::request_new_connections,
            this, &CommunicateMainWindow::process_new_connections);
}

void CommunicateMainWindow::init_history_manager() {
    history_manager = new HistoryManagerSchedular(this);
}

void CommunicateMainWindow::init_session_hubs() {
    sessionHub = new SessionHub(local_info, this);
    connect(sessionHub, &SessionHub::sessionReady, this,
            &CommunicateMainWindow::process_session_ready);

    connect(sessionHub, &SessionHub::textReceived, this,
            &CommunicateMainWindow::process_text_received);
}

void CommunicateMainWindow::onContactChanged(Session* session) {
    auto info = ui->chatListPanel->request_info(session);

    ui->chatMainPanel->setTitle(info.get_markable_name());
    ui->chatMainPanel->setSessionID(session->sessionID());
    qDebug() << "Loading the histories";
    history_manager->load_history(session, ui->chatMainPanel);
}

void CommunicateMainWindow::onSend(const QString& text) {
    ui->chatMainPanel->appendMessage(text, true, pixmap);
    QString id = ui->chatMainPanel->getCurrentSessionID();
    Session* send_to = sessionHub->queryFromUuid(id);

    auto history = history_manager->queryHistory(send_to);
    if (!history) {
        qCritical() << "Can not resume history! all communications will not be resumed!";
    } else {
        history->enQueueMessage(text, true, MetaMessages::AcceptableType::PlainMessage);
    }

    if (send_to) {
        send_to->sendText(text);
        qInfo() << "Send OK";
    } else {
        qCritical() << "Unfind! connections!";
    }
}

void CommunicateMainWindow::switch_page(ToolsEnums::Functionality enumType) {
    auto widget_page = router.value(enumType);
    if (widget_page) {
        ui->stackedWidget->setCurrentWidget(widget_page);
    } else {
        qCritical() << "Disabled functionalities or page unfind...";
    }
}

void CommunicateMainWindow::process_session_ready(Session* s, const SessionInfo& sessionInfo) {
    QString name = sessionInfo.nickName;
    qInfo() << "Ok Connected" << ", With name!"
            << name << ", target connection port" << s->peerInfo().second;
    history_manager->createHistorySession(s);
    ui->chatListPanel->append_context(s, { name, s->sessionID(), "Hello!", QDateTime::currentDateTime(), 1 });
    ui->chatMainPanel->setCommunicateStatus(CommunicatableStatus::ONLINE);
    ui->chatMainPanel->setEditWidgetEditable(true);
    ui->chatMainPanel->setTitle(name);
    ui->chatMainPanel->setSessionID(s->sessionID());
    ui->chatMainPanel->appendMessage("Hello", false, QPixmap());
}

void CommunicateMainWindow::process_text_received(Session* s, const QString& text) {
    auto history = history_manager->queryHistory(s);
    if (!history) {
        qCritical() << "Can not resume history! all communications will not be resumed!";
    } else {
        history->enQueueMessage(text, false, MetaMessages::AcceptableType::PlainMessage);
    }
    ui->chatMainPanel->appendMessage(text, false, pixmap);
}

void CommunicateMainWindow::process_new_connections(const QString& name, const QString& ip, const int port) {
    qDebug() << "UI has requested for connection positive: " << ip << " " << port;
    PeerInfo info;
    info.host_address = ip;
    info.target_port = port;
    sessionHub->createSessionActive(local_info, info);
}

CommunicateMainWindow::~CommunicateMainWindow() {
	delete ui;
}
