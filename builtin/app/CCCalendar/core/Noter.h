#ifndef NOTER_H
#define NOTER_H
#include <QDate>
#include <QMap>
#include <QString>
struct NoteInfo {
    QString notes;
};

/**
 * @brief The Noter class holdings the light recorders
 * of the Date notes
 */
class Noter {
public:
    Noter() = default;
    Q_DISABLE_COPY_MOVE(Noter);
    void submitNoteInfo(const QDate &date, const NoteInfo &infos);
    void removeNoteInfo(const QDate& date);
    NoteInfo* noteInfo(const QDate& date) const;

private:
    QMap<QDate, std::shared_ptr<NoteInfo>> notes;
};

#endif // NOTER_H
