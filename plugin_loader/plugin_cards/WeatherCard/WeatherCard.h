#ifndef WEATHERCARD_H
#define WEATHERCARD_H
#include "DesktopPluginWidgetBase.h"
#include "WeatherData.h"
#include <QWidget>
namespace Ui {
class WeatherCard;
}

class WeatherRequestEngine;
class WeatherCard : public QWidget {
	Q_OBJECT

public:
    explicit WeatherCard(QWidget* parent = nullptr);
	~WeatherCard();
private slots:
    void receiveDatas(const WeatherData& data);

private:
    Ui::WeatherCard* ui;
    WeatherRequestEngine* engine;
};

class WeatherCard_Plugins : public QObject, public DesktopPluginWidgetBase {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.DesktopPluginWidgetBase.DesktopPluginWidgetBase/1.0" FILE "WeatherCard_plugin.json")
    Q_INTERFACES(DesktopPluginWidgetBase)
public:
    QWidget* factorize_widget(QWidget* parent = nullptr) override {
        return new WeatherCard(parent);
    }
};

#endif // WEATHERCARD_H
