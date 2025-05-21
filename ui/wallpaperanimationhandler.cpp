#include "wallpaperanimationhandler.h"
#include "core/coretools.h"
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QPropertyAnimation>

WallPaperAnimationHandler::WallPaperAnimationHandler(QObject* parent)
    : QObject { parent } { }

void WallPaperAnimationHandler::
    process_switch(
        const DesktopMainWindow::WallPaperGroup& group,
        ImagePoolEngine& engine) {
    /* Engines precheck */
    if (!engine.image_list)
        return; /* don't switch */
    if (engine.image_list->size() <= 1)
        return; /* no need to switch */
    /* don't set the invalid */
    QLabel* wallpaperlabel = group.wallpaperLabel;
    QLabel* bufferpaperlabel = group.bufferpaperLabel;
    if (!wallpaperlabel || !bufferpaperlabel)
        return;

	/* filled with def switcher if nullptr */
	if (!engine.selector) {
		engine.selector = [](QStringList* list) -> int {
			/* return randomly */
			return CoreTools::random_int(0, list->size() - 1);
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
		engine.selector(engine.image_list)));

	wallpaperlabel->setPixmap(next_one);
	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(bufferpaperlabel);
	bufferpaperlabel->setGraphicsEffect(opacityEffect);

	QPropertyAnimation* fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
	fadeOut->setDuration(2000);
	fadeOut->setStartValue(1.0);
	fadeOut->setEndValue(0.0);

	connect(fadeOut, &QPropertyAnimation::finished, [=]() {
		bufferpaperlabel->hide();
		bufferpaperlabel->setGraphicsEffect(nullptr);
		fadeOut->deleteLater();
	});

	fadeOut->start();
}
