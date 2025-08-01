#include "AutoStepIniter.h"
#include "AutoStepInitTask.h"
#include <QDebug>
AutoStepIniter::AutoStepIniter(QObject* parent)
    : QObject { parent } {
}

void AutoStepIniter::install_tasks(std::shared_ptr<AutoStepInitTask>&& task) {
    tasks.emplaceBack(std::move(task));
}

void AutoStepIniter::run_init_session() {
    if (tasks.empty()) {
        qWarning() << "the session owns no task, nothing worth init!";
        return;
    }

    float steps = auto_caculate_process();
    float current = 0;
    for (const auto& each_task_session : std::as_const(tasks)) {
        each_task_session->invoke_init();
        current += steps;
        emit updateProgress(each_task_session->get_displayText(), current);
        qInfo() << "Session of: " << each_task_session->get_displayText()
                << " Finished at: " << current << "%!";
    }
}

float AutoStepIniter::auto_caculate_process() {
    return 100.0f / static_cast<float>(tasks.size());
}
