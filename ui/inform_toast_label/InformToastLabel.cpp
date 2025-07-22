#include "InformToastLabel.h"
#include "ui_InformToastLabel.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
InformToastLabel::InformToastLabel(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::InformToastLabel) {
	ui->setupUi(this);
    setStyleSheet(R"(
    QLabel {
        background-color: transparent;
    }

    QLabel#title_label {
        color: #FFFFFF;
        font-weight: bold;
        font-size: 16px;
    }

    QLabel#content_label {
        color: #D0E7FF;  /* 柔和的淡蓝 */
        font-size: 14px;
    }

    QLabel#icon_label {
        background-color: transparent;
    }
    )");
    setAutoFillBackground(false);
    setAttribute(Qt::WA_TranslucentBackground);

    auto effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setOffset(0, 4);
    effect->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(effect);
}

InformToastLabel::~InformToastLabel() {
	delete ui;
}

void InformToastLabel::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRectF rect = this->rect();
    QLinearGradient gradient(rect.topLeft(), rect.bottomLeft());
    gradient.setColorAt(0, QColor(60, 60, 60, 200));
    gradient.setColorAt(1, QColor(100, 100, 100, 200));

    QBrush brush(gradient);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect.adjusted(0, 0, -1, -1), 12, 12);
}

void InformToastLabel::setTitle(const QString& title) {
    ui->title_label->setText(title);
}

void InformToastLabel::setText(const QString& text) {
    ui->content_label->setText(text);
}

void InformToastLabel::setIcon(const QString& icons) {
    ui->icon_label->setPixmap(QPixmap(icons).scaled(ui->icon_label->size(), Qt::KeepAspectRatio));
}
