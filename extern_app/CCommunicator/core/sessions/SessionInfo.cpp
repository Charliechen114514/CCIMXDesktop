#include "SessionInfo.h"
#include "SessionError.h"
#include "SessionProtos.h"

SessionInfo::SessionInfo(const QByteArray& decoder_array) {
    if (decoder_array.startsWith(NAME_INDICATOR)) {
        nickName = DECODER::decode_name(decoder_array);
    } else {
        throw SessionError::NameInvalid();
    }
}

QByteArray SessionInfo::toProtocalString() const {
    QByteArray result;
    // encoding name
    result = NAME_INDICATOR + nickName.toUtf8() + FINISH;
    // return the result
    return result;
}
