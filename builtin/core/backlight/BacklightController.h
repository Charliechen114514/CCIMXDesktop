#ifndef BACKLIGHTCONTROLLER_H
#define BACKLIGHTCONTROLLER_H
#include <QtClassHelperMacros>
class BacklightControllerImpl;

/**
 * @brief backlighty controller
 * 
 */
class BacklightController {
public:
    /**
     * @brief Disable copy move
     * 
     */
    Q_DISABLE_COPY_MOVE(BacklightController);
    /**
     * @brief Construct a new Backlight Controller object
     * 
     */
	BacklightController();

    /**
     * @brief max level light
     * 
     * @return int 
     */
    int max_level();
    /**
     * @brief min level light
     * 
     * @return int 
     */
    int min_level();
    /**
     * @brief Set the Light Level object
     * 
     * @param lightLevel 
     */
    void setLightLevel(int lightLevel);
    /**
     * @brief get the light level
     * 
     * @return int 
     */
    int lightLevel();

private:
    BacklightControllerImpl* impl; ///< impl handle
};

#endif // BACKLIGHTCONTROLLER_H
