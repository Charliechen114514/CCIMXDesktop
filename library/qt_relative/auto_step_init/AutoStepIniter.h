#ifndef AUTOSTEPINITER_H
#define AUTOSTEPINITER_H
#include <QObject>
class AutoStepInitTask;
class AutoStepIniter : public QObject {
	Q_OBJECT
public:
    explicit AutoStepIniter(QObject* parent = nullptr);
    void install_tasks(std::shared_ptr<AutoStepInitTask>&& task);
    void run_init_session();

signals:
    void updateProgress(QString displayText, int process_value);

private:
    QList<std::shared_ptr<AutoStepInitTask>> tasks;
    float auto_caculate_process();
};

#endif // AUTOSTEPINITER_H
