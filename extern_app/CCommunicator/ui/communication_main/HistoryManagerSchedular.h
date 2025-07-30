#ifndef HISTORYMANAGERSCHEDULAR_H
#define HISTORYMANAGERSCHEDULAR_H
#include "core/historyContainers/MetaMessages.h"
#include <QMap>
#include <QObject>
class Session;
class ChatMainPanel;
class HistoryContainers;
class HistoryManagerSchedular : public QObject {
	Q_OBJECT
public:
    explicit HistoryManagerSchedular(QObject* parent = nullptr);
    ~HistoryManagerSchedular();
    void createHistorySession(Session* session);
    std::shared_ptr<HistoryContainers> queryHistory(Session* sessions);
    bool load_history(Session* s, ChatMainPanel* mainPanel);

signals:

private:
    QMap<Session*, std::shared_ptr<HistoryContainers>>
        schedulars;
};

#endif // HISTORYMANAGERSCHEDULAR_H
