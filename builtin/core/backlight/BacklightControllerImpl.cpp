#include "BacklightControllerImpl.h"

BacklightControllerImpl* BacklightControllerImpl::creator() {
    return new
#ifdef ARM_BUILD
        ArmPlatformBacklightController()
#else
        PesudoLightController();
#endif
}

int PesudoLightController::MAX_LIGHT_VAL() {
    return PesudoLightController::MAX;
}

int PesudoLightController::MIN_LIGHT_VAL() {
    return PesudoLightController::MIN;
}

void PesudoLightController::setLightLevel(int lightLevel) {
    this->current_light = lightLevel;
}

int PesudoLightController::lightLevel() {
    return current_light;
}

#ifdef ARM_BUILD
// TODO: Waiting for ARM Releases
#endif
