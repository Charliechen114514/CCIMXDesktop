#include "ListContextInfo.h"

ListContextInfo::ListContextInfo(const QString markable_name, const QString& uuid)
    : markable_name(markable_name)
    , markingUuid(uuid) {
}

ListContextInfo::ListContextInfo(const QString& markableName,
                                 const QString& uuid,
                                 const QString& displayText,
                                 const QDateTime& displayDatetime,
                                 int unreadCount)
    : markable_name(markableName)
    , displayText(displayText)
    , display_datetime(displayDatetime)
    , unread(unreadCount)
    , markingUuid(uuid) {
}

QString ListContextInfo::get_markable_name() const {
    return markable_name;
}

void ListContextInfo::flush_datetime(const QDateTime& display_datetime) {
    this->display_datetime = display_datetime;
}

const QDateTime& ListContextInfo::queryDateTime() const {
    return display_datetime;
}

int ListContextInfo::getUnread() const {
    return unread;
}

const QString& ListContextInfo::getDisplayText() const {
    return displayText;
}

const QPixmap& ListContextInfo::avatar() const {
    return avatar_pixmap;
}

void ListContextInfo::setQueryDateTime(const QDateTime& dateTime) {
    display_datetime = dateTime;
}

void ListContextInfo::setUnread(int unreadCount) {
    unread = unreadCount;
}

void ListContextInfo::setDisplayText(const QString& text) {
    displayText = text;
}

void ListContextInfo::setAvatar(const QPixmap& pixmap) {
    avatar_pixmap = pixmap;
}
