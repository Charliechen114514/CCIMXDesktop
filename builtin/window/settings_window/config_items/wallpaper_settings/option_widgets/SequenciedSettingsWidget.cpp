#include "SequenciedSettingsWidget.h"
#include "../utils/ImageListViewWidget.h"
#include "core/coretools.h"
#include "core/wallpaper/WallPaperUtilsColliections.h"
#include "ui/UiTools/easing_curve_combox_setupper/EasingCurveComboxBoxSetuper.h"
#include "ui_SequenciedSettingsWidget.h"
SequenciedSettingsWidget::SequenciedSettingsWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::SequenciedSettingsWidget) {
	ui->setupUi(this);
    viewer = new ImageListViewer(this);
    connect(viewer, &ImageListViewer::imageClicked,
            this, &SequenciedSettingsWidget::process_clicked_pixmaps);
    connect(this, &SequenciedSettingsWidget::loadToImageListView,
            viewer, &ImageListViewer::setImageLists);
    connect(ui->switching_trigger, &QSpinBox::valueChanged, this,
            &SequenciedSettingsWidget::setWallpaper_switch_time);
    connect(ui->animation_spinbox, &QSpinBox::valueChanged, this,
            &SequenciedSettingsWidget::setAnimation_duration);
    ui->image_displayerWidgets->layout()->addWidget(viewer);
    using namespace UiTools::EasingCurveComboBoxSetuper;
    setupComboBox(ui->animate_type);
    connect(ui->animate_type, &QComboBox::currentTextChanged, this, [this]() {
        using UiTools::EasingCurveComboBoxSetuper::selectedEasing;
        curve = selectedEasing(ui->animate_type);
    });
}

SequenciedSettingsWidget::~SequenciedSettingsWidget() {
	delete ui;
}

void SequenciedSettingsWidget::flush_with_non_path(const QStringList& image_paths) {
    image_lists = image_paths;
    emit loadToImageListView(image_lists);
}

void SequenciedSettingsWidget::flush_images(const QString& list) {
    this->image_lists_folders = list;
    QStringList tempLists = CoreTools::enumeratefiles(list, WallPaperUtilsColliections::prefixs());
    flush_with_non_path(tempLists);
}

QString SequenciedSettingsWidget::folders_image_path() const {
    return image_lists_folders;
}

QStringList SequenciedSettingsWidget::get_image_lists() const {
    return image_lists;
}

void SequenciedSettingsWidget::process_clicked_pixmaps(const QString& map) {
    ui->clicked_label->setPixmap(QPixmap(map));
}

void SequenciedSettingsWidget::apply_new_images() {
    emit reinstalls(image_lists);
}

void SequenciedSettingsWidget::enforceTimeConstraint() {
    int minValue = ui->animation_spinbox->minimum();
    int maxValue = ui->switching_trigger->maximum();

    animation_duration = std::clamp(animation_duration, minValue, maxValue);
    wallpaper_switch_time = std::clamp(wallpaper_switch_time, minValue, maxValue);

    if (wallpaper_switch_time <= animation_duration) {
        wallpaper_switch_time = animation_duration + 1000;
    }

    if (wallpaper_switch_time > maxValue) {
        wallpaper_switch_time = maxValue;
        animation_duration = std::min(wallpaper_switch_time - 1000, maxValue);
    }

    blockSignals(true);
    ui->animation_spinbox->setValue(animation_duration);
    ui->switching_trigger->setValue(wallpaper_switch_time);
    blockSignals(false);
}

int SequenciedSettingsWidget::getAnimation_duration() const {
    return animation_duration;
}

int SequenciedSettingsWidget::getWallpaper_switch_time() const {
    return wallpaper_switch_time;
}

void SequenciedSettingsWidget::setAnimation_duration(int newAnimation_duration) {
    animation_duration = newAnimation_duration;
    enforceTimeConstraint();
}

void SequenciedSettingsWidget::setWallpaper_switch_time(int newWallpaper_switch_time) {
    wallpaper_switch_time = newWallpaper_switch_time;
    enforceTimeConstraint();
}

QEasingCurve SequenciedSettingsWidget::get_easingcurve_type() const {
    return curve;
}
