#include "localweathercard.h"
#include "builtin/core/icm20608/icm20608_adapter.h"
#include "core/coretools.h"
#include "desktoptoast.h"
#include <QGraphicsDropShadowEffect>
#include <QLabel>
/**
 * @brief The PesudoLocalFetcher class works in upper machines
 * this is using in preview and test the ui behaviours
 */
struct PesudoLocalFetcher : public LocalWeatherLightFetcher {
public:
	/**
	 * @brief disable copy
     *
	 */
	Q_DISABLE_COPY(PesudoLocalFetcher);
	PesudoLocalFetcher() = default;
	/**
	 * @brief temp_min matters the rand gen's minimals
	 */
	static constexpr float temp_min = 20.0;
	/**
	 * @brief temp_max matters the rand gen's maximals
	 */
	static constexpr float temp_max = 25.0;

	float fetch_local_tempature() override {
		return CoreTools::random_float(temp_min, temp_max);
	}

	QString makeup_toast_message() override {
		return QString("pesudo x86 icm20608: %1 degree").arg(fetch_local_tempature());
	}
};

struct LocalFetcher : public LocalWeatherLightFetcher {
public:
	/**
	 * @brief disable copy
     *
	 */
	Q_DISABLE_COPY(LocalFetcher);
	/**
	 * @brief Construct a new Local Fetcher object
     *
	 */
	LocalFetcher() = default;

	float fetch_local_tempature() override {
		ICM20608AppData appdata;
		data_valid = icm20608_handle.get_package_sync(appdata);
		return appdata.temperature;
	}
	QString makeup_toast_message() override {
		float result = fetch_local_tempature();
		if (!data_valid) {
			return "Current icm20608 is unavailable!";
		}
		return QString("Current Temperature: %1 degree").arg(result);
	}

private:
	/*handles of the ICM20608*/
	ICM20608 icm20608_handle; ///< the raw handle
	bool data_valid { false }; ///< is the data valid?
};

LocalWeatherCard::
    LocalWeatherCard(DesktopToast* toast, QWidget* parent)
    : AppCardWidget(toast, parent) {

    setAttribute(Qt::WA_StyledBackground);
    setAutoFillBackground(true);
    setCurrentIcon(QPixmap(":/src/temperature.png"));
    setObjectName("AppCardWidget");
    setStyleSheet(R"(
    #AppCardWidget {
        border-radius: 20px;
        background: qlineargradient(
            x1: 0, y1: 0, x2: 0, y2: 1,
            stop: 0 #4A90E2,
            stop: 1 #1E3C72
        );
        padding: 12px;
    }
)");
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 160));
    setGraphicsEffect(shadow);
}

void LocalWeatherCard::invoke_preLaunch_work() {
#ifdef ARM_BUILD
	/* for arm, it is expected to use the real */
	this->localFetcher = new LocalFetcher;
#else
	/* for amd64/x86_64, there shell be no real icm20608 */
	this->localFetcher = new PesudoLocalFetcher;
#endif
    operate_comment_label();
}

void LocalWeatherCard::operate_comment_label() {
    setHelperFunction(QString("%1°C").arg(QString::number(localFetcher->fetch_local_tempature())));
}

void LocalWeatherCard::postAppCardWidget() {
	/* invoke the read session until we use */
    operate_comment_label();
	QString msg = localFetcher->makeup_toast_message();
	binding_toast->set_message(msg);
}

void LocalWeatherCard::setupSelfTextLabelStyle(
    QLabel* selfTextLabel) {
    selfTextLabel->setAlignment(Qt::AlignCenter);
    selfTextLabel->setStyleSheet(R"(
    QLabel {
        color: white;
        font-size: 12px;
        font-weight: bold;
    }
)");
}
