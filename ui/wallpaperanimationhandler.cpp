#include "wallpaperanimationhandler.h"
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

WallPaperAnimationHandler::WallPaperAnimationHandler(QObject *parent)
    : QObject{parent}
{}

void WallPaperAnimationHandler::
process_switch(
        const DesktopMainWindow::WallPaperGroup &group,
        ImagePoolEngine &engine)
{
    if(!engine.image_list) return; /* don't switch */
    if(engine.image_list->size() <= 1) return; /* no need to switch */
    /* don't set the invalid */
    QLabel* wallpaperlabel = group.wallpaperLabel;
    QLabel* bufferpaperlabel = group.bufferpaperLabel;
    if(!wallpaperlabel || !bufferpaperlabel) return;

    /* filled with def switcher if nullptr */
    if(!engine.selector){
        engine.selector = [](QStringList* list) -> int {
            return std::rand() % list->size();
        };
    }

    /* set the auxi label for help */
    bufferpaperlabel->setPixmap(
        wallpaperlabel->pixmap(Qt::ReturnByValue));

    /* thus show the things */
    bufferpaperlabel->stackUnder(group.shoule_be_lower);
    bufferpaperlabel->show();

    /* then switch the true one */
    QPixmap next_one(engine.image_list->at(
        engine.selector(engine.image_list)
    ));

    wallpaperlabel->setPixmap(next_one);
    QGraphicsOpacityEffect *opacityEffect =
        new QGraphicsOpacityEffect(bufferpaperlabel);
    bufferpaperlabel->setGraphicsEffect(opacityEffect);

    QPropertyAnimation *fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
    fadeOut->setDuration(2000); // 动画时长，单位毫秒
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    connect(fadeOut, &QPropertyAnimation::finished, [=]() {
        bufferpaperlabel->hide();
        bufferpaperlabel->setGraphicsEffect(nullptr);
        fadeOut->deleteLater();
    });

    fadeOut->start();
}
