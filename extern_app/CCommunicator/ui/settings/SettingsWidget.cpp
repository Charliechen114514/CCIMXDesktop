#include "SettingsWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
SettingsWidget::SettingsWidget(QWidget* parent)
    : QWidget { parent } {
    auto* root = new QVBoxLayout(this);
    root->setContentsMargins(20, 20, 20, 20);
    root->setSpacing(16);

    QLabel* titleLabel = new QLabel("⚙ Settings ⚙", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size:44px; font-weight:600;");
    titleLabel->setMaximumHeight(100);
    root->addWidget(titleLabel, 0, Qt::AlignHCenter);
    auto* nickNameLayout = new QHBoxLayout(this);
    QLabel* nickNameLabel = new QLabel("NickName: ", this);
    nickNameLabel->setAlignment(Qt::AlignCenter);
    nickNameLayout->addWidget(nickNameLabel);
    nickNameEdit = new QLineEdit(this);
    connect(nickNameEdit, &QLineEdit::returnPressed,
            this, &SettingsWidget::auth_new_nickname);
    nickNameLayout->addWidget(nickNameEdit);
    nickNameLabel->setMinimumHeight(70);
    nickNameEdit->setMinimumHeight(70);
    nickNameLayout->addStretch();
    root->addLayout(nickNameLayout);
    root->addStretch();
}

void SettingsWidget::register_localInfo(const SessionInfo& session) {
    this->holding_info = session;
    nickNameEdit->setPlaceholderText(session.nickName);
}

void SettingsWidget::auth_new_nickname() {
    QString newNickName = nickNameEdit->text();
    if (holding_info.nickName == newNickName) {
        qWarning() << "Same name, dont change!";
        return;
    }
    qDebug() << "Auth Success: " << newNickName;
    holding_info.nickName = newNickName;
    emit nickNameChanged(newNickName);
}
