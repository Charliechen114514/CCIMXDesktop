#include "HistoryManagerSchedular.h"
#include "core/historyContainers/HistoryContainers.h"
#include "ui/communication_main/ChatMainPanel.h"
HistoryManagerSchedular::HistoryManagerSchedular(QObject* parent)
    : QObject { parent } {
}

void HistoryManagerSchedular::createHistorySession(Session* session) {
    schedulars.insert(session, std::make_shared<HistoryContainers>());
    qDebug() << "Ok when creating the history containers";
}

std::shared_ptr<HistoryContainers>
HistoryManagerSchedular::queryHistory(Session* sessions) {
    auto records = schedulars.value(sessions);
    return records;
}

bool HistoryManagerSchedular::load_history(Session* s, ChatMainPanel* mainPanel) {

    auto history = queryHistory(s);
    if (!history) {
        qCritical() << "No history found!";
        return false;
    }

    mainPanel->clearShownMessages();
    history->process_resume_message(mainPanel);
    qDebug() << "Resume OK";
    return true;
}

HistoryManagerSchedular::~HistoryManagerSchedular() = default;
