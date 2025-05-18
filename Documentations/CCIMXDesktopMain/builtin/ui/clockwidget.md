# 模块名称 ClockWidget

ClockWidget 是一个自定义的时钟组件，继承自 QWidget，用于在 Qt 界面中以矢量绘制方式动态显示模拟时钟。该组件内部使用 QTimer 定时器驱动，通过重载 paintEvent 方法按帧更新时钟外观，并通过 time_update 信号向其他需要同步时间的组件广播当前时间。

## 构造与析构

 ClockWidget 在构造时接收可选的父级 QWidget 指针，用于将该组件嵌入到父窗口中。构造函数内部会创建并启动一个 QTimer，定时触发内部 update 调用，从而使时钟界面以可视化的方式不断刷新。析构函数负责清理 UI 指针和定时器资源，以防止内存泄漏。

## 外部接口

 ClockWidget 通过 time_update 信号向外部发送当前时间，信号的参数类型为 QTime，便于其他组件捕获并同步显示或处理时间数据。组件不提供额外的公有方法，而是依赖重载的 sizeHint 方法为布局管理器提供首选尺寸值，在无显式约束时可使用该尺寸进行合理布局。

## 绘制流程

 ClockWidget 在每次定时器超时后调用 update，从而触发 paintEvent。在 paintEvent 中，组件首先绘制背景圆形表盘，然后通过 drawTicks 方法绘制小时刻度和分钟刻度，接着使用 drawHands 方法按当前时分秒计算指针旋转角度并绘制时针、分针和秒针，再通过 drawNumbers 方法在表盘边缘绘制数字标记，最后在中心绘制一个实心圆点。所有绘制操作均基于 QPainter，利用常量成员定义的尺寸和旋转角度确保时钟比例和样式一致。

## 常量与私有成员

 ClockWidget 内部定义了多组静态常量，用于指定默认组件大小、表盘直径、圆半径、刻度长度和宽度、指针长度以及数字与中心点位置等参数，保证了绘制逻辑的可维护性和可配置性。私有成员包括 ui 指针、内部定时器 internal_updater、当前时间 cur_time 以及绘制时调用的若干辅助方法，如 process_update_invokation、drawBackground、drawTicks、drawHands、drawNumbers 和 drawCenterDot，它们共同实现了时钟从数据更新到界面呈现的全流程。

# 注意

 将 ClockWidget 对象实例化并添加到布局后，无需额外手动刷新，内部定时器会自动更新时钟外观，并通过 time_update 信号定期向外部广播当前时间，其他组件可通过连接该信号实现时间联动或触发定时任务。