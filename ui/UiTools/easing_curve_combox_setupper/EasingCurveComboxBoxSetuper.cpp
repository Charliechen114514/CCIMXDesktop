#include "EasingCurveComboxBoxSetuper.h"
#include <QComboBox>
#include <QEasingCurve>
#include <QMap>

static const QMap<QString, QEasingCurve::Type> easingCurveMap = {
    { "Linear", QEasingCurve::Linear },
    { "InQuad", QEasingCurve::InQuad },
    { "OutQuad", QEasingCurve::OutQuad },
    { "InOutQuad", QEasingCurve::InOutQuad },
    { "OutInQuad", QEasingCurve::OutInQuad },
    { "InCubic", QEasingCurve::InCubic },
    { "OutCubic", QEasingCurve::OutCubic },
    { "InOutCubic", QEasingCurve::InOutCubic },
    { "OutInCubic", QEasingCurve::OutInCubic },
    { "InQuart", QEasingCurve::InQuart },
    { "OutQuart", QEasingCurve::OutQuart },
    { "InOutQuart", QEasingCurve::InOutQuart },
    { "OutInQuart", QEasingCurve::OutInQuart },
    { "InQuint", QEasingCurve::InQuint },
    { "OutQuint", QEasingCurve::OutQuint },
    { "InOutQuint", QEasingCurve::InOutQuint },
    { "OutInQuint", QEasingCurve::OutInQuint },
    { "InSine", QEasingCurve::InSine },
    { "OutSine", QEasingCurve::OutSine },
    { "InOutSine", QEasingCurve::InOutSine },
    { "OutInSine", QEasingCurve::OutInSine },
    { "InExpo", QEasingCurve::InExpo },
    { "OutExpo", QEasingCurve::OutExpo },
    { "InOutExpo", QEasingCurve::InOutExpo },
    { "OutInExpo", QEasingCurve::OutInExpo },
    { "InCirc", QEasingCurve::InCirc },
    { "OutCirc", QEasingCurve::OutCirc },
    { "InOutCirc", QEasingCurve::InOutCirc },
    { "OutInCirc", QEasingCurve::OutInCirc },
    { "InElastic", QEasingCurve::InElastic },
    { "OutElastic", QEasingCurve::OutElastic },
    { "InOutElastic", QEasingCurve::InOutElastic },
    { "OutInElastic", QEasingCurve::OutInElastic },
    { "InBack", QEasingCurve::InBack },
    { "OutBack", QEasingCurve::OutBack },
    { "InOutBack", QEasingCurve::InOutBack },
    { "OutInBack", QEasingCurve::OutInBack },
    { "InBounce", QEasingCurve::InBounce },
    { "OutBounce", QEasingCurve::OutBounce },
    { "InOutBounce", QEasingCurve::InOutBounce },
    { "OutInBounce", QEasingCurve::OutInBounce },
    { "InCurve", QEasingCurve::InCurve },
    { "OutCurve", QEasingCurve::OutCurve },
    { "SineCurve", QEasingCurve::SineCurve },
    { "CosineCurve", QEasingCurve::CosineCurve },
    { "BezierSpline", QEasingCurve::BezierSpline },
    { "TCBSpline", QEasingCurve::TCBSpline },
    { "Custom", QEasingCurve::Custom },
    { "NCurveTypes", QEasingCurve::NCurveTypes }
};

void UiTools::EasingCurveComboBoxSetuper::setupComboBox(QComboBox* combo) {
    combo->addItems(easingCurveMap.keys());
}

QEasingCurve::Type UiTools::EasingCurveComboBoxSetuper::selectedEasing(QComboBox* combo) {
    QString selectedText = combo->currentText();
    return easingCurveMap.value(selectedText, QEasingCurve::Linear);
}
