#include "Noter.h"

void Noter::submitNoteInfo(const QDate& date, const NoteInfo& infos) {
    notes.insert(date, std::make_shared<NoteInfo>(infos));
}

void Noter::removeNoteInfo(const QDate& date) {
    notes.remove(date);
}

NoteInfo* Noter::noteInfo(const QDate& date) const {
    auto it = notes.find(date);
    if (it != notes.end()) {
        return it.value().get();
    } else {
        return nullptr;
    }
}
