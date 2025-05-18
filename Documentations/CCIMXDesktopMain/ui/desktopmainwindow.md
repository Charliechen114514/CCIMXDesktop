# 模块名称 DesktopMainWindow

这里就是主界面了。DesktopMainWindow 类继承自 QMainWindow，用于构建整个桌面应用的主窗口框架。该类在初始化过程中加载界面布局、壁纸切换机制、应用卡片区域以及底部提示系统，并提供页面切换、应用调度初始化和响应鼠标、窗口大小变化等事件的入口。

在构造函数中会完成用户界面对象 ui 的创建和绑定，同时实例化 DesktopToast 作为全局消息弹出器，并调用 post_setupui 方法对背景图、应用区域和壁纸切换定时器进行配置。壁纸切换归纳为一个 WallPaperGroup 结构，其中 shoule_be_lower 用于承载主壁纸，wallpaperLabel 与 bufferpaperLabel 分别作为当前与过渡图像容器，invoke_switch_timer 则定时触发背景切换。壁纸列表保存在 image_lists 中，切换间隔由 switch_bg_time 静态常量定义。

DesktopMainWindow 提供 showToast 方法，通过传入消息字符串将文本弹窗展示给用户，desktop_toast 访问器可用于外部模块获取同一 DesktopToast 实例。页面切换通过 to_next_page 与 to_prev_page 方法实现，内部调用 slideToPage 实现带动画的左右滑动效果。窗口调整大小或鼠标按下、释放事件会分别触发 resizeEvent、mousePressEvent 与 mouseReleaseEvent 重载，为实现拖拽切换或自适应布局预留了记录按压和释放点的 records 结构。

应用调度部分支持远程注入应用包装器实例，通过 install_remote_appwrapper 方法将 ApplicationWrapper 对象加入 app_wrapper 列表。应用卡片初始化在 post_inits 方法中以异步信号 deptach_app_cards_init 发出后触发 invoke_appcards_init 和 handle_app_status 处理逻辑，后者根据 AppWidget 发出的 postAppStatus 信号调整界面或日志记录。所有 AppWidget 与 AppCardWidget 对象会保存在 app_widgets 与 app_cards 列表中。

私有方法 setup_bg_image、setup_apps 和 post_setupui 协同完成界面搭建，其中 setup_bg_image 负责加载并设置多张壁纸，setup_apps 负责遍历 app_wrapper 列表创建 AppWidget 并将其插入到堆叠窗口或布局中。slideToPage 则通过动画实现页面切换效果。壁纸组的 invoke_switch_bgpage 可在外部调用或通过定时器 invoke_switch_timer 自动触发，实现动态背景。

典型使用流程是在程序入口创建 DesktopMainWindow 实例，将其作为 QApplication 的主窗口显示后，调用 install_remote_appwrapper 注入所有需要管理的 ApplicationWrapper，然后调用 post_inits 启动应用卡片的预调度流程，用户即可看到动态壁纸切换、应用卡片和全局消息提示的完整桌面界面。
