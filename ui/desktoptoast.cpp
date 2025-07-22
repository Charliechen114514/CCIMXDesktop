#include "desktoptoast.h"
#include "inform_toast_label/InformToastLabel.h"
#include <QGuiApplication>
#include <QLabel>
#include <QPropertyAnimation>
#include <QScreen>
#include <QTimer>
#include <QVBoxLayout>
namespace {

QSize get_size(InformToastLabel* label, const QString& message, const int width) {
    const int maxWidth = width;
    int height = label->height();
    return QSize(maxWidth, height);
}

}

DesktopToast::DesktopToast(QWidget* parent)
    : QWidget { parent } {
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
    label = new InformToastLabel(this);
    label->setMinimumWidth(400);
    moveAnimation = new QPropertyAnimation(this, "pos");
    fadeAnimation = new QPropertyAnimation(this, "pos");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    setLayout(layout);


    connect(fadeAnimation, &QPropertyAnimation::finished, this, [this]() {
        isHandling = false;
        hide();

        /* see if there are still some issue to be solved */
        QMutexLocker locker(&queue_mutex);
        if (!pools.isEmpty()) {
            isHandling = true;
            QString msg = pools.dequeue();
            emit do_show_toast(msg);
        }
    });
    connect(this, &DesktopToast::do_show_toast,
            this, &DesktopToast::set_message_impl);
}

void DesktopToast::start_animation() {
    show();
    moveAnimation->stop();
    moveAnimation->setDuration(animation_maintain_msec);
    moveAnimation->setStartValue(startPos);
    moveAnimation->setEndValue(endPos);
    moveAnimation->setEasingCurve(QEasingCurve::OutCubic);
    moveAnimation->start();
}

void DesktopToast::start_close_animation() {
    show();
    fadeAnimation->stop();
    fadeAnimation->setDuration(animation_maintain_msec);
    fadeAnimation->setStartValue(endPos);
    fadeAnimation->setEndValue(startPos);
    fadeAnimation->start();
}

void DesktopToast::set_message(const QString& message) {
    // lock to prevent the enqueue race condition
    QMutexLocker locker(&queue_mutex);
    pools.enqueue(message);
    if (!isHandling) {
        isHandling = true;
        QString msg = pools.dequeue();
        emit do_show_toast(msg);
    }
    // lock ends
}

void DesktopToast::setWidth(const int width) {
    this->_width = width;
}

void DesktopToast::adjust_place() {
    QWidget* referenceWidget = parentWidget();
    if (referenceWidget) {
        QRect parentRect = referenceWidget->rect();
        QPoint topCenter((parentRect.width() - label->width()) / 2, 30);
        endPos = referenceWidget->mapToGlobal(topCenter);
    } else {
/* do the stuff according Qt Versions */
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
        QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
#else
        QRect screenGeometry = QApplication::desktop()->availableGeometry();
#endif
        int screenWidth = screenGeometry.width();
        int screenX = screenGeometry.x();
        QPoint topCenter(screenX + (screenWidth - label->width()) / 2, screenGeometry.top() + 30);
        endPos = topCenter;
    }

    startPos = QPoint(endPos.x(), endPos.y() - label->height());
    move(startPos);
}

void DesktopToast::set_message_impl(const QString& message) {
    label->setText(message);
    label->adjustSize();
    adjustSize();
    adjust_place();
    // qDebug() << "[Toast] label sizeHint:" << label->sizeHint();
    // qDebug() << "[Toast] actual label size:" << label->size();
    // qDebug() << "[Toast] Toast size:" << size();
    // qDebug() << "[Toast] startPos:" << startPos << "endPos:" << endPos;
    show();
    raise();
    start_animation();
    QTimer::singleShot(wait_time + animation_maintain_msec, this, &DesktopToast::start_close_animation);
}
