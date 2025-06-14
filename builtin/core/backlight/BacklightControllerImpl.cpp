#include "BacklightControllerImpl.h"

BacklightControllerImpl* BacklightControllerImpl::creator() {
    return new
#ifdef ARM_BUILD
        ArmPlatformBacklightController();
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
#include <QFile>
#include <QTextStream>
#include <QDebug>

int ArmPlatformBacklightController::MAX_LIGHT_VAL() {
    QFile file(max_brightness_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to read max_brightness";
        return 100; // fallback
    }
    QTextStream in(&file);
    int max_val;
    in >> max_val;
    return max_val;
}

int ArmPlatformBacklightController::MIN_LIGHT_VAL() {
    return MIN;
}

void ArmPlatformBacklightController::setLightLevel(int lightLevel) {
    int max_val = MAX_LIGHT_VAL();
    if (lightLevel < MIN) lightLevel = MIN;
    if (lightLevel > max_val) lightLevel = max_val;

    QFile file(brightness_file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to write brightness";
        return;
    }

    QTextStream out(&file);
    out << QString::number(lightLevel);
    file.close();

    current_light = lightLevel;
}

int ArmPlatformBacklightController::lightLevel() {
    QFile file(brightness_file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to read current brightness";
        return current_light; // fallback to cache
    }

    QTextStream in(&file);
    int current_val;
    in >> current_val;
    current_light = current_val;
    return current_val;
}

#endif
