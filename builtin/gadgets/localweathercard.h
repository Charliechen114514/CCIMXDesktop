#ifndef LOCALWEATHERCARD_H
#define LOCALWEATHERCARD_H
/* Card Works as the base */
#include "appcardwidget.h"

/**
 * @brief The LocalWeatherLightFetcher class is the interface level class
 * if later, the projects using C++23, we shell try to use the concept to redefined the
 * class Interface for the lower cost in performance
 */
struct LocalWeatherLightFetcher {
public:
	LocalWeatherLightFetcher() = default;
	Q_DISABLE_COPY(LocalWeatherLightFetcher);
	/* for advanced c++, use concept is better */

	/**
	 * @brief fetch_local_tempature is the main function to fetch the local temperature
	 * @return temperature value
	 */
	virtual float fetch_local_tempature() = 0;
	/**
	 * @brief makeup_toast_message is the message that will be displayed in the toast, so
	 * this functions is using in indicating how to format the message
	 * @return
	 */
	virtual QString makeup_toast_message() = 0;
};

/**
 * @brief The LocalWeatherCard class is the card widgets, press it to
 * trigger the light service(current displaying by toast depatching)
 */
class LocalWeatherCard : public AppCardWidget {
public:
	LocalWeatherCard() = delete;
	Q_DISABLE_COPY(LocalWeatherCard);
	explicit LocalWeatherCard(
		DesktopToast* toast, QWidget* parent = nullptr);

public:
	/**
	 * @brief concrete implementation of the AppCardWidget
	 */
	void invoke_preLaunch_work();

protected:
	/**
	 * @brief postAppCardWidget is the concrete implementation of the AppCardWidget
	 * @note this is the main function to post the message to the toast
	 */
	void postAppCardWidget();
	LocalWeatherLightFetcher* localFetcher { nullptr };
};

#endif // LOCALWEATHERCARD_H
