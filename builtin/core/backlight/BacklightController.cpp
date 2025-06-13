#include "BacklightController.h"
#include "BacklightControllerImpl.h"
BacklightController::BacklightController() {
    impl = BacklightControllerImpl::creator();
}

int BacklightController::max_level() {
    return impl->MAX_LIGHT_VAL();
}

int BacklightController::min_level() {
    return impl->MIN_LIGHT_VAL();
}

void BacklightController::setLightLevel(int lightLevel) {
    impl->setLightLevel(lightLevel);
}

int BacklightController::lightLevel() {
    return impl->lightLevel();
}
