#include "DrawerWindow.h"
#include "SaveWindow.h"
#include "core/SimpleDrawingScene.h"
#include "settings.h"
#include "ui_DrawerWindow.h"
#include <QColorDialog>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
namespace {
void addWidgetsInGridLayout(QGridLayout* layout, const QList<QPushButton*>& widgets) {
	int count = widgets.size();
	int cols = std::ceil(std::sqrt(count));
	int rows = std::ceil(static_cast<double>(count) / cols);

	int index = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (index >= count)
				return;
			layout->addWidget(widgets[index++], r, c);
		}
	}
}

QString formatColor(const QColor& c) {
	return QString("Color: (%1, %2, %3)").arg(c.red()).arg(c.green()).arg(c.blue());
}

}

DrawerWindow::DrawerWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DrawerWindow) {
	ui->setupUi(this);
	setMouseTracking(true);
	saveWindow = new SaveWindow(this);
	setup_enable_drawings();
	setup_settings();
	init_connections();
}

SimpleDrawingScene* DrawerWindow::scene_instance() {
	return ui->draw_widget->scene_instance();
}

void DrawerWindow::init_connections() {
	connect(ui->actionredo, &QAction::triggered,
			ui->draw_widget->scene_instance(), &SimpleDrawingScene::redo);
	connect(ui->actionundo, &QAction::triggered,
			ui->draw_widget->scene_instance(), &SimpleDrawingScene::undo);
	connect(ui->actionedit, &QAction::triggered,
			scene_instance(), [this]() {
				scene_instance()->setMode(SimpleDrawingScene::DrawingMode::EditMode);
			});
	connect(ui->actiondraw, &QAction::triggered,
			scene_instance(), [this]() {
				scene_instance()->setMode(SimpleDrawingScene::DrawingMode::DrawingMode);
			});
	connect(ui->actionquit, &QAction::triggered, this, &DrawerWindow::close);
}

void DrawerWindow::setup_enable_drawings() {
	QWidget* shapeWidget = new QWidget(this);
	QGridLayout* l = new QGridLayout(shapeWidget);
	static QList<QPair<QPair<QString, QString>, std::function<void()>>> shapeActions = {
		{ { "Line", ":/icons/line.png" },
		  [this]() { scene_instance()->setItemType(
						 SimpleDrawingScene::SupportItemItem::Line); } },
		{ { "Ellipse", ":/icons/ellipse.png" },
		  [this]() { scene_instance()->setItemType(
						 SimpleDrawingScene::SupportItemItem::Ellipse); } },
		{ { "Rect", ":/icons/rect.png" },
		  [this]() { scene_instance()->setItemType(
						 SimpleDrawingScene::SupportItemItem::Rect); } },
		{ { "Freehand", ":/icons/freehand.png" },
		  [this]() { scene_instance()->setItemType(
						 SimpleDrawingScene::SupportItemItem::FreeHand); } }
	};

	QList<QPushButton*> buttons;

	for (const auto& pack : shapeActions) {
		QPushButton* button = new QPushButton(this);
		button->setText(pack.first.first);
		button->setIcon(QIcon(pack.first.second));
		connect(button, &QPushButton::clicked, this, pack.second);
		buttons << button;
	}
	addWidgetsInGridLayout(l, buttons);
	shapeWidget->setLayout(l);
	ui->toolBar->addWidget(shapeWidget);

	QPushButton* saveBtn = new QPushButton(this);
	saveBtn->setIcon(QIcon(":/icons/save.png"));
	saveBtn->setText("Save");
	connect(saveBtn, &QPushButton::clicked, this, [this]() {
		saveWindow->bindImage(scene_instance()->exportImage());
		saveWindow->show();
	});
	ui->toolBar->addWidget(saveBtn);
}

void DrawerWindow::setup_settings() {
	QSlider* penWidthSiler = new QSlider(this);
	penWidthSiler->setMinimum(1);
	penWidthSiler->setMaximum(10);
	QLabel* widthLabel = new QLabel(this);
	penWidthSiler->setValue(DEF_PEN_WIDTH);
	widthLabel->setText(QString("%1 px").arg(DEF_PEN_WIDTH));
	connect(penWidthSiler, &QSlider::valueChanged, penWidthSiler,
			[this, widthLabel](const int value) {
				scene_instance()->setPenWidth(value);
				widthLabel->setText(QString("%1 px").arg(value));
			});

	ui->toolBar->addWidget(penWidthSiler);
	ui->toolBar->addWidget(widthLabel);

	QPushButton* colorButton = new QPushButton(this);
	QLabel* color_label = new QLabel(this);
	color_label->setText(formatColor(DEF_PEN_COLOR));
	colorButton->setText("Set Pen Color");
	colorButton->setIcon(QIcon(":/icons/color.png"));
	connect(colorButton, &QPushButton::clicked, this, [this, color_label]() {
		QColor c = QColorDialog::getColor();
		if (c.isValid()) {
			scene_instance()->setColor(c);
			color_label->setText(formatColor(c));
		}
	});

	ui->toolBar->addWidget(colorButton);
	ui->toolBar->addWidget(color_label);
}

DrawerWindow::~DrawerWindow() {
	delete ui;
}
