#ifndef METAMESSAGES_H
#define METAMESSAGES_H
#include <QDateTime>
#include <QVariant>
struct MetaMessages {
    enum class AcceptableType {
        PlainMessage
    } type
        = MetaMessages::AcceptableType::PlainMessage;
    QDateTime messageDateTime;
    QVariant messages;
    MetaMessages();

    MetaMessages(const QVariant& msg, bool isMe, AcceptableType t);

    MetaMessages(QVariant&& msg, bool isMe, AcceptableType t);
    friend inline constexpr bool operator==(const MetaMessages& left, const MetaMessages& right) {
        return right.type == left.type && right.messageDateTime == left.messageDateTime
            && right.messages == left.messages;
    }

    bool isMe { false };
};

#endif // METAMESSAGES_H
