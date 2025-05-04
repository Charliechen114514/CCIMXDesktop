#include "desktopmainwindow.h"
#include "builtin/page/homepage.h"
#include "pagefactory.h"
#include "app_wrapper/pagesetuper.h"

/* create a homepage */
QWidget *PageFactory::build_home_page(DesktopMainWindow *mainWindow)
{
    HomePage*   homePage = new HomePage(mainWindow);
    /* build homepage app cards here */
    mainWindow->app_cards << PageFactory::place_appcards_in_empty_widgets(
        mainWindow,
        homePage->expected_appcards_widgets());
    return      homePage;
}

QList<AppWidget *> PageFactory::build_pesudo_page(
    const QString &pixpath, int how_many, DesktopMainWindow *mainWindow)
{
    QList<PageSetuper::PageSetupSessionRequest> req;
    for(int i = 0; i < how_many; i++)
    {
        req.push_back({pixpath, QString::number(i), nullptr});
    }

    return PageSetuper::create_one_app_only_page_append(
        mainWindow->stackedWidget(), mainWindow, req);
}


#include <QGridLayout>
#include "builtin/gadgets/netcardgadget.h"
#include "builtin/gadgets/localweathercard.h"
QList<AppCardWidget*> PageFactory::
place_appcards_in_empty_widgets(
        DesktopMainWindow *mainWindow, QWidget *placed)
{
    if(!placed->layout()){
        QGridLayout*    gridLayout = new QGridLayout(placed);
        placed->setLayout(gridLayout);
    }

    QGridLayout*    gridLayout = dynamic_cast<QGridLayout*>(placed->layout());
    if(!gridLayout) return {}; // not pass the layout check

    QList<AppCardWidget*> app_cards;
    int row = 0;
    int col = 0;

    /* netcards build */
    NetCardGadget*  netcard = new NetCardGadget(mainWindow->desktop_toast(), placed);
    gridLayout->addWidget(netcard, row, col);
    col++;
    app_cards << netcard;

    LocalWeatherCard*   weather_card = new LocalWeatherCard(mainWindow->desktop_toast(), placed);
    gridLayout->addWidget(weather_card, row, col);
    col++;
    app_cards << weather_card;
    return app_cards;
}



