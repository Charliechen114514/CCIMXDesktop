#ifndef LOGGERBASECONSUMER_H
#define LOGGERBASECONSUMER_H
#include <QString>
/**
 * @brief The LoggerBaseConsumer class
 * as consumer type
 */
class LoggerBaseConsumer {
public:
    virtual ~LoggerBaseConsumer() = default;
    /**
     * @brief consume_message to impled the write
     * @param message for written
     * @return do we success?
     */
    virtual bool consume_message(const QString&& message) = 0;
    /**
     * @brief errorString
     * @return
     */
    virtual QString errorString() const = 0;
};

#endif // LOGGERBASECONSUMER_H
