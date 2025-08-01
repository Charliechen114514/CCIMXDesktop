#include "FastSettingsWidget.h"
#include "builtin/core/backlight/BackLightControllerSingleton.h"
#include "builtin/core/backlight/BacklightController.h"
#include "ui_FastSettingsWidget.h"
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
FastSettingsWidget::FastSettingsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FastSettingsWidget)
    , backlight_controller(BackLightControllerSingleton::instance()) {
    ui->setupUi(this);
    // adjust places
    resize(parent->width(), parent->height());
    move(0, -height());
    hide();

    // effects
    auto* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(30);
    shadow->setOffset(0, 6);
    shadow->setColor(QColor(0, 0, 0, 120));
    setGraphicsEffect(shadow);

    setup_light_settings();

    connect(ui->btn_hide, &QPushButton::clicked,
            this, &FastSettingsWidget::slideUp);
}

void FastSettingsWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bg(180, 210, 255, 160);
    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    painter.fillPath(path, bg);
}

void FastSettingsWidget::setup_light_settings()
{
    ui->light_slider->setMaximum(backlight_controller->max_level());
    ui->light_slider->setMinimum(backlight_controller->min_level());
    connect(ui->light_slider, &QSlider::valueChanged,
            this, [this](int level){
                backlight_controller->setLightLevel(level);
            });
}


void FastSettingsWidget::slideDown() {
    if (isVisible()) return;
    qDebug() << "Running Slider Show up";
    raise();
    show();
    QRect startRect = geometry();
    QRect endRect = QRect(x(), 0, parentWidget()->width(), parentWidget()->height());

    QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(300);
    anim->setStartValue(startRect);
    anim->setEndValue(endRect);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void FastSettingsWidget::slideUp() {
    if (!isVisible()) return;
    qDebug() << "Running Slider Hide up";
    QRect startRect = geometry();
    QRect endRect = QRect(x(), -height(), parentWidget()->width(), parentWidget()->height());

    QPropertyAnimation* anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(300);
    anim->setStartValue(startRect);
    anim->setEndValue(endRect);
    anim->setEasingCurve(QEasingCurve::InCubic);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, &QPropertyAnimation::finished, this, &FastSettingsWidget::hide);
}


FastSettingsWidget::~FastSettingsWidget() {
	delete ui;
}
