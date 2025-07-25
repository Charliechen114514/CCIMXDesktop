/**
 * @file WeatherCard.h
 * @brief Defines the WeatherCard widget and its plugin factory for displaying weather information.
 */

#ifndef WEATHERCARD_H
#define WEATHERCARD_H

#include "DesktopPluginWidgetBase.h" // Base class for desktop plugin widgets
#include "WeatherData.h" // Data structure for weather information
#include <QObject> // Base class for WeatherCard_Plugins (for Q_OBJECT)
#include <QWidget> // Base class for WeatherCard
#include <QtPlugin> // For Q_PLUGIN_METADATA and Q_INTERFACES

// Forward declaration of the UI namespace generated by Qt Designer
namespace Ui {
class WeatherCard;
}

// Forward declaration to avoid heavy includes
class WeatherRequestEngine;

/**
 * @class WeatherCard
 * @brief A custom QWidget that displays current weather information.
 *
 * This widget is designed to present weather data in a compact "card" format.
 * It receives `WeatherData` objects and updates its UI to reflect the current
 * weather conditions. It typically relies on a `WeatherRequestEngine` to fetch
 * the actual weather data.
 */
class WeatherCard : public QWidget {
Q_OBJECT // Enables Qt's meta-object system features like signals and slots

    public :
    /**
     * @brief Constructs a WeatherCard object.
     * @param parent A pointer to the parent widget, if any. Defaults to `nullptr`.
     */
    explicit WeatherCard(QWidget* parent = nullptr);

    /**
     * @brief Destroys the WeatherCard object.
     * 	 * This destructor is responsible for cleaning up resources, particularly
     * the dynamically allocated UI object and the `WeatherRequestEngine`.
     */
    ~WeatherCard();

private slots:
    /**
     * @brief Slot to receive and display weather data.
     * 	 * This slot is connected to a signal (e.g., from `WeatherRequestEngine`)
     * that provides updated `WeatherData`. It then updates the internal UI
     * elements to show the received weather information.
     * @param data A constant reference to the `WeatherData` object containing the weather details.
     */
    void receiveDatas(const WeatherData data);

private:
    /**
     * @brief A pointer to the UI object generated by Qt Designer.
     * 	 * This member provides access to the widgets and layout defined in the `.ui` file
     * associated with `WeatherCard`.
     */
    Ui::WeatherCard* ui;

    /**
     * @brief A pointer to the `WeatherRequestEngine` instance.
     * 	 * This engine is responsible for making API calls or other requests to
     * fetch weather data.
     */
    WeatherRequestEngine* engine;
};

/**
 * @class WeatherCard_Plugins
 * @brief A plugin factory class for creating WeatherCard instances.
 *
 * This class serves as the entry point for dynamically loading `WeatherCard`
 * as a plugin within a Qt application. It implements the `DesktopPluginWidgetBase`
 * interface, allowing it to be discovered and instantiated by a plugin server.
 */
class WeatherCard_Plugins : public QObject, public DesktopPluginWidgetBase {
Q_OBJECT // Enables Qt's meta-object system features

/**
 * @brief Qt plugin metadata macro.
 * 	 * Specifies the unique identifier (IID) for the plugin interface and the
 * path to the JSON file containing additional plugin metadata (e.g., version, dependencies).
 */
Q_PLUGIN_METADATA(IID "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0" FILE "WeatherCard_plugin.json")

    /**
     * @brief Declares that this class implements the `DesktopPluginWidgetBase` interface.
     * This is crucial for Qt's plugin system to correctly identify and use this class.
     */
    Q_INTERFACES(DesktopPluginWidgetBase)

        public :
    /**
     * @brief Factory method to create and return a new instance of WeatherCard.
     * 	 * This method is part of the `DesktopPluginWidgetBase` interface. When the plugin
     * is loaded, this method is called to create the actual widget that will be displayed.
     * @param parent A pointer to the parent widget for the new WeatherCard instance. Defaults to `nullptr`.
     * @return A pointer to a newly created `WeatherCard` widget. Ownership is transferred to the caller.
     */
    QWidget* factorize_widget(QWidget* parent = nullptr) override {
        return new WeatherCard(parent);
    }
};

#endif // WEATHERCARD_H
