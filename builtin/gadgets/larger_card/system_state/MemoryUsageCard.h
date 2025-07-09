#ifndef MEMORYUSAGECARD_H
#define MEMORYUSAGECARD_H

#include <QWidget>

namespace Ui {
class MemoryUsageCard;
}

/**
 * @brief The MemoryUsageCard class
 */
class MemoryUsageCard : public QWidget {
	Q_OBJECT

public:
    explicit MemoryUsageCard(QWidget* parent = nullptr); ///< constructor
    ~MemoryUsageCard(); ///< erase
    void refresh_once(); ///< refresh memory info

private:
    Ui::MemoryUsageCard* ui; ///< ui handle
};

#endif // MEMORYUSAGECARD_H
