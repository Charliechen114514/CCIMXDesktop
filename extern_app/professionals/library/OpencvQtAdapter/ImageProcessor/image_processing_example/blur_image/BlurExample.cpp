#include "BlurExample.h"
#include "BlurProcessor.h"
#include "CVImage.h"
#include "QtAdaptTools.h"
#include "ui_BlurExample.h"
BlurExample::BlurExample(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::BlurExample) {

	ui->setupUi(this);
    int total_steps = (MAX_KER_SZ - MIN_KER_SZ) / 2 + 1;
    ui->gaussain_kernel_size->setMaximum(total_steps - 1);
    ui->medianblursize->setMaximum(total_steps - 1);
    connect(ui->btn_control_widget, &ImageProcessingWidget::image_loaded,
            this, [this](const QImage& image) {
                ui->image_label->setImage(image);
            });

    connect(ui->btn_control_widget, &ImageProcessingWidget::request_processing,
            this, &BlurExample::process_blur);

    connect(ui->mean_kernelsize_bar, &QSlider::valueChanged,
            this, &BlurExample::process_meanblur);

    connect(ui->gaussain_blur_sigma_x, &QDoubleSpinBox::valueChanged,
            this, &BlurExample::process_guassainblur);
    connect(ui->gaussain_blur_sigma_y, &QDoubleSpinBox::valueChanged,
            this, &BlurExample::process_guassainblur);
    connect(ui->gaussain_kernel_size, &QSlider::valueChanged,
            this, &BlurExample::process_guassainblur);

    connect(ui->medianblursize, &QSlider::valueChanged,
            this, &BlurExample::process_medianblur);
    connect(ui->pushButton, &QPushButton::clicked,
            this, &BlurExample::process_filterblur);

    ui->btn_control_widget->process_direct_load(":/example_image/lena.jpg");
}

void BlurExample::process_blur() {
    process_medianblur();
    process_guassainblur();
    process_meanblur();
    process_filterblur();
}

BlurExample::~BlurExample() {
	delete ui;
}

void BlurExample::process_medianblur() {
    QImage image = ui->btn_control_widget->image().copy();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    MedianBlur blur;
    blur.package.kernel_size = ui->medianblursize->value() * 2 + MIN_KER_SZ;
    blur.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->MedianLabel->setImage(new_image);
}

void BlurExample::process_guassainblur() {
    QImage image = ui->btn_control_widget->image().copy();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    GuassainBlur blur;
    blur.package.kernel_size = ui->gaussain_kernel_size->value() * 2 + MIN_KER_SZ;
    blur.package.sigma_x = ui->gaussain_blur_sigma_x->value();
    blur.package.sigma_y = ui->gaussain_blur_sigma_y->value();
    blur.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->GaussainBlurLabel->setImage(new_image);
}

void BlurExample::process_meanblur() {
    QImage image = ui->btn_control_widget->image().copy();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    MeanBlur blur;
    blur.package.kernel_size = ui->mean_kernelsize_bar->value();
    blur.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->MeanLabel->setImage(new_image);
}

void BlurExample::process_filterblur() {
    QImage image = ui->btn_control_widget->image().copy();
    if (image.isNull()) {
        return;
    }
    CVImage cvImage = QtAdaptTools::fromRGBQImage(image);
    FilterBlur blur;
    blur.package.d = ui->filterd_slider->value();
    blur.package.sigma_color = ui->signma_color->value();
    blur.package.sigma_space = ui->sigma_space->value();
    blur.process(cvImage);
    QImage new_image = QtAdaptTools::toDisplayableImage(cvImage);
    ui->bilateralFilterLabel->setImage(new_image);
}
