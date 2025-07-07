#include "PageSwitchingLimiter.h"

PageSwitchingLimiter::PageSwitchingLimiter(QSlider* bar, QObject* parent)
    : BoundSliderFactory<PageSwitchingLimiterParams::DEF_POSX,
                         PageSwitchingLimiterParams::LEAST_POSX,
                         PageSwitchingLimiterParams::MAX_POSX>(bar, parent) {
}

void PageSwitchingLimiter::_plain_set_value(int value) {
    BoundSliderFactory<PageSwitchingLimiterParams::DEF_POSX,
                       PageSwitchingLimiterParams::LEAST_POSX,
                       PageSwitchingLimiterParams::MAX_POSX>::_plain_set_value(value);
    emit valueChanged(current_value);
}
