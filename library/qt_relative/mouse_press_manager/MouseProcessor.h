#ifndef MOUSEPROCESSOR_H
#define MOUSEPROCESSOR_H
#include <QPoint>
#include <QString>
#include <functional>
class MouseRecorder;
class MouseProcessor {
public:
    using TryFunctor = std::function<bool(MouseRecorder* recorder)>;
    using ProcessFunctor = std::function<bool(MouseRecorder* recorder)>;
    MouseProcessor() = delete;
    explicit MouseProcessor(
        TryFunctor _try_functor,
        ProcessFunctor _processing_functor);
    Q_DISABLE_COPY_MOVE(MouseProcessor);
    bool try_and_process(MouseRecorder* recorder);
    inline bool tryProcess(MouseRecorder* recorder) { return try_functor(recorder); }
    inline bool directProcess(MouseRecorder* recorder) { return processing_functor(recorder); }
    inline void setNext(MouseProcessor* processor) { next_one = processor; }
    inline MouseProcessor* next() const { return next_one; }
    inline bool isEnable() const { return enabled; }
    inline void setEnable(bool enabled) { this->enabled = enabled; }

    inline QString name() const { return processor_name; }
    inline void setName(const QString& name) { processor_name = name; }
    inline void setName(QString&& name) { processor_name = std::move(name); }

private:
    TryFunctor try_functor;
    ProcessFunctor processing_functor;
    MouseProcessor* next_one { nullptr };
    QString processor_name { "MouseProcessor" };
    bool enabled { true };
};

#endif // MOUSEPROCESSOR_H
