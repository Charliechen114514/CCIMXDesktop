#ifndef LOCALWEATHERCARD_H
#define LOCALWEATHERCARD_H
/* Card Works as the base */
#include "appcardwidget.h"

struct LocalWeatherLightFetcher{
public:
    LocalWeatherLightFetcher() = default;
    Q_DISABLE_COPY(LocalWeatherLightFetcher);
    /* for advanced c++, use concept is better */
    virtual float fetch_local_tempature() = 0;
    virtual QString makeup_toast_message() = 0;
};

class LocalWeatherCard : public AppCardWidget
{
public:
    LocalWeatherCard() = delete;
    Q_DISABLE_COPY(LocalWeatherCard);
    explicit LocalWeatherCard(
        DesktopToast* toast, QWidget *parent = nullptr);

public:
    void invoke_preLaunch_work();

protected:
    void postAppCardWidget();
    LocalWeatherLightFetcher*   localFetcher{nullptr};
};

#endif // LOCALWEATHERCARD_H
