#ifndef EASINGCURVECOMBOXBOXSETUPER_H
#define EASINGCURVECOMBOXBOXSETUPER_H
#include <QEasingCurve>
class QComboBox;

/**
 * @namespace UiTools supports the Ui sessions
 */
namespace UiTools {
/**
 * @namespace EasingCurveComboBoxSetuper setup the combox box
 */
namespace EasingCurveComboBoxSetuper {
    /**
     * @brief setupComboBox setup for filling the combo box
     * @param combo
     */
    void setupComboBox(QComboBox* combo);
    /**
     * @brief selectedEasing for the selecting to the real
     * @param combo
     * @return
     */
    QEasingCurve::Type selectedEasing(QComboBox* combo);
}
}

#endif // EASINGCURVECOMBOXBOXSETUPER_H
