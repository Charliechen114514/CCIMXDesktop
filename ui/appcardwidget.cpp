#include "appcardwidget.h"
#include "ui_appcardwidget.h"

AppCardWidget::AppCardWidget(DesktopToast* toast, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::AppCardWidget) {
    ui->setupUi(this);
    /* toast is binding for post some message */
    binding_toast = toast;

    /* properties */
    ui->icons_label->setScaledContents(true);
    ui->icons_label->installEventFilter(this);
    ui->text_labels->installEventFilter(this);
    ui->icons_label->setStyleSheet(
        "QLabel {"
        "background: qlineargradient(spread:pad, "
        "x1:0, y1:0, x2:1, y2:1, "
        "stop:0 rgba(150, 150, 150, 100), "
        "stop:1 rgba(130, 130, 130, 255));"
        "border-radius: 15px;"
        "border: 2px solid rgba(0, 0, 0, 100);"
        "}");
}

/* set the icon */
void AppCardWidget::setCurrentIcon(const QPixmap& icons) {
    /* icons */
    ui->icons_label->setPixmap(icons);
}

void AppCardWidget::invoke_textlabel_stylefresh() {
    setupSelfTextLabelStyle(ui->text_labels);
}

void AppCardWidget::setHelperFunction(const QString& what) {
    ui->text_labels->setText(what);
}

AppCardWidget::~AppCardWidget() {
    delete ui;
}

bool AppCardWidget::eventFilter(QObject* watched, QEvent* event) {
    if (watched == ui->icons_label) {
        if (event->type() == QEvent::MouseButtonPress) {
            postAppCardWidget();
            return true;
        }
    }
    if (watched == ui->text_labels) {
        if (event->type() == QEvent::MouseButtonPress) {
            postAppCardWidget();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}
