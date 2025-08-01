#ifndef BACKLIGHTCONTROLLERSINGLETON_H
#define BACKLIGHTCONTROLLERSINGLETON_H
#include <QtClassHelperMacros>
#include <memory>
class BacklightController;

class BackLightControllerSingleton {
public:
    static std::shared_ptr<BacklightController> instance();

private:
    BackLightControllerSingleton() = delete;
    ~BackLightControllerSingleton() = delete;
    Q_DISABLE_COPY_MOVE(BackLightControllerSingleton);

    static std::shared_ptr<BacklightController> m_instance;
};

#endif // BACKLIGHTCONTROLLERSINGLETON_H
