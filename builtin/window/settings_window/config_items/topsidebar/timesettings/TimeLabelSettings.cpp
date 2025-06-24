#include "TimeLabelSettings.h"
#include "DefaultLabelName.h"
#include "TopSideBarWidget.h"
#include "core/labelStyler/LabelStyleReader.h"
#include "core/labelStyler/LabelStyler.h"
#include "desktopmainwindow.h"
#include "ui/UiTools/font_info_formater/FontInfoFormarter.h"
#include "ui/topstatusbar/time_display/TimeDisplayIconWidget.h"
#include "ui_TimeLabelSettings.h"
#include <QFontDialog>
TimeLabelSettings::TimeLabelSettings(DesktopMainWindow* parent)
    : QWidget(parent)
    , ui(new Ui::TimeLabelSettings) {
	ui->setupUi(this);

    auto label_required = parent->topSideBar()->queryFromName(TopStatusBar_LabelName::TIME);
    if (!label_required) {
        qWarning() << "Can not find the operating label!";
        setEnabled(false);
        return;
    }
    TimeDisplayIconWidget* widget = dynamic_cast<TimeDisplayIconWidget*>(label_required);
    if (!widget) {
        qWarning() << "Missing cases of the widgets";
        setEnabled(false);
        return;
    }

    operatingTimeLabel = widget->displayedLabel();
    settingsPack.font = LabelStyleReader::font(this->operatingTimeLabel);
    settingsPack.fontColor = LabelStyleReader::textColor(this->operatingTimeLabel);
    process_preview();
    connect(ui->btn_select_color, &ColorSelectWidget::colorSelected,
            this, [this](QColor color) {
                settingsPack.fontColor = color;
                process_preview();
            });
    connect(ui->btn_select_font, &QPushButton::clicked,
            this, [this]() {
                bool ok = false;
                QFont f = QFontDialog::getFont(&ok, settingsPack.font, this);
                if (!ok)
                    return;
                settingsPack.font = f;
                process_preview();
            });
    connect(ui->btn_apply, &QPushButton::clicked,
            this, &TimeLabelSettings::process_apply);
}

TimeLabelSettings::~TimeLabelSettings() {
	delete ui;
}

void TimeLabelSettings::process_preview() {
    LabelStyler styler;
    styler.label = ui->label;
    styler.setFont(settingsPack.font);
    styler.setTextColor(settingsPack.fontColor);
    using UiTools::FontFormater::describeFont;
    ui->font_info->setPlainText(describeFont(settingsPack.font));
}

void TimeLabelSettings::process_apply() {
    LabelStyler styler;
    styler.label = operatingTimeLabel;
    styler.setFont(settingsPack.font);
    styler.setTextColor(settingsPack.fontColor);
}
