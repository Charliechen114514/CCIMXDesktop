#include "DateShowCard.h"
#include <QDate>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QVBoxLayout>
DateShowCard::DateShowCard(QWidget* parent)
    : QWidget { parent } {
    setObjectName("DateCardWidget");
    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);

    titleLabel = new QLabel(this);
    titleLabel->setAlignment(Qt::AlignCenter);

    dayLabel = new QLabel(this);
    dayLabel->setAlignment(Qt::AlignCenter);

    fullTextLabel = new QLabel(this);
    fullTextLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(dayLabel);
    layout->addWidget(fullTextLabel);
    layout->setSpacing(6);
    layout->setContentsMargins(12, 12, 12, 12);

    setLayout(layout);

    // 样式表
    setStyleSheet(R"(
        #DateCardWidget {
            border-radius: 20px;
            background: qlineargradient(
                x1: 0, y1: 0, x2: 0, y2: 1,
                stop: 0 #4A90E2,
                stop: 1 #1E3C72
            );
        }
        QLabel {
            color: white;
        }
    )");

    titleLabel->setStyleSheet("font-size: 32px;");
    dayLabel->setStyleSheet("font-size: 48px; font-weight: bold;");
    fullTextLabel->setStyleSheet("font-size: 16px;");

    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(16);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);
    int day = QDate::currentDate().day();
    setDate(day, QDate::currentDate().toString("MM/dd ddd"), "Date Today");
}

void DateShowCard::setDate(int dayOfMonth, const QString& fullDateText, const QString& title) {
    dayLabel->setText(QString::number(dayOfMonth));
    fullTextLabel->setText(fullDateText);
    titleLabel->setText(title);
}
