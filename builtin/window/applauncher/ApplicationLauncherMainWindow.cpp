#include "ApplicationLauncherMainWindow.h"
#include "app_wrapper/applicationwrapper.h"
#include "core/coretools.h"
#include "core/wallpaper/WallPaperUtilsColliections.h"
#include "desktopmainwindow.h"
#include "ui/appwidget.h"
#include "ui_ApplicationLauncherMainWindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
ApplicationLauncherMainWindow::ApplicationLauncherMainWindow(DesktopMainWindow* parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicationLauncherMainWindow) {
	ui->setupUi(this);
    this->window = parent;
    setup_internal_memory();
    process_according_per_checkbox();
    connect(ui->checkBox_for_perminant, &QCheckBox::clicked,
            this, &ApplicationLauncherMainWindow::process_according_per_checkbox);
    connect(ui->btn_launch_application, &QPushButton::clicked,
            this, &ApplicationLauncherMainWindow::process_depatch);
    connect(ui->exes, &QLineEdit::textChanged,
            this, &ApplicationLauncherMainWindow::collect_to_commands_depatched);
    connect(ui->arguments_lineedit, &QLineEdit::textChanged,
            this, &ApplicationLauncherMainWindow::collect_to_commands_depatched);
    connect(ui->btn_select, &QPushButton::clicked,
            this, [this]() {
                QString result = CoreTools::getExecutableFile(this);
                ui->exes->setText(result);
            });
    connect(ui->btn_select_image, &QPushButton::clicked,
            this, [this]() {
                QString loadable_string = QFileDialog::getOpenFileName(this, "select a icon map", ".",
                                                                       CoreTools::
                                                                           fromFiltersToFilterString(
                                                                               WallPaperUtilsColliections::prefixs()));
                if (loadable_string.isEmpty())
                    return;
                appWidget->setIcon(QPixmap(loadable_string));
            });
    connect(ui->btn_set_default_icon, &QPushButton::clicked,
            this, [this]() {
                appWidget->setIcon(QPixmap(":/icons/sources/def_icon.png"));
            });
    connect(ui->name_edit, &QLineEdit::textEdited, this, [this](const QString& buffer) {
        appWidget->setAppName(buffer);
    });
    connect(ui->actionquit, &QAction::triggered, this, &ApplicationLauncherMainWindow::close);
}

ApplicationLauncherMainWindow::~ApplicationLauncherMainWindow() {
	delete ui;
}

void ApplicationLauncherMainWindow::show() {
    if (!wrapper) {
        setup_appwrapper();
    }
    QMainWindow::show();
}

void ApplicationLauncherMainWindow::process_according_per_checkbox() {
    bool isPerminate = ui->checkBox_for_perminant->isChecked();
    ui->appwidget_settings->setVisible(isPerminate);
    if (!appWidget) {
        setup_appwidgets_settings();
    }
}

void ApplicationLauncherMainWindow::process_depatch() {
    if (ui->exes->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Please submit a executable path");
        return;
    }

    bool isPerminate = ui->checkBox_for_perminant->isChecked();
    shell_delete_current = !isPerminate;
    wrapper->set_app_path(ui->exes->text());
    QStringList arguments = ui->arguments_lineedit->text().split(" ");
    wrapper->install_args(arguments);
    this->hide();
    if (isPerminate) {
        appWidget->bindApp(wrapper);
    }
    wrapper->depatch_app();
}

void ApplicationLauncherMainWindow::collect_to_commands_depatched() {
    ui->command_displayings->setText(ui->exes->text() + ui->arguments_lineedit->text());
}

void ApplicationLauncherMainWindow::install_to_window() {
    window->install_for_new_dynamicpage(appWidget);
}

void ApplicationLauncherMainWindow::setup_internal_memory() {
    setup_appwrapper();
}

void ApplicationLauncherMainWindow::setup_appwrapper() {
    wrapper = new ApplicationWrapper(this, window);
    connect(wrapper, &ApplicationWrapper::self_depatched_success,
            this, &ApplicationLauncherMainWindow::process_post_success);
    connect(wrapper, &ApplicationWrapper::self_mission_finished,
            this, &ApplicationLauncherMainWindow::process_post_finish);
}

void ApplicationLauncherMainWindow::setup_appwidgets_settings() {
    appWidget
        = new AppWidget(QPixmap(":/icons/sources/def_icon.png"), "Defaults", this);
    ui->app_preview->layout()->addWidget(appWidget);
}

void ApplicationLauncherMainWindow::process_post_success() {
    // currently do nothing!
}

void ApplicationLauncherMainWindow::process_post_finish() {

    if (shell_delete_current) {
        disconnect(wrapper, &ApplicationWrapper::self_depatched_success,
                   this, &ApplicationLauncherMainWindow::process_post_success);
        disconnect(wrapper, &ApplicationWrapper::self_mission_finished,
                   this, &ApplicationLauncherMainWindow::process_post_finish);
        wrapper->deleteLater();
        wrapper = nullptr;
    } else {
        install_to_window();
        wrapper = nullptr; // release the handle

        appWidget = nullptr; // release the handle and moves to the mainWindow sessions
    }
}
