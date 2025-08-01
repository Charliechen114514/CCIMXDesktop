#ifndef AUTOSTEPINITTASK_H
#define AUTOSTEPINITTASK_H
#include <QString>
#include <functional>

class AutoStepInitTask {
public:
    using InitTask = std::function<void(void)>;
    AutoStepInitTask() = delete;
    Q_DISABLE_COPY_MOVE(AutoStepInitTask);
    AutoStepInitTask(InitTask&& task_function, const QString& displayText);
    AutoStepInitTask(InitTask&& task_function, QString&& displayText);
    inline void invoke_init() { task_function(); }
    inline void setDisplayText(const QString& str) { displayText = str; }
    inline void setDisplayText(QString&& str) { displayText = std::move(str); }
    inline QString get_displayText() const { return displayText; }

private:
    InitTask task_function;
    QString displayText;
};

#endif // AUTOSTEPINITTASK_H
