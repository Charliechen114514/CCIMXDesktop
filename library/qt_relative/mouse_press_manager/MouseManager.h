#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H
#include <QList>
#include <QPoint>
#include <memory>
class MouseProcessor;
class MouseRecorder;

class MouseManager {
public:
	MouseManager();
    ~MouseManager();
    Q_DISABLE_COPY_MOVE(MouseManager);
    enum class PointType {
        Press,
        Release
    };

    void register_processor(MouseProcessor* new_processor);
    void install_mousepoint(const QPoint& point, PointType pointType);
    void install_mousepoint(QPoint&& point, PointType pointType);
    bool run_processor();

private:
    std::shared_ptr<MouseRecorder> recorder;
    QList<std::shared_ptr<MouseProcessor>> processor_recorders;
    MouseProcessor* head_processor { nullptr };
};

#endif // MOUSEMANAGER_H
