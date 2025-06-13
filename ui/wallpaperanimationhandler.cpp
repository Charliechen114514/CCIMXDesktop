#include "wallpaperanimationhandler.h"
#include "core/coretools.h"
#include "core/wallpaper/WallPaperEngine.h"
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

WallPaperAnimationHandler::WallPaperAnimationHandler(QObject* parent)
    : QObject { parent } { }

QString WallPaperAnimationHandler::ImagePoolEngine::default_selections(const QStringList& list) {
    return list.at(default_index(list));
}

int WallPaperAnimationHandler::ImagePoolEngine::default_index(const QStringList& list) {
    return CoreTools::random_int(0, list.size() - 1);
}

void WallPaperAnimationHandler::
    process_opacity_switch(
        const WallPaperEngine* group,
        ImagePoolEngine& engine,
        const AnimationSettingsPackage& packages) {
    /* Engines precheck */
    if (!engine.image_list)
        return; /* don't switch */
    if (engine.image_list->size() <= 1)
        return; /* no need to switch */
    /* don't set the invalid */
    QLabel* wallpaperlabel = group->wallpaperLabel;
    QLabel* bufferpaperlabel = group->bufferpaperLabel;
    if (!wallpaperlabel || !bufferpaperlabel)
        return;

	/* filled with def switcher if nullptr */
	if (!engine.selector) {
		engine.selector = [](QStringList* list) -> int {
			/* return randomly */
            return ImagePoolEngine::default_index(*list);
		};
	}

	/* set the auxi label for help */
	bufferpaperlabel->setPixmap(
        wallpaperlabel->pixmap(Qt::ReturnByValue));

	/* thus show the things */
    bufferpaperlabel->stackUnder(group->shoule_be_lower);
	bufferpaperlabel->show();

	/* then switch the true one */
	QPixmap next_one(engine.image_list->at(
        engine.selector(engine.image_list)));

	wallpaperlabel->setPixmap(next_one);
	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(bufferpaperlabel);
	bufferpaperlabel->setGraphicsEffect(opacityEffect);

	QPropertyAnimation* fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
    fadeOut->setDuration(packages.durations);
	fadeOut->setStartValue(1.0);
	fadeOut->setEndValue(0.0);

	connect(fadeOut, &QPropertyAnimation::finished, [=]() {
		bufferpaperlabel->hide();
		bufferpaperlabel->setGraphicsEffect(nullptr);
		fadeOut->deleteLater();
	});

	fadeOut->start();
}

void WallPaperAnimationHandler::process_movement_switch(
    const WallPaperEngine* group,
    ImagePoolEngine& engine,
    const AnimationSettingsPackage& packages) {

    if (!engine.image_list || engine.image_list->size() <= 1)
        return;

    QLabel* wallpaperlabel = group->wallpaperLabel;
    QLabel* bufferpaperlabel = group->bufferpaperLabel;
    if (!wallpaperlabel || !bufferpaperlabel)
        return;

    if (!engine.selector) {
        engine.selector = [](QStringList* list) -> int {
            return ImagePoolEngine::default_index(*list);
        };
    }

    QPixmap next_one(engine.image_list->at(engine.selector(engine.image_list)));
    QSize size = wallpaperlabel->size();
    QPoint wallpaperPos = wallpaperlabel->pos();
    bufferpaperlabel->setPixmap(next_one);
    bufferpaperlabel->stackUnder(group->shoule_be_lower);
    bufferpaperlabel->move(wallpaperPos.x() + size.width(), wallpaperPos.y());
    bufferpaperlabel->show();

    QPropertyAnimation* anim_old = new QPropertyAnimation(wallpaperlabel, "pos");
    anim_old->setDuration(packages.durations);
    anim_old->setStartValue(wallpaperPos);
    anim_old->setEndValue(QPoint(wallpaperPos.x() - size.width(), wallpaperPos.y()));

    QPropertyAnimation* anim_new = new QPropertyAnimation(bufferpaperlabel, "pos");
    anim_new->setDuration(packages.durations);
    anim_new->setStartValue(QPoint(wallpaperPos.x() + size.width(), wallpaperPos.y()));
    anim_new->setEndValue(wallpaperPos);

    QParallelAnimationGroup* group_anim = new QParallelAnimationGroup;
    group_anim->addAnimation(anim_old);
    group_anim->addAnimation(anim_new);

    connect(group_anim, &QParallelAnimationGroup::finished, [=]() {
        wallpaperlabel->move(wallpaperPos);
        wallpaperlabel->setPixmap(next_one);
        bufferpaperlabel->hide();
        group_anim->deleteLater();
    });

    group_anim->start();
}
