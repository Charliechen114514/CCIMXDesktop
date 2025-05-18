# 模块名称 AppWidget

功能概述
 AppWidget 类继承自 QWidget，用于在界面上以图标加名称的卡片形式展示单个应用，它能够绑定后台的 ApplicationWrapper 实例以实现应用的调度和状态反馈，并通过信号机制向外部报告应用的存在与否状态。

类说明
 AppWidget 提供了对单个应用项从 UI 呈现到后台控制的完整封装。构造时需提供一个图标和名称，以便在界面上直观展示；随后可通过 bindApp 方法将一个 ApplicationWrapper 实例与之关联，从而在用户交互时触发应用的启动或停止逻辑。

构造与析构
 在调用 explicit AppWidget(const QPixmap& icon, const QString& name, QWidget *parent) 构造函数时，图标和名称会被设置到内部的 UI 组件中，同时可选的父窗口指针决定了在整个窗口层次结构中的归属。析构函数负责清理与 UI 相关的资源。

公有方法
 bindApp 会将外部传入的 ApplicationWrapper 指针存储到内部成员 app_internal，用于后续启动和状态检查；get_app 则返回已绑定的 ApplicationWrapper 指针以便外部进一步操作或查询。setIcon 和 setAppName 方法允许动态更新卡片的图标和名称，调用后会立即在界面上反映变化。setDummy 方法将当前卡片标记为“占位”状态，此时卡片可能显示为灰度或禁用交互；showIconOnly 则可切换为仅展示图标不显示名称，以配合不同的布局需求。icon 和 app_name 两个常量访问函数分别返回当前设置的图标和名称。

枚举类型
 AppWidget 定义了一个内部枚举 AppStatus，包含 AppOk（应用存在且可用）和 AppNonExsits（应用不存在或无法启动）两种状态，用于向外部报告当前应用是否可用。

信号
 postAppStatus(AppWidget::AppStatus status) 信号在内部执行应用调度检查后发出，携带上述枚举类型的值，可用于外部 UI 更新或日志记录。

事件处理
 AppWidget 重载了 eventFilter 方法，通过拦截鼠标点击或悬停事件来触发 do_daptch 私有方法，从而启动或检查所绑定的 ApplicationWrapper。此机制使得用户无需手动调用启动接口，仅需点击卡片即可完成应用调度操作。

私有成员
 ui 成员指向自动生成的 UI 类，用于管理图标、标签等子控件；dummy_state 表示当前卡片是否为占位状态；app_internal 存储绑定的 ApplicationWrapper；do_daptch 方法为私有调度入口，用于根据当前状态决定调用 ApplicationWrapper 的 depatch_app 或报告错误状态。

## 使用示例

 在界面构建阶段，可先创建一个 AppWidget 并传入应用图标与名称，随后通过 bindApp 将 ApplicationWrapper 实例与之关联，并将该卡片添加到布局或堆叠窗口中。用户在界面中点击该卡片时，eventFilter 会捕获点击事件并调用 do_daptch，从而启动或检查后台应用，执行完毕后自动发出 postAppStatus 信号，外部可连接此信号来更新卡片视觉样式或日志提示。
