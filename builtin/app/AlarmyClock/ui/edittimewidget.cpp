#include "edittimewidget.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QProxyStyle>
#include <QTimeEdit>
#include <QVBoxLayout>

class CustomProxyStyle : public QProxyStyle {
public:
    using QProxyStyle::QProxyStyle;

    void drawPrimitive(PrimitiveElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const override {
        if (element == PE_FrameLineEdit) {
            // 不绘制QTimeEdit的边框
            return;
        }
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
};

EditTimeWidget::EditTimeWidget(QWidget* parent)
    : QWidget(parent) {
    setupUi();
    setupStyle();
    connect(timeEdit, &QTimeEdit::timeChanged, this, []() {
        qDebug() << "Time has changed";
    });
    connect(toggleSwitch, &QCheckBox::toggled, this, []() {
        qDebug() << "Cout the time!";
    });
}

EditTimeWidget::~EditTimeWidget() {
    delete timeEdit->style();
}

void EditTimeWidget::setupUi() {
    // --- 实例化UI组件 ---
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm");
    timeEdit->setTime(QTime::currentTime());
    timeEdit->setStyle(new CustomProxyStyle()); // 应用自定义Style

    toggleSwitch = new QCheckBox(this);
    toggleSwitch->setChecked(false); // 默认开启

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(timeEdit);
    mainLayout->addWidget(toggleSwitch);
}

void EditTimeWidget::setupStyle() {
    setObjectName("EditTimeWidget");
    QString styleSheet = R"(

/* === QTimeEdit 样式 === */
QTimeEdit {
    background-color: transparent;
    border: none;
    font-size: 26px;
    font-weight: 500;
    color: #333333;
    padding: 5px;
}

/* 高亮焦点时 */
QTimeEdit:focus {
    background-color: #f0f0f0;
    border-radius: 5px;
}

/* 隐藏上下箭头按钮 */
QTimeEdit::up-button, QTimeEdit::down-button {
    width: 0px;
    height: 0px;
    margin: 0;
    padding: 0;
    border: none;
}
QTimeEdit::up-arrow, QTimeEdit::down-arrow {
    image: none;
}

/* === iOS 风格开关 (QCheckBox) === */
QCheckBox::indicator {
    width: 30px;
    height: 30px;
    border-radius: 15px;
    border: 1px solid #E5E5E5;
}

/* 打开状态 */
QCheckBox::indicator:checked {
    background-color: #34C759;
    border-color: #34C759;
}

/* 滑块位置模拟 */
QCheckBox::indicator:unchecked {
    padding-left: 2px;
}

QCheckBox::indicator:checked {
    padding-left: 22px;
}

/* 滑块圆形效果 */
QCheckBox::indicator {
    qproperty-iconSize: 10px 10px; /* 保证滑块大小 */
    background-clip: content;
    border-radius: 15px;
}

    )";
    this->setStyleSheet(styleSheet);
}

// --- 公共接口实现 ---

void EditTimeWidget::setTime(const QTime& time) {
    QTime old_time = timeEdit->time();
    timeEdit->setTime(time);
    emit timeChanged(old_time, time);
}

QTime EditTimeWidget::time() const {
    return timeEdit->time();
}

void EditTimeWidget::setAlarmEnabled(bool enabled) {
    toggleSwitch->setChecked(enabled);
    emit alarmEnabledChanged(enabled);
}

bool EditTimeWidget::isAlarmEnabled() const {
    return toggleSwitch->isChecked();
}
