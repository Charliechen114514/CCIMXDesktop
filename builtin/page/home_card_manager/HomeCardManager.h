#ifndef HOMECARDMANAGER_H
#define HOMECARDMANAGER_H
#include <QtClassHelperMacros>
#include <memory>
class QStackedWidget;
class QWidget;
class QMutex;
class HomeCardManager {
public:
    explicit HomeCardManager(QStackedWidget* widget);
    Q_DISABLE_COPY_MOVE(HomeCardManager);
    virtual void installWidget(QWidget* widget);
    virtual void removeWidget(QWidget* widget);
    virtual int accessible_card_cnt() const;

protected:
    QStackedWidget* stacked_widget;
    std::shared_ptr<QMutex> mutex;
};

#endif // HOMECARDMANAGER_H
