#ifndef SESSIONPROTOS_H
#define SESSIONPROTOS_H
#include <QString>
static constexpr const char* NAME_INDICATOR = "NAME:";
static constexpr const char* FINISH = "\n";
static constexpr const char* TEXTTYPE = "PLAIN_TEXT";
namespace DECODER {

inline QString decode_name(const QByteArray& e) {
    return QString::fromUtf8(e.mid(::strlen(NAME_INDICATOR)));
}

inline QString decode_plainText(const QByteArray& e) {
    return QString::fromUtf8(e.mid(::strlen(TEXTTYPE)));
}

inline QByteArray encode_plainText(const QString& text) {
    return TEXTTYPE + text.toUtf8() + FINISH;
}

inline bool isType(const QByteArray& e, const char* TYPE) {
    return e.startsWith(TYPE);
}

};

#endif // SESSIONPROTOS_H
