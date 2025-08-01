#include "BackLightControllerSingleton.h"
#include "BacklightController.h"
#include <mutex>
std::shared_ptr<BacklightController>
    BackLightControllerSingleton::m_instance = nullptr;

std::shared_ptr<BacklightController> BackLightControllerSingleton::instance() {
    static std::once_flag init_flag;
    std::call_once(init_flag, []() {
        m_instance = std::make_shared<BacklightController>();
    });
    return m_instance;
}
