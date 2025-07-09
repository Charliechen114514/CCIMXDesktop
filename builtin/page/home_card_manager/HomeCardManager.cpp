#include "HomeCardManager.h"
#include <QStackedWidget>
#include <stdexcept>
HomeCardManager::HomeCardManager(QStackedWidget* widget)
    : stacked_widget(widget) {
    if (!widget) {
        throw std::invalid_argument("Widget Holding can not be null!");
    }
}

void HomeCardManager::installWidget(QWidget* widget) {
    stacked_widget->addWidget(widget);
}

void HomeCardManager::removeWidget(QWidget* widget) {
    stacked_widget->removeWidget(widget);
}

int HomeCardManager::accessible_card_cnt() const {
    return stacked_widget->count();
}
