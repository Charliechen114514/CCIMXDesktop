#include "CCIMX_DesktopSplashWindow.h"
#include <QPainter>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QTimer>
CCIMX_DesktopSplashWindow::CCIMX_DesktopSplashWindow()
    : QSplashScreen(QPixmap(":/splash_sources/sources/CCIMXDesktopLogo.png").scaled(QSize(1024, 600)))
    , progressBar(new QProgressBar(this)) {
    progressBar->setRange(0, 100);
    progressBar->setTextVisible(false);
    progressBar->setStyleSheet(R"(
        QProgressBar {
            background-color: #222;
            border-radius: 5px;
        }
        QProgressBar::chunk {
            background-color: #00aaff;
            border-radius: 5px;
        })");
    int barWidth = this->width() - 100;
    int barHeight = 30;
    progressBar->setGeometry(50, this->height() - 60,
                             barWidth, barHeight);
}

void CCIMX_DesktopSplashWindow::close() {
    QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(CLOSE_DURATION);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::InOutQuad);
    connect(anim, &QPropertyAnimation::finished, this, &QSplashScreen::close);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void CCIMX_DesktopSplashWindow::handle_accessment(const QString& message, const int value) {
    currentMessage = message;
    if (progressAnim) {
        progressAnim->stop();
        delete progressAnim;
    }

    progressAnim = new QPropertyAnimation(progressBar, "value", this);
    progressAnim->setDuration(2000);
    progressAnim->setStartValue(progressValue);
    progressAnim->setEndValue(value);
    progressAnim->setEasingCurve(QEasingCurve::InOutCubic);
    progressAnim->start(QAbstractAnimation::DeleteWhenStopped);

    progressValue = value;
    this->showMessage(message, Qt::AlignLeft | Qt::AlignBottom, Qt::white);
    repaint();
}

void CCIMX_DesktopSplashWindow::drawContents(QPainter* painter) {
    QFont font;
    font.setPointSizeF(this->height() / 28.0);
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(Qt::white);

    QRect rect = this->rect();
    QFontMetrics fm(font);

    int maxTextWidth = rect.width() - 150;
    QRect messageRect(rect.left() + 50, rect.bottom() - 120, maxTextWidth, 0); // 高度设0，用于计算

    QString elidedMessage = fm.elidedText(currentMessage, Qt::ElideRight, maxTextWidth);
    QRect bounded = fm.boundingRect(messageRect, Qt::TextWordWrap, elidedMessage);
    messageRect.setHeight(bounded.height());

    painter->drawText(messageRect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap, elidedMessage);

    // 百分比仍右对齐
    QRect percentRect(rect.right() - 100, rect.bottom() - 120, 80, 30);
    painter->drawText(percentRect, Qt::AlignRight | Qt::AlignVCenter, QString("%1%").arg(progressValue));
}
