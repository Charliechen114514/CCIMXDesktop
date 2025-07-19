#include "HomeCardManager.h"
#include <QMutex>
#include <QStackedWidget>
#include <stdexcept>
HomeCardManager::HomeCardManager(QStackedWidget* widget)
    : stacked_widget(widget) {
    if (!widget) {
        throw std::invalid_argument("Widget Holding can not be null!");
    }
    mutex = std::make_shared<QMutex>();
}

void HomeCardManager::installWidget(QWidget* widget) {
    QMutexLocker<QMutex> locker(mutex.get());
    widget->setParent(stacked_widget);
    stacked_widget->addWidget(widget);
}

void HomeCardManager::removeWidget(QWidget* widget) {
    QMutexLocker<QMutex> locker(mutex.get());
    stacked_widget->removeWidget(widget);
}

int HomeCardManager::accessible_card_cnt() const {
    return stacked_widget->count();
}
