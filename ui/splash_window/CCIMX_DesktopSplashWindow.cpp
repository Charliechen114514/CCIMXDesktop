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
    auto pixmap = QSplashScreen::pixmap();
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
    repaint();
}

void CCIMX_DesktopSplashWindow::drawContents(QPainter* painter) {
    QSplashScreen::drawContents(painter);
}
