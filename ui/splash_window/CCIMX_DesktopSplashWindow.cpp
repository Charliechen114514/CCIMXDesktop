#include "CCIMX_DesktopSplashWindow.h"
#include "desktopmainwindow.h"
#include <QPainter>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QTimer>
CCIMX_DesktopSplashWindow::CCIMX_DesktopSplashWindow(DesktopMainWindow* holdingWindow)
    : QSplashScreen(QPixmap(":/splash_sources/sources/CCIMXDesktopLogo.png").scaled(QSize(1024, 600)))
    , holdingWindow(holdingWindow)
    , progressBar(new QProgressBar(this)) {
    progressBar->setGeometry(50, 600 - 90, 1024 - 100, 20);
    progressBar->setRange(0, 100);
    connect(holdingWindow, &DesktopMainWindow::updateProgress,
            this, &CCIMX_DesktopSplashWindow::handle_accessment);
}

void CCIMX_DesktopSplashWindow::close() {
    QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(500);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    connect(anim, &QPropertyAnimation::finished, this, &QSplashScreen::close);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void CCIMX_DesktopSplashWindow::handle_accessment(const QString& message, const int value) {
    showMessage(message, Qt::AlignLeft | Qt::AlignCenter, Qt::white);
    progressBar->setValue(value);
    this->progressValue = value;
    repaint();
}

void CCIMX_DesktopSplashWindow::drawContents(QPainter* painter) {
    // QSplashScreen::drawContents(painter);
    QFont font = painter->font();
    font.setPointSize(22); // 设置更大的字体
    font.setBold(true);
    painter->setFont(font);

    painter->setPen(Qt::white);
    QString message = this->message();
    QRect rect = this->rect();
    QRect textRect(rect.left() + 50, rect.bottom() - 120, rect.width() - 100, 30);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, message);

    QString percentStr = QString("%1%").arg(progressValue);
    QRect percentRect(rect.right() - 100, rect.bottom() - 120, 80, 30);
    painter->drawText(percentRect, Qt::AlignRight | Qt::AlignVCenter, percentStr);
}
