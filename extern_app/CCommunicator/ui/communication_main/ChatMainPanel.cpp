#include "ChatMainPanel.h"
#include "ChatBubble.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>
namespace {
QToolButton* addIconBtn(const QString& btn_text, QWidget* parent, QLayout* layout) {
    auto* b = new QToolButton(parent);
    b->setText(btn_text);
    b->setAutoRaise(true);
    layout->addWidget(b);
    return b;
}
}

ChatMainPanel::ChatMainPanel(QWidget* parent)
    : QWidget { parent } {
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(0, 0, 0, 0);
    root->setSpacing(0);
    setLayout(root);
    // header init
    init_header();
    // init list widgets
    // message area
    init_message_shown();
    // toolbar + input
    init_input_widegt();
}

void ChatMainPanel::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    adjustBubbleWidths();
}

void ChatMainPanel::adjustBubbleWidths() {
    // 可根据你的 padding 或者滚动条宽度做微调
    int w = listWidget->viewport()->width();
    for (int i = 0; i < listWidget->count(); ++i) {
        auto* item = listWidget->item(i);
        auto* bubble = qobject_cast<ChatBubble*>(listWidget->itemWidget(item));
        if (!bubble)
            continue;
        bubble->setFixedWidth(w);
        item->setSizeHint(bubble->sizeHint());
    }
}

void ChatMainPanel::appendMessage(const QString& text, bool me, QPixmap avatar) {
    auto* item = new QListWidgetItem;
    auto* bubble = new ChatBubble(text, me, avatar, this);
    item->setSizeHint(bubble->sizeHint());
    bubble->setFixedWidth(listWidget->viewport()->width());
    listWidget->addItem(item);
    listWidget->setItemWidget(item, bubble);
    listWidget->scrollToBottom();
}

void ChatMainPanel::setTitle(const QString& title) {
    this->title->setText(title);
}

QString ChatMainPanel::getTitle() const {
    return title->text();
}

QString ChatMainPanel::getCurrentSessionID() const {
    return session_id;
}

void ChatMainPanel::clearShownMessages() {
    listWidget->clear();
}

void ChatMainPanel::setCommunicateStatus(CommunicatableStatus communicatable) {
    const char* status_stylesheet = nullptr;
    const char* status_text = nullptr;

    switch (communicatable) {
    case CommunicatableStatus::ONLINE:
        status_stylesheet = "background:#2ecc71;"
                            "border-radius:5px;";
        status_text = "Online";
        break;
    case CommunicatableStatus::OFFLINE:
        status_stylesheet = "background:#e74c3c;"
                            "border-radius:5px;";
        status_text = "Offline";
        break;
    case CommunicatableStatus::WAITING:
        status_stylesheet = "background:#e74c3c;"
                            "border-radius:5px;";
        status_text = "Waiting";
        break;
    }

    dotStatus->setStyleSheet(status_stylesheet);
    statueIndicator->setText(status_text);

    if (communicatable != communicate_status) {
        communicate_status = communicatable;
        emit communicatableChanged(communicate_status);
    }
}

void ChatMainPanel::setEditWidgetEditable(bool editable) {
    input_widget->setEnabled(editable);
    input_widget->setVisible(editable);
}

bool ChatMainPanel::editWidgetEditable() const {
    return input_widget->isEnabled();
}

void ChatMainPanel::setSessionID(const QString& session_id) {
    this->session_id = session_id;
}

void ChatMainPanel::sendClicked() {
    QString text = editor->toPlainText().trimmed();
    if (text.isEmpty())
        return;
    emit sendMessage(text);
    editor->clear();
}

void ChatMainPanel::init_header() {
    auto* header = new QWidget;
    header->setFixedHeight(56);
    auto* hl = new QHBoxLayout(header);
    hl->setContentsMargins(16, 0, 16, 0);

    title = new QLabel(this);
    title->setStyleSheet("font-size:16px;"
                         "font-weight:600;");
    dotStatus = new QLabel(this);
    dotStatus->setFixedSize(10, 10);
    statueIndicator = new QLabel(this);
    statueIndicator->setStyleSheet("font-size:16px;"
                                   "font-weight:600;");
    setCommunicateStatus(CommunicatableStatus::OFFLINE);
    hl->addWidget(title);
    hl->addWidget(dotStatus, 0, Qt::AlignVCenter);
    hl->addWidget(statueIndicator, 1, Qt::AlignVCenter);
    hl->addStretch();

    for (const auto& each : HEADER_ICON) {
        addIconBtn(each, this, hl);
    }
    header->setStyleSheet("background:#FFFFFF;"
                          "border-bottom:1px solid #EDEDED;");
    layout()->addWidget(header);
}

void ChatMainPanel::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    QTimer::singleShot(0, this, &ChatMainPanel::adjustBubbleWidths);
}

void ChatMainPanel::init_message_shown() {
    listWidget = new QListWidget;
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setFrameShape(QFrame::NoFrame);
    listWidget->setStyleSheet("QListWidget{"
                              "background:#FFFFFF;"
                              "border:none;"
                              "} "
                              "QListWidget::item{"
                              "border:none;"
                              "}");
    listWidget->setSpacing(8);
    dynamic_cast<QVBoxLayout*>(layout())->addWidget(listWidget, 1);
}

void ChatMainPanel::init_input_widegt() {
    input_widget = new QWidget;
    auto* vb = new QVBoxLayout(input_widget);
    vb->setContentsMargins(12, 8, 12, 8);
    vb->setSpacing(6);

    auto* tools = new QHBoxLayout;
    for (const auto& each : TOOL_ICON) {
        addIconBtn(each, this, tools);
    }
    tools->addStretch();
    vb->addLayout(tools);

    editor = new QTextEdit;
    editor->setFixedHeight(100);
    editor->setPlaceholderText("输入消息...");
    vb->addWidget(editor);

    auto* sendLayout = new QHBoxLayout;
    sendLayout->addStretch();
    btn_send = new QPushButton("发送");
    btn_send->setFixedSize(80, 32);
    btn_send->setEnabled(true);
    sendLayout->addWidget(btn_send);
    vb->addLayout(sendLayout);

    layout()->addWidget(input_widget);
    input_widget->setStyleSheet("background:#FFFFFF;"
                                "border-top:1px solid #EDEDED;");

    connect(btn_send, &QPushButton::clicked, this,
            &ChatMainPanel::sendClicked);
}
