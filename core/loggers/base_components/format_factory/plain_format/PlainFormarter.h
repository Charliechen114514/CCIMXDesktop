#ifndef PLAINFORMARTER_H
#define PLAINFORMARTER_H
#include "../FormativeFactory.h"

/**
 * @brief The PlainFormarter class just simply output the
 * message as default, without any tiring messages info!
 */
class PlainFormarter : public FormativeFactory {
public:
    PlainFormarter() = default; ///< constructor
    /**
     * @brief formativeFactory format strings
     * @param type
     * @param context
     * @param msg
     * @return
     */
    QString formativeFactory(
        QtMsgType type,
        const QMessageLogContext& context,
        const QString& msg) override;
};

#endif // PLAINFORMARTER_H
