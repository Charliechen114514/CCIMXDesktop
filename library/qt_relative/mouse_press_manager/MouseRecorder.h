#ifndef MOUSERECORDER_H
#define MOUSERECORDER_H
#include <QPoint>

/**
 * @brief The MouseRecorder class
 * plain struct for recording mouse
 */
class MouseRecorder {
public:
    QPoint press; ///< Mouse press position
    QPoint release; ///< Mouse release position
};

#endif // MOUSERECORDER_H
