#include "wallpaperanimationhandler.h"
#include "core/coretools.h"
#include "core/wallpaper/WallPaperEngine.h"
#include <QGraphicsOpacityEffect>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

namespace {
struct OpacityPackage {
    QObject* target;
    qreal start;
    qreal end;
    int duration;
    QEasingCurve curve;
};

// creating for the conv
QPropertyAnimation* createOpacityAnimation(const OpacityPackage&& package) {
    QPropertyAnimation* anim = new QPropertyAnimation(package.target, "opacity");
    anim->setDuration(package.duration);
    anim->setStartValue(package.start);
    anim->setEndValue(package.end);
    anim->setEasingCurve(package.curve);
    return anim;
}

struct MovePackage {
    QWidget* widget;
    QPoint start;
    QPoint end;
    int duration;
    QEasingCurve curve;
};

// creating for the conv
QPropertyAnimation* createMoveAnimation(const MovePackage&& package) {
    QPropertyAnimation* anim = new QPropertyAnimation(package.widget, "pos");
    anim->setDuration(package.duration);
    anim->setStartValue(package.start);
    anim->setEndValue(package.end);
    anim->setEasingCurve(package.curve);
    return anim;
}
}

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

    QPropertyAnimation* fadeOut = createOpacityAnimation({ opacityEffect, 1.0, 0.0, packages.durations, QEasingCurve::OutCubic });
    opacityEffect->setParent(fadeOut);

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

    QPoint offscreenRight = wallpaperPos + QPoint(size.width(), 0);
    QPoint offscreenLeft = wallpaperPos - QPoint(size.width(), 0);
    QPropertyAnimation* anim_old = createMoveAnimation({ wallpaperlabel, wallpaperPos, offscreenLeft, packages.durations, QEasingCurve::InOutCubic });
    QPropertyAnimation* anim_new = createMoveAnimation({ bufferpaperlabel, offscreenRight, wallpaperPos, packages.durations, QEasingCurve::InOutCubic });

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
