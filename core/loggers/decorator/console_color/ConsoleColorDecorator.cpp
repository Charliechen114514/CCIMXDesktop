#include "ConsoleColorDecorator.h"

ConsoleColorDecorator::ConsoleColorDecorator(FormativeFactory* other_factory)
    : FormativeFactory()
    , decorated_factory(other_factory) {
}

QString ConsoleColorDecorator::formativeFactory(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    return from_msgType(type) + (decorated_factory ? decorated_factory->formativeFactory(type, context, msg) : get_default_type(type, context, msg))
        + RESET;
}

QString ConsoleColorDecorator::from_msgType(QtMsgType type) const {
    switch (type) {
    case QtDebugMsg:
        return RESET;
    case QtInfoMsg:
        return CYAN;
    case QtWarningMsg:
        return YELLOW;
    case QtCriticalMsg:
        return RED;
    case QtFatalMsg:
        return RED;
    default:
        return RESET;
    }
}
