# 模块名称 WallPaperAnimationHandler

功能概述
 WallPaperAnimationHandler 结构体继承自 QObject，负责桌面主窗口壁纸的平滑切换动画。它通过接收一个包含当前与缓冲壁纸的 WallPaperGroup，以及一个可定制的 ImagePoolEngine，引导新的壁纸切换过程，实现图片的过渡动画而无需调用者关注底层细节。

内部结构
 WallPaperAnimationHandler 提供了一个嵌套结构 ImagePoolEngine，用于描述可用壁纸池和从中选取下一张壁纸的算法。该结构体包含指向 QStringList 的 image_list 成员，表示壁纸路径的集合，以及一个 std::function 形式的 selector 回调，用于根据传入的壁纸列表返回下一张壁纸在列表中的索引。通过外部注入不同的 selector，调用者可自定义顺序、随机或加权选择等多种策略。

静态方法说明
 process_switch 是 WallPaperAnimationHandler 唯一的静态成员函数。调用该函数时，首先读取传入的 group 中的 wallpaperLabel 作为当前显示壁纸，bufferpaperLabel 作为过渡层，invoke_switch_timer 用于时机触发。函数内会使用 engine.selector 从 engine.image_list 中选出下一张壁纸，更新 bufferpaperLabel 的内容，并启动 DesktopMainWindow 中定义的背景切换定时器或动画效果。整个切换过程包含先将新壁纸置于缓冲层并调整其可见性，然后通过透明度和位置动画将其替换到主层，最后更新 group.shoule_be_lower 指向最新壁纸。

使用方式
 在程序初始化时，创建一个 WallPaperAnimationHandler 对象并将其作为 DesktopMainWindow 的子对象，以确保其生命周期与主窗口一致。准备一个 ImagePoolEngine 实例，将 DesktopMainWindow 壁纸列表传入 image_list，并实现 selector 回调以决定轮换策略。随后在适当时机（如定时器触发或手动调用）使用 WallPaperAnimationHandler::process_switch，将主窗口的 WallPaperGroup 和 ImagePoolEngine 传入，即可完成一次壁纸切换动画。调用者可将该操作绑定到 invoke_switch_bgpage 信号或自定义事件中，实现自动或用户触发的动态壁纸更新。
