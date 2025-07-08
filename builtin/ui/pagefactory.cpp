#include "pagefactory.h"
#include "app_wrapper/pagesetuper.h"
#include "builtin/gadgets/larger_card/DateShowCard.h"
#include "builtin/gadgets/larger_card/system_state/DiskUsageCardWidget.h"
#include "builtin/page/homepage.h"
#include "desktopmainwindow.h"
#include "ui/appcardwidget.h"
#include "ui/card_stack/CardStackWidget.h"
#include "ui/internal_calendar/ModernCalendarWidget.h"
#include <QLabel>
/* create a homepage */
QWidget* PageFactory::build_home_page(DesktopMainWindow* mainWindow) {
	HomePage* homePage = new HomePage(mainWindow);
    CardStackWidget* widget = homePage->card_stack_widget();
    widget->addWidget(new ModernCalendarWidget(homePage));
    widget->addWidget(new DateShowCard(homePage));
    widget->addWidget(new DiskUsageCardWidget(homePage));
    widget->setablility_of_autoSwitch(false);
	/* build homepage app cards here */
	mainWindow->app_cards << PageFactory::place_appcards_in_empty_widgets(
        mainWindow,
        homePage->expected_appcards_widgets());
    for (const auto& each : std::as_const(mainWindow->app_cards)) {
        each->invoke_textlabel_stylefresh();
    }
	return homePage;
}

#include "builtin/core/netability_scanner/NetAbilityScanner.h"
#include "builtin/gadgets/localweathercard.h"
#include "builtin/gadgets/netcardgadget.h"
#include <QGridLayout>
QList<AppCardWidget*> PageFactory::
    place_appcards_in_empty_widgets(
        DesktopMainWindow* mainWindow, QWidget* placed) {
    if (!placed->layout()) {
        QGridLayout* gridLayout = new QGridLayout(placed);
        placed->setLayout(gridLayout);
    }

    /*
     *  qobject_cast is performance better then dynamic_cast
     *  due to the RTTI and qt_meta's performance differs
     */
    QGridLayout* gridLayout = qobject_cast<QGridLayout*>(placed->layout());
    gridLayout->setSpacing(3);
    gridLayout->setContentsMargins(2, 2, 2, 2);
	if (!gridLayout)
		return {}; // not pass the layout check

	QList<AppCardWidget*> app_cards;
	int row = 0;
	int col = 0;

	/* netcards build */
	NetCardGadget* netcard = new NetCardGadget(mainWindow->desktop_toast(), placed);
    QObject::connect(mainWindow->netAbilityScanner(), &NetAbilityScanner::postStatus,
                     netcard, &NetCardGadget::process_once_fresh);
    gridLayout->addWidget(netcard, row, col);
	col++;
	app_cards << netcard;

	LocalWeatherCard* weather_card = new LocalWeatherCard(mainWindow->desktop_toast(), placed);
	gridLayout->addWidget(weather_card, row, col);
	col++;
	app_cards << weather_card;
	return app_cards;
}
