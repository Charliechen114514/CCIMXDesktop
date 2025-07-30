#ifndef LISTCONTEXTINFO_H
#define LISTCONTEXTINFO_H
#include <QDateTime>
#include <QPixmap>
#include <QString>

class ListContextInfo {
public:
    ListContextInfo() = delete;
    ListContextInfo(const QString markable_name, const QString& uuid);
    ListContextInfo(const QString& markableName, const QString& uuid,
                    const QString& displayText,
                    const QDateTime& displayDatetime,
                    int unreadCount);
    friend bool operator==(
        const ListContextInfo& left,
        const ListContextInfo& right) noexcept {
        return left.markable_name == right.markable_name;
    }
    QString get_markable_name() const;
    ;
    void flush_datetime(const QDateTime& display_datetime);
    const QDateTime& queryDateTime() const;
    int getUnread() const;
    const QString& getDisplayText() const;
    const QString& uuid() const { return markingUuid; }
    const QPixmap& avatar() const;

    void setQueryDateTime(const QDateTime& dateTime);
    void setUnread(int unreadCount);
    void setDisplayText(const QString& text);
    void setAvatar(const QPixmap& pixmap);

private:
    QString markable_name; // oh shit, these cannot be changed and be a must
    QString displayText {};
    QDateTime display_datetime;
    QString markingUuid;
    QPixmap avatar_pixmap;
    int unread { 0 };
};

namespace std {
template <>
struct hash<ListContextInfo> {
    std::size_t operator()(const ListContextInfo& info) const {
        // Use the hash function for QString
        return qHash(info.get_markable_name());
    }
};
}

#endif // LISTCONTEXTINFO_H
