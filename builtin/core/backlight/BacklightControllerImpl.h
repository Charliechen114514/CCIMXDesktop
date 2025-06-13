#ifndef BACKLIGHTCONTROLLERIMPL_H
#define BACKLIGHTCONTROLLERIMPL_H

#include <QtClassHelperMacros>

/**
 * @brief The BacklightControllerImpl class
 * Abstract base class for platform-specific backlight control implementations.
 * 
 * This class defines the interface for querying and setting backlight levels.
 * Derived classes should provide platform-specific implementations.
 */
class BacklightControllerImpl {
public:
    Q_DISABLE_COPY_MOVE(BacklightControllerImpl)

    /**
     * @brief Gets the maximum supported light level.
     * @return The maximum backlight value.
     */
    virtual int MAX_LIGHT_VAL() = 0;

    /**
     * @brief Gets the minimum supported light level.
     * @return The minimum backlight value.
     */
    virtual int MIN_LIGHT_VAL() = 0;

    /**
     * @brief Sets the current light level.
     * @param lightLevel The desired backlight value.
     */
    virtual void setLightLevel(int lightLevel) = 0;

    /**
     * @brief Gets the current light level.
     * @return The current backlight value.
     */
    virtual int lightLevel() = 0;

    /**
     * @brief Creates a platform-specific implementation of BacklightControllerImpl.
     * @return Pointer to a new instance of a subclass.
     */
    static BacklightControllerImpl* creator();

    /**
     * @brief Virtual destructor.
     */
    virtual ~BacklightControllerImpl() = default;

protected:
    /**
     * @brief Protected constructor to enforce abstract usage.
     */
    BacklightControllerImpl() = default;
};

/**
 * @brief The PesudoLightController class
 * A dummy light controller used for testing or non-hardware platforms.
 */
class PesudoLightController : public BacklightControllerImpl {
    static constexpr int MAX = 100;       ///< Maximum dummy brightness value
    static constexpr int MIN = 0;         ///< Minimum dummy brightness value
    int current_light = 50;               ///< Current dummy brightness value

public:
    /**
     * @brief Default constructor.
     */
    PesudoLightController() = default;

    Q_DISABLE_COPY_MOVE(PesudoLightController)

    /**
     * @brief Destructor.
     */
    ~PesudoLightController() override = default;

    /**
     * @brief Gets the dummy maximum brightness value.
     * @return The value 100.
     */
    int MAX_LIGHT_VAL() override;

    /**
     * @brief Gets the dummy minimum brightness value.
     * @return The value 0.
     */
    int MIN_LIGHT_VAL() override;

    /**
     * @brief Sets the dummy current brightness value.
     * @param lightLevel New value to set.
     */
    void setLightLevel(int lightLevel) override;

    /**
     * @brief Gets the current dummy brightness value.
     * @return Current dummy brightness.
     */
    int lightLevel() override;
};

#ifdef ARM_BUILD
/**
 * @brief The ArmPlatformBacklightController class
 * A stub for platform-specific backlight controller on ARM systems.
 * 
 */
class ArmPlatformBacklightController : public BacklightControllerImpl {
    
};
#endif

#endif // BACKLIGHTCONTROLLERIMPL_H
