#include "UserInfoCard.h"
#include <QGraphicsDropShadowEffect>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>

UserInfoCard::UserInfoCard(QWidget* parent)
    : QWidget(parent)
    , avatarLabel(new QLabel(this))
    , nameLabel(new QLabel(this))
    , phoneLabel(new QLabel(this))
    , emailLabel(new QLabel(this)) {

    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(false);
    setObjectName("UserInfoCard");

    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(0, 0, 0, 80));
    setGraphicsEffect(shadow);

    avatarLabel->setFixedSize(72, 72);
    avatarLabel->setScaledContents(true);

    setStyleSheet(R"(
        #UserInfoCard {
            border-radius: 20px;
            background: qlineargradient(
                x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #43e97b,
                stop: 1 #38f9d7
            );
        }
    )");

    nameLabel->setStyleSheet("color: white; font-size: 42px; font-weight: bold; font-family: 'Segoe UI';");
    phoneLabel->setStyleSheet("color: white; font-size: 24px;");
    emailLabel->setStyleSheet("color: white; font-size: 24px;");

    auto phoneLayout = new QHBoxLayout;
    auto phoneIcon = new QLabel(this);
    phoneIcon->setPixmap(QPixmap(":/avator/sources/avatar/phone.png").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    phoneLayout->addWidget(phoneIcon);
    phoneLayout->addSpacing(6);
    phoneLayout->addWidget(phoneLabel);
    phoneLayout->addStretch();

    auto emailLayout = new QHBoxLayout;
    auto emailIcon = new QLabel(this);
    emailIcon->setPixmap(QPixmap(":/avator/sources/avatar/email.png").scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    emailLayout->addWidget(emailIcon);
    emailLayout->addSpacing(6);
    emailLayout->addWidget(emailLabel);
    emailLayout->addStretch();

    auto nameLayout = new QHBoxLayout;
    auto nameIcon = new QLabel(this);
    nameIcon->setPixmap(QPixmap(":/avator/sources/avatar/name.png").scaled(54, 54, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    nameLayout->addWidget(nameIcon);
    nameLayout->addSpacing(6);
    nameLayout->addWidget(nameLabel);
    nameLayout->addStretch();

    QVBoxLayout* infoLayout = new QVBoxLayout;
    infoLayout->addLayout(phoneLayout);
    infoLayout->addLayout(nameLayout);
    infoLayout->addLayout(emailLayout);
    infoLayout->setSpacing(8);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(avatarLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(infoLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void UserInfoCard::setUserInfo(const UserInfo& info) {
    nameLabel->setText(info.get_name());
    phoneLabel->setText(info.get_phone_number());
    emailLabel->setText(info.get_email());
    avatarLabel->setPixmap(QPixmap(info.get_avatar()).scaled(72, 72, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
}

void UserInfoCard::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
    gradient.setColorAt(0, QColor(0x43e97b));
    gradient.setColorAt(1, QColor(0x38f9d7));
    painter.setBrush(gradient);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 20, 20);

    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
