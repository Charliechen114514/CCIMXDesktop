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

    const std::vector<ToolLeftWidgets::ToolButtonInstallPackage> packages = {
        { "This", QIcon(), [] { qDebug() << "Hello, world!"; } },
        { "is", QIcon(), [] { qDebug() << "Hello, world2!"; } },
        { "a", QIcon(), [] { qDebug() << "Hello, world2!"; } },
        { "demo", QIcon(), [] { qDebug() << "Hello, world2!"; } }
    };

    for (const auto& package : packages) {
        left->install_toolbuttons(package);
    }
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
