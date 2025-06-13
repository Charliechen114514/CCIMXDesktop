#ifndef LIGHTCONFIGURES_H
#define LIGHTCONFIGURES_H

#include <QWidget>

namespace Ui {
class LightConfigures;
}

class BacklightController;

/**
 * @brief The LightConfigures class
 * Provides a UI interface for adjusting the screen backlight brightness.
 * 
 * This class connects to the backlight controller and allows users to 
 * change the brightness level through a GUI component.
 */
class LightConfigures : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the LightConfigures widget.
     * @param parent Optional parent QWidget.
     */
    explicit LightConfigures(QWidget* parent = nullptr);

    /**
     * @brief Destructor.
     */
    ~LightConfigures();

private:
    Ui::LightConfigures* ui;                          ///< UI components pointer.
    std::shared_ptr<BacklightController> controller;  ///< Backlight controller.

    /**
     * @brief Sets the brightness level.
     * @param level The desired brightness level.
     */
    void setLightLevel(int level);

    /**
     * @brief Executes post-processing logic after brightness value changes.
     */
    void post_hooks_of_value_session();
};

#endif // LIGHTCONFIGURES_H
