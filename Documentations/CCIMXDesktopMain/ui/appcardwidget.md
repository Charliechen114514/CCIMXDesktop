# 模块名称 AppCardWidget

功能概述
 AppCardWidget 是一个轻量级的应用卡片基类，继承自 QWidget，用于在桌面应用中以卡片形式展示各类子模块。它集成了与 DesktopToast 的交互能力，能在卡片生命周期内向用户弹出提示信息，同时为具体应用卡片提供标准化的预启动流程接口和渲染后处理钩子。

类说明
 AppCardWidget 禁用了复制构造与赋值操作，以避免同一卡片实例被多重管理。其构造函数要求传入一个 DesktopToast 对象，作为全局或局部提示机制的承载者；可选的父 QWidget 参数则用于将卡片嵌入到更大的界面布局中。

构造与析构
 调用显式构造函数时会完成与 DesktopToast 的绑定，并初始化内部的 UI 指针；析构函数则负责释放与 UI 相关的资源，确保卡片销毁时不会遗留内存或事件过滤器。

公有接口
 setCurrentIcon 方法允许子类或外部逻辑为卡片设置或更新图标，接收一个 QPixmap 对象。
 invoke_preLaunch_work 是一个纯虚函数，由具体的应用卡片实现预启动行为，例如检查环境、拉取数据或发起后台请求；框架在系统启动或页面切换时会调用此接口。

受保护接口与事件过滤
 postAppCardWidget 同样是纯虚函数，用于在卡片完成初次渲染或布局后执行后处理逻辑，例如启动动画、加载动态数据或注册定时器。binding_toast 和 ui 成员分别保存了用于弹出通知的 DesktopToast 指针和与之对应的 UI 对象。
 eventFilter 方法重载自 QObject，可拦截并处理卡片内部或其子控件的事件，子类可在此实现鼠标悬停、点击反馈或拖拽行为。

## 使用示例

 在创建具体应用卡片类时，应继承自 AppCardWidget，重载 invoke_preLaunch_work 和 postAppCardWidget 两个纯虚方法，用以定义卡片在预启动阶段和渲染完成后的自定义逻辑。在界面初始化过程中，将 DesktopToast 对象传入卡片构造函数，并将卡片添加到布局。系统或页面管理器将自动调用 invoke_preLaunch_work 执行启动前检查，随后在显示卡片后调用 postAppCardWidget 触发后续渲染逻辑。通过 setCurrentIcon 或 eventFilter，外部代码可动态更新卡片图标或拦截交互事件，实现丰富的用户体验。