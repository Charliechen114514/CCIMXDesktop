#include <QLabel>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QScreen>
#include <QTimer>
#include "desktoptoast.h"

DesktopToast::DesktopToast(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    label = new QLabel(this);
    setStyleSheet(
        "QLabel {"
        "background: qlineargradient(spread:pad, "
        "x1:0, y1:0, x2:1, y2:1, "
        "stop:0 rgba(250, 250, 250, 100), "
        "stop:1 rgba(230, 230, 230, 100));"
        "border-radius: 10px;"
        "}"
    );

    connect(this, &DesktopToast::do_show_toast,
            this, &DesktopToast::set_message_impl);
}

void DesktopToast::start_animation()
{
    show();
    if(moveAnimation){
        moveAnimation->stop();
        moveAnimation->deleteLater();
    }

    moveAnimation = new QPropertyAnimation(this, "pos");
    moveAnimation->setDuration(animation_maintain_msec);
    moveAnimation->setStartValue(startPos);
    moveAnimation->setEndValue(endPos);
    moveAnimation->setEasingCurve(QEasingCurve::OutCubic);
    moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void DesktopToast::start_close_animation()
{
    show();

    if(fadeAnimation){
        fadeAnimation->stop();
        fadeAnimation->deleteLater();
    }
    fadeAnimation = new QPropertyAnimation(this, "pos");
    fadeAnimation->setDuration(animation_maintain_msec);
    fadeAnimation->setStartValue(endPos);
    fadeAnimation->setEndValue(startPos);
    connect(fadeAnimation, &QPropertyAnimation::finished, this, [this]() {
        isHandling = false;
        hide();

        /* see if there are still some issue to be solved */
        if(!pools.isEmpty()){
            isHandling = true;
            QString msg = pools.dequeue();
            emit do_show_toast(msg);
        }
    });

    fadeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void DesktopToast::adjust_place()
{
    QWidget* referenceWidget = parentWidget();
    if (referenceWidget) {
        QRect parentRect = referenceWidget->rect();
        QPoint topCenter(parentRect.width() / 2 - width() / 2, 30);
        endPos = referenceWidget->mapToGlobal(topCenter);
    } else {
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
        QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
#else
        QRect screenGeometry = QApplication::desktop()->availableGeometry();
#endif
        int screenWidth = screenGeometry.width();
        int screenX = screenGeometry.x();
        QPoint topCenter(screenX + (screenWidth - width()) / 2, screenGeometry.top() + 30);
        endPos = topCenter;
    }

    startPos = QPoint(endPos.x(), endPos.y() - 70);
    move(startPos);
}

void DesktopToast::set_message(const QString& message)
{
    pools.enqueue(message);
    if(!isHandling){
        isHandling = true;
        QString msg = pools.dequeue();
        emit do_show_toast(msg);
    }
}

void DesktopToast::set_message_impl(const QString& message)
{
    label->setText(message);
    label->adjustSize();
    resize(label->size());
    adjust_place();
    show();
    raise();
    start_animation();
    QTimer::singleShot(wait_time + animation_maintain_msec, this, &DesktopToast::start_close_animation); // 2秒后关闭
}
