#ifndef FORMATIVEFACTORY_H
#define FORMATIVEFACTORY_H
#include <QDebug>
#include <QString>
class FormativeFactory {
public:
    virtual ~FormativeFactory() = default;
    /**
     * @brief Formats a log message according to configured options
     * @param type The log message type (debug, warning, etc.)
     * @param context The log message context (file, line, function)
     * @param msg The actual log message
     * @return Formatted log message as QString
     */
    virtual QString formativeFactory(QtMsgType type, const QMessageLogContext& context, const QString& msg) = 0;
};

#endif // FORMATIVEFACTORY_H
