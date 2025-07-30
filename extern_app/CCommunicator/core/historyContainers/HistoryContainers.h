#ifndef HISTORYCONTAINERS_H
#define HISTORYCONTAINERS_H
#include "MetaMessages.h"
#include <QObject>
class ChatMainPanel;

class HistoryContainers {
public:
    HistoryContainers();
    void enQueueMessage(const QVariant& message, bool isMe, MetaMessages::AcceptableType type);
    void enQueueMessage(QVariant&& message, bool isMe, MetaMessages::AcceptableType type);
    void removeMessage(MetaMessages&& messageType);
    void process_resume_message(ChatMainPanel* panel);

private:
    QList<std::shared_ptr<MetaMessages>> metaMessages;
};

#endif // HISTORYCONTAINERS_H
