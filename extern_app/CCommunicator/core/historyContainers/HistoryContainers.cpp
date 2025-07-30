#include "HistoryContainers.h"
#include "ChatMainPanel.h"
HistoryContainers::HistoryContainers() {
}

void HistoryContainers::enQueueMessage(const QVariant& message, bool isMe, MetaMessages::AcceptableType type) {
    metaMessages.append(std::make_shared<MetaMessages>(message, isMe, type));
    qDebug() << "Enqueued message (copy): Type =" << static_cast<int>(type) << ", Content =" << message;
}

void HistoryContainers::enQueueMessage(QVariant&& message, bool isMe, MetaMessages::AcceptableType type) {
    metaMessages.append(std::make_shared<MetaMessages>(std::move(message), isMe, type));
    qDebug() << "Enqueued message (move): Type =" << static_cast<int>(type) << ", Content =" << message;
}

void HistoryContainers::removeMessage(MetaMessages&& message) {
    qDebug() << "Attempting to remove exact match message: Type =" << static_cast<int>(message.type)
             << ", Content =" << message.messages;

    metaMessages.removeIf(
        [&](const std::shared_ptr<MetaMessages>& existingPtr) {
            // 确保指针有效，然后比较指针指向的 MetaMessages 对象
            return existingPtr && (*existingPtr == message);
        });

    qDebug() << "Messages remaining after removal:" << metaMessages.size();
}

void HistoryContainers::process_resume_message(ChatMainPanel* panel) {
    // OK, we resume these
    for (const std::shared_ptr<MetaMessages>& metaMessage : std::as_const(metaMessages)) {
        switch (metaMessage->type) {
        case MetaMessages::AcceptableType::PlainMessage:
            panel->appendMessage(
                metaMessage->messages.toString(),
                metaMessage->isMe, QPixmap());
            break;
        default:
            qCritical() << "Unknown Message Types";
            break;
        }
    }
}
