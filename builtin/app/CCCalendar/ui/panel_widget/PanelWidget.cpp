#include "PanelWidget.h"
#include <QEvent>
#include <QPropertyAnimation>
PanelWidget::PanelWidget(QWidget* parent)
    : QWidget { parent } {
    animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);

    setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose, false);
    parent->installEventFilter(this);
}

void PanelWidget::updatePosition() {
    if (!parentWidget())
        return;

    QRect parentRect = parentWidget()->geometry();
    QRect targetRect(0, 0, width(), parentRect.height());

    if (isVisible() && !isSlidingIn) {
        setGeometry(targetRect);
    } else {
        setGeometry(targetRect.translated(-width(), 0));
    }
}

bool PanelWidget::eventFilter(QObject* watched, QEvent* event) {
    if (watched == parentWidget() && (event->type() == QEvent::Move || event->type() == QEvent::Resize)) {
        updatePosition();
    }
    return QWidget::eventFilter(watched, event);
}

void PanelWidget::slideIn() {
    isSlidingIn = true;

    updatePosition();
    show();
    raise();

    animation->stop();
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(0, 0, width(), height()));

    disconnect(animation, &QPropertyAnimation::finished, this, &PanelWidget::closePanel);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        isSlidingIn = false;
    });
}

void PanelWidget::slideOut() {
    animation->stop();
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(-width(), 0, width(), height()));
    connect(animation, &QPropertyAnimation::finished, this, &PanelWidget::closePanel);
    animation->start();
}

void PanelWidget::closePanel() {
    disconnect(animation, &QPropertyAnimation::finished, this, &PanelWidget::closePanel);
    hide();
}
