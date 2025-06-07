#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "ui_interface/params_sliderbar/FloatSlideBar.h"
#include "ui_interface/tool_left_widgets/ToolLeftWidgets.h"
#include <QSpacerItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
	ui->setupUi(this);
    Q_INIT_RESOURCE(sources); ///< we need to call this before the library loaded
    auto left = new ToolLeftWidgets(this);

    ToolLeftWidgets::ToolButtonInstallPackage package = {
        .name = "This",
        .icon = QIcon(),
        .callback = []() {
            qDebug() << "Hello, world!";
        }
    };
    left->install_toolbuttons(package);

    ToolLeftWidgets::ToolButtonInstallPackage package2 = {
        .name = "is",
        .icon = QIcon(),
        .callback = []() {
            qDebug() << "Hello, world2!";
        }
    };
    left->install_toolbuttons(package2);

    ToolLeftWidgets::ToolButtonInstallPackage package3 = {
        .name = "a",
        .icon = QIcon(),
        .callback = []() {
            qDebug() << "Hello, world2!";
        }
    };
    left->install_toolbuttons(package3);

    ToolLeftWidgets::ToolButtonInstallPackage package4 = {
        .name = "demo",
        .icon = QIcon(),
        .callback = []() {
            qDebug() << "Hello, world2!";
        }
    };
    left->install_toolbuttons(package4);
    ui->centralwidget->layout()->addWidget(left);
    ui->centralwidget->layout()->addItem(new QSpacerItem(300, 100));
    auto floatbar = new FloatSlider(Qt::Horizontal, this);
	ui->centralwidget->layout()->addWidget(floatbar);

	connect(floatbar, &FloatSlider::floatValueChanged, this, [](double f) {
		qDebug() << f;
	});
}

MainWindow::~MainWindow() {
	delete ui;
}
