#include "SideBarWidget.h"
#include "ui_SideBarWidget.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

namespace SideBarUtilsTools {
void clearLayout(QLayout* layout) {
	if (!layout)
		return;

	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr) {
		if (item->widget()) {
			item->widget()->hide();
		} else {
			clearLayout(item->layout());
		}
	}
}
} // namespace SideBarUtilsTools

SideBarWidget::SideBarWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SideBarWidget) {
    ui->setupUi(this);
    __initMemory();
    __initConnection();
}

void SideBarWidget::switch_state() {
    setState(!hidden_state);
}

void SideBarWidget::switch_button_visible() {
    setButtonVisible(!ui->btn_operate->isVisible());
}

void SideBarWidget::removeLayout(Role r) {
	switch (r) {
	case Role::SideBar:
		SideBarUtilsTools::clearLayout(ui->widgetSiderBar->layout());
		break;
	case Role::MainSide:
		SideBarUtilsTools::clearLayout(ui->widget_mainside->layout());
		break;
	}
}

void SideBarWidget::setButtonVisible(bool visible) {
	ui->btn_operate->setVisible(visible);
	ui->btn_operate->setText(hidden_state ? ">" : "<");
}

void SideBarWidget::addLayout(const QWidgetList& widgetList,
                              Role r) {
    switch (r) {
    case Role::SideBar:
        ui->widgetSiderBar->setLayout(new QVBoxLayout(ui->widgetSiderBar));
        for (auto& w : widgetList) {
            ui->widgetSiderBar->layout()->addWidget(w);
        }
        break;
    case Role::MainSide:
        ui->widget_mainside->setLayout(new QVBoxLayout(ui->widget_mainside));
        for (auto& w : widgetList) {
            ui->widget_mainside->layout()->addWidget(w);
        }
        break;
    }
}

/* setTypes */
void SideBarWidget::setAnimationDuration(int duration) {
	animation_button->setDuration(duration);
	animation_main->setDuration(duration);
	animation_side->setDuration(duration);
}
void SideBarWidget::setAnimationCurve(QEasingCurve::Type curve) {
	animation_button->setEasingCurve(curve);
	animation_main->setEasingCurve(curve);
	animation_side->setEasingCurve(curve);
}

void SideBarWidget::__initMemory() {
	animation_main = new QPropertyAnimation(ui->widget_mainside, "geometry");
	animation_main->setDuration(SideBarWidgetStaticConfig::ANIMATION_DURATION);
	animation_main->setEasingCurve(SideBarWidgetStaticConfig::ANIMATION_CURVE);
	animation_side = new QPropertyAnimation(ui->widgetSiderBar, "geometry");
	animation_side->setDuration(SideBarWidgetStaticConfig::ANIMATION_DURATION);
	animation_side->setEasingCurve(SideBarWidgetStaticConfig::ANIMATION_CURVE);
	animation_button = new QPropertyAnimation(ui->btn_operate, "geometry");
	animation_button->setDuration(
		SideBarWidgetStaticConfig::ANIMATION_DURATION);
	animation_main->setDuration(SideBarWidgetStaticConfig::ANIMATION_DURATION);
	group = new QParallelAnimationGroup(this);
	group->addAnimation(animation_main);
	group->addAnimation(animation_side);
	group->addAnimation(animation_button);
}

void SideBarWidget::__initConnection() {
	connect(ui->btn_operate, &QPushButton::clicked, this,
			[this]() { setState(!hidden_state); });
	connect(group, &QParallelAnimationGroup::finished, this, [this] {
		ui->widgetSiderBar->setVisible(!hidden_state);
		// have no better idea :(, to update the layout
		resize(size().width() + 1, size().height() + 1);
		resize(size().width() - 1, size().height() - 1);
	});
}

void SideBarWidget::do_hide_animations() {
	animation_side->setStartValue(ui->widgetSiderBar->geometry());
	/* move to the hidden place */
	animation_side->setEndValue(
		QRect(-ui->widgetSiderBar->width(), ui->widgetSiderBar->y(),
			  ui->widgetSiderBar->width(), ui->widgetSiderBar->height()));

	animation_button->setStartValue(ui->btn_operate->geometry());
	animation_button->setEndValue(QRect(0, ui->btn_operate->y(),
										ui->btn_operate->width(),
										ui->btn_operate->height()));

	animation_main->setStartValue(ui->widget_mainside->geometry());
	animation_main->setEndValue(QRect(
		ui->btn_operate->width(), ui->widget_mainside->y(),
		width() - ui->btn_operate->width(), ui->widget_mainside->height()));

	ui->btn_operate->setText(">");
	group->start();
}
void SideBarWidget::do_show_animations() {
	animation_side->setStartValue(ui->widgetSiderBar->geometry());
	/* move to the hidden place */
	animation_side->setEndValue(QRect(0, ui->widgetSiderBar->y(),
									  ui->widgetSiderBar->width(),
									  ui->widgetSiderBar->height()));

	animation_button->setStartValue(ui->btn_operate->geometry());
	animation_button->setEndValue(
		QRect(ui->widgetSiderBar->width(), ui->btn_operate->y(),
			  ui->btn_operate->width(), ui->btn_operate->height()));

	animation_main->setStartValue(ui->widget_mainside->geometry());
	animation_main->setEndValue(
		QRect(ui->widgetSiderBar->width() + ui->btn_operate->width(),
			  ui->widget_mainside->y(),
			  width() - ui->btn_operate->width() - ui->widgetSiderBar->width(),
			  ui->widget_mainside->height()));
	ui->btn_operate->setText("<");
	ui->widgetSiderBar->setVisible(true);
	group->start();
}

SideBarWidget::~SideBarWidget() {
	delete ui;
}
