#include "AboutMainWindow.h"
#include "./ui_AboutMainWindow.h"
#include "version.h"
#include <QTimer>
AboutMainWindow::AboutMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::AboutMainWindow) {
	ui->setupUi(this);
	show_mainWidget();

	init_connections();

	QTimer::singleShot(500, this, &AboutMainWindow::load_from_static_info);
}

void AboutMainWindow::show_readme() {
	hide_all();
	ui->readme_widget->show();
}

void AboutMainWindow::show_mainWidget() {
	hide_all();
	ui->mainAbout->show();
}

AboutMainWindow::~AboutMainWindow() {
	delete ui;
}

void AboutMainWindow::load_from_static_info() {
	ui->mainAbout->setTitle(DESKTOP_NAME);
	ui->mainAbout->setLogo(QIcon(":/logo/logo/CCIMXDesktopLogo.png"));
	ui->mainAbout->setMoreInfo(AUTHOR_INFO);
	ui->mainAbout->setDescriptions(ABOUT_DESCRIPT);
	ui->mainAbout->setVersionString(CCIMXDESKTOP_VERSION_FULL);

	ui->readme_widget->load_file(":/readme/doc/README.md");
}

void AboutMainWindow::hide_all() {
	for (const auto& widget : ui->MainDisplayWidget->children()) {
		QWidget* possible_widget = dynamic_cast<QWidget*>(widget);
		if (!possible_widget)
			continue;
		possible_widget->hide();
	}
}

void AboutMainWindow::init_connections() {
	connect(ui->btn_see_readme, &QPushButton::clicked,
			this, &AboutMainWindow::show_readme);
	connect(ui->btn_showMainPage, &QPushButton::clicked,
			this, &AboutMainWindow::show_mainWidget);
}
