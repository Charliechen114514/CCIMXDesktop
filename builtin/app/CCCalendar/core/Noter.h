#ifndef NOTER_H
#define NOTER_H

#include <QDate>
#include <QMap>
#include <QString>

/**
 * @struct NoteInfo
 * @brief Container for note information
 *
 * Stores the textual content of a single note.
 */
struct NoteInfo {
    QString notes; /**< The content of the note */
};

/**
 * @class Noter
 * @brief Manages date-based note storage and retrieval
 *
 * Provides functionality to store, retrieve, and manage notes
 * associated with specific dates using a QMap-based storage system.
 * The class is non-copyable and non-movable.
 */
class Noter {
public:
    /**
     * @brief Default constructor
     */
    Noter() = default;

    Q_DISABLE_COPY_MOVE(Noter); /**< Disables copying and moving */

    /**
     * @brief Add or update a note for a specific date
     * @param date The date to associate with the note
     * @param infos The note content to store
     */
    void submitNoteInfo(const QDate& date, const NoteInfo& infos);

    /**
     * @brief Remove a note for a specific date
     * @param date The date whose note should be removed
     */
    void removeNoteInfo(const QDate& date);

    /**
     * @brief Retrieve a note for a specific date
     * @param date The date to look up
     * @return Pointer to the NoteInfo if found, nullptr otherwise
     * @note The returned pointer is only valid while the Noter exists
     */
    NoteInfo* noteInfo(const QDate& date) const;

private:
    QMap<QDate, std::shared_ptr<NoteInfo>> notes; /**< Map storing date-note associations */
};

#endif // NOTER_H
