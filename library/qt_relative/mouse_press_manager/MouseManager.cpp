#include "MouseManager.h"
#include "MouseProcessor.h"
#include "MouseRecorder.h"

#include <QDebug>
MouseManager::MouseManager()
    : recorder(new MouseRecorder) {
}

MouseManager::~MouseManager() = default;

void MouseManager::
    register_processor(MouseProcessor* new_processor) {

    if (!new_processor) {
        throw std::invalid_argument("Can not accept null processor");
    }
    processor_recorders.emplaceBack(std::move(new_processor));

    if (!head_processor) {
        head_processor = new_processor;
    } else {
        // set the end session
        MouseProcessor* current = head_processor;
        while (current->next()) {
            current = current->next();
        }
        current->setNext(new_processor);
    }
}

void MouseManager::install_mousepoint(const QPoint& point, PointType pointType) {
    switch (pointType) {
    case PointType::Press:
        recorder->press = point;
        break;
    case PointType::Release:
        recorder->release = point;
        break;
    }
}

void MouseManager::install_mousepoint(QPoint&& point, PointType pointType) {
    switch (pointType) {
    case PointType::Press:
        recorder->press = std::move(point);
        break;
    case PointType::Release:
        recorder->release = std::move(point);
        break;
    }
}

bool MouseManager::run_processor() {
    if (!head_processor) {
        qCritical() << "No processor is registered, manager do nothing!";
        return false;
    }

    bool isHandled = head_processor->try_and_process(recorder.get());
    if (!isHandled) {
        qCritical() << "Current Chain failed to process the events!";
    } else {
        qDebug() << "Ok, event is processed!";
    }

    return isHandled;
}
