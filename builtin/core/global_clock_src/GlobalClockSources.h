#ifndef GLOBALCLOCKSOURCES_H
#define GLOBALCLOCKSOURCES_H
#include <QObject>
#include <QTime>
class QTimer;

/**
 * @brief The GlobalClockSources class
 * holds the desktop timer sessions,
 * defaulty, we use the QTimer API For the wrappers
 */
class GlobalClockSources : public QObject {
	Q_OBJECT
    static constexpr const unsigned short SEC_PERIOD = 1000;

public:
    explicit GlobalClockSources(QObject* parent = nullptr);

signals:
    /**
     * @brief timeUpdate will update all the relative events to
     * update its time
     * @param newTime
     */
    void timeUpdate(QTime newTime);

private:
    QTimer* internal_updater;
};

#endif // GLOBALCLOCKSOURCES_H
