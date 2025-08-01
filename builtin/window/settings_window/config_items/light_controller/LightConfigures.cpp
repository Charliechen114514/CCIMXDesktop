#include "LightConfigures.h"
#include "builtin/core/backlight/BackLightControllerSingleton.h"
#include "builtin/core/backlight/BacklightController.h"
#include "ui_LightConfigures.h"
LightConfigures::LightConfigures(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LightConfigures) {
    ui->setupUi(this);
    controller = BackLightControllerSingleton::instance();
    setLightLevel(controller->lightLevel());

    ui->light_setterbar->setMaximum(controller->max_level());
    ui->light_setterbar->setMinimum(controller->min_level());

    connect(ui->light_setterbar, &QSlider::valueChanged,
            this, [this](int value) {
                qInfo() << "set the light level at" << value;
                setLightLevel(value);
            });
    connect(ui->btn_set_min, &QPushButton::clicked,
            this, [this]() {
                qInfo() << "set the light level at min level";
                setLightLevel(controller->min_level());
            });

    connect(ui->btn_set_max, &QPushButton::clicked,
            this, [this]() {
                qInfo() << "set the light level at max level";
                setLightLevel(controller->max_level());
            });

    connect(ui->btn_mid, &QPushButton::clicked,
            this, [this]() {
                int level = (controller->max_level() + controller->min_level()) / 2;
                setLightLevel(level);
            });
}

LightConfigures::~LightConfigures() {
	delete ui;
}

void LightConfigures::setLightLevel(int level) {
    controller->setLightLevel(level);
    ui->light_setterbar->setValue(level);
    post_hooks_of_value_session();
}

void LightConfigures::post_hooks_of_value_session() {

    int current_light_level = controller->lightLevel();
    ui->light_indicator->setText(QString("Light Level: %1").arg(current_light_level));
}
