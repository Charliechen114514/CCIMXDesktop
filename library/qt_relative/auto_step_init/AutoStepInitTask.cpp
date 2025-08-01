#include "AutoStepInitTask.h"

AutoStepInitTask::AutoStepInitTask(
    InitTask&& task_function,
    const QString& displayText)
    : task_function(std::move(task_function))
    , displayText(displayText) {
}

AutoStepInitTask::AutoStepInitTask(
    InitTask&& task_function, QString&& displayText)
    : task_function(std::move(task_function))
    , displayText(std::move(displayText)) {
}
