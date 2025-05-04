#include "StackPageSwitcher.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QStackedWidget>

void StackpageSwitcherAnimation::process_animations(
	QStackedWidget* binding_widget, AnimationInfo* animation_info) {
	QWidget* currentPage = binding_widget->currentWidget();
	QWidget* nextPage = binding_widget->widget(animation_info->new_index);

	int moving_width = animation_info->toLeft ? binding_widget->width() : -binding_widget->width();
	nextPage->move(moving_width, 0);
	nextPage->show();

	/* moves out */
	QPropertyAnimation* animCurrent = new QPropertyAnimation(currentPage, "pos");
	animCurrent->setDuration(300);
	animCurrent->setStartValue(currentPage->pos());
	animCurrent->setEndValue(QPoint(-moving_width, 0));

	/* moves in */
	QPropertyAnimation* animNext = new QPropertyAnimation(nextPage, "pos");
	animNext->setDuration(300);
	animNext->setStartValue(nextPage->pos());
	animNext->setEndValue(QPoint(0, 0));

	QParallelAnimationGroup* group = new QParallelAnimationGroup(binding_widget);
	group->addAnimation(animCurrent);
	group->addAnimation(animNext);

	connect(group, &QParallelAnimationGroup::finished, binding_widget, [=]() {
		binding_widget->setCurrentWidget(nextPage);
		currentPage->move(0, 0);
	});

	group->start(QAbstractAnimation::DeleteWhenStopped);
}
