#include "MetaMessages.h"

MetaMessages::MetaMessages()
    : type(AcceptableType::PlainMessage)
    , messageDateTime(QDateTime::currentDateTime()) { }

MetaMessages::MetaMessages(const QVariant& msg, bool isMe, AcceptableType t)
    : type(t)
    , messageDateTime(QDateTime::currentDateTime())
    , messages(msg)
    , isMe(isMe) { }

MetaMessages::MetaMessages(QVariant&& msg, bool isMe, AcceptableType t)
    : type(t)
    , messageDateTime(QDateTime::currentDateTime())
    , messages(std::move(msg))
    , isMe(isMe) { }
