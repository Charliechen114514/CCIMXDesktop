#include "pagefactory.h"
#include "app_wrapper/pagesetuper.h"

#include "builtin/page/home_card_manager/HomeCardManager.h"
#include "builtin/page/homepage.h"
#include "desktopmainwindow.h"
#include "ui/appcardwidget.h"
#include <QLabel>

#include "builtin/gadgets/larger_card/DateShowCard.h"
#include "builtin/gadgets/larger_card/UserInfoCard.h"
#include "builtin/gadgets/larger_card/system_state/DiskUsageCardWidget.h"
#include "builtin/gadgets/larger_card/system_state/MemoryUsageCard.h"
#include "core/users/DesktopUserInfo.h"
#include "ui/internal_calendar/ModernCalendarWidget.h"
/* create a homepage */
HomePage* PageFactory::build_home_page(DesktopMainWindow* mainWindow) {
	HomePage* homePage = new HomePage(mainWindow);
    HomeCardManager* cardManager = homePage->homeCardManager();
    UserInfoCard* user_info_card = new UserInfoCard(homePage);
    DesktopUserInfo* info = mainWindow->get_user_info();
    QObject::connect(info, &DesktopUserInfo::user_init_ok,
                     user_info_card, &UserInfoCard::setUserInfo);
    UserInfo* user_info = info->get_info();
    if (user_info) {
        qDebug() << "User info is ready up!";
        user_info_card->setUserInfo(*user_info);
    }
    qDebug() << "Trying to insert card widgets";
    QWidgetList widgetList = {
        user_info_card,
        new ModernCalendarWidget(homePage),
        new DateShowCard(homePage),
        new DiskUsageCardWidget(homePage),
        new MemoryUsageCard(homePage)
    };
    qDebug() << "widgetList is prepared!";
    for (const auto& widget : widgetList) {
        cardManager->installWidget(widget);
    }
    qDebug() << "widgetList is inserted!";
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
