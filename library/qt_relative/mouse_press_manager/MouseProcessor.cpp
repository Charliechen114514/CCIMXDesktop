#include "MouseProcessor.h"
#include <QDebug>

MouseProcessor::MouseProcessor(
    TryFunctor _try_functor,
    ProcessFunctor _processing_functor)
    : try_functor(std::move(_try_functor))
    , processing_functor(std::move(_processing_functor)) {
}

bool MouseProcessor::try_and_process(MouseRecorder* recorder) {
    if (!enabled) {
        return next_one ? next_one->try_and_process(recorder) : false;
    }

    if (tryProcess(recorder)) {
        // OK, we can handle this
        if (directProcess(recorder)) {
            // Ok, we handle success
            qInfo() << processor_name << ": handle OK!";
            return true;
        } else {
            // OK, we need to go next or false back;
            qInfo() << processor_name << ": although it satisfied "
                                         "the processing, but processing "
                                         "failed, pass to the next one!";
            return next_one ? next_one->try_and_process(recorder) : false;
        }
    } else {
        qInfo() << processor_name << ": failed to pass the session, "
                                     "pass to the possible next one!";
        return next_one ? next_one->try_and_process(recorder) : false;
    }
}
