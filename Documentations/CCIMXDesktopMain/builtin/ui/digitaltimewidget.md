# 模块名称 DigitalTimeWidget

## 功能概述

DigitalTimeWidget 是一个基于 QWidget 的数字时钟显示组件，用于在界面上以数字形式呈现时间。它可以与 ClockWidget 同步，当 ClockWidget 发出时间更新信号时，DigitalTimeWidget 将接收并存储新的时间值，然后在自身重绘过程中将当前时间以字符串方式绘制到窗口上。

## 类结构说明

 DigitalTimeWidget 继承自 QWidget，其构造函数接受一个可选的父窗口指针，用于将该组件嵌入到其它布局或窗口中。该组件内部维护了一个 QTime 类型的成员 stored_time，用以保存最新的时间数据，以及一个指向 ClockWidget 的指针 clk_widget，用于接收时钟更新信号。

## 接口方法说明

 构造函数 DigitalTimeWidget(QWidget *parent)
 在构造过程中，组件完成 QWidget 基类的初始化，并将内部时间设置为默认值 00:00:00，同时将时钟指针置空。用户可根据需要将父控件传入，从而让布局管理器正确处理组件大小和位置。

bindClockWidget(ClockWidget* clock)
 该方法用于将外部的 ClockWidget 对象与本组件进行绑定。调用后，DigitalTimeWidget 会将自身的 process_time_update 槽函数连接到 ClockWidget 的 time_update 信号上，以便在时钟更新时自动触发时间存储和界面刷新流程。

process_time_update(QTime process_time)
 这是一个公共槽函数，用于接收来自 ClockWidget 的时间更新信号。函数体中将传入的时间参数赋值给 stored_time，并调用 update() 触发组件的重绘，从而更新显示的数字时间。

paintEvent(QPaintEvent *event)
 在每次重绘时，组件会覆盖 QWidget 的 paintEvent 方法，通过 QPainter 在可用绘图区域内以合适的字体和位置绘制 stored_time 对应的文本。绘制逻辑应包含对字体大小、文本对齐方式以及背景透明度的控制，以保证数字时钟既清晰可读又与界面风格保持一致。

## 私有成员说明

 stored_time 保存当前要显示的时间值，初始为 00:00:00；clk_widget 用于引用外部 ClockWidget 实例，绑定后可持续接收时间更新信号。

## 说明

 在界面初始化阶段，先创建 ClockWidget 并将其添加到窗口。随后创建 DigitalTimeWidget，将界面指针传入其构造函数。调用 bindClockWidget 并将 ClockWidget 实例传入，即可在 ClockWidget 发出 time_update 信号时自动更新数字显示，无需额外手动刷新逻辑。