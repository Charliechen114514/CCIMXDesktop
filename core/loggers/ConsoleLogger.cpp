#include "ConsoleLogger.h"
#include "base_components/format_factory/plain_format/PlainFormarter.h"
#include "base_components/format_factory/standard_format/StandardFormater.h"
#include "base_components/message_comsumer/ConsoleConsumer.h"
#include "decorator/console_color/ConsoleColorDecorator.h"

namespace {
FormativeFactory* factoryFromType(ConsoleLogger::ConsoleFormatStyle style) {
    switch (style) {
    case ConsoleLogger::ConsoleFormatStyle::Plain:
        return new PlainFormarter;
    case ConsoleLogger::ConsoleFormatStyle::LoguruLike:
        return new StandardFormater;
    }
    return nullptr;
}
}

ConsoleLogger::ConsoleLogger(ConsoleFormatStyle type)
    : DesktopLoggerBackends(std::make_shared<ConsoleColorDecorator>(factoryFromType(type)), std::make_shared<ConsoleConsumer>()) {
}

bool ConsoleLogger::postSelfStatus() {
    return true;
}
