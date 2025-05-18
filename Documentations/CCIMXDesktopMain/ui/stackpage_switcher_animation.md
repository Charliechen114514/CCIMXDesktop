# 模块名称 StackpageSwitcherAnimation

功能概述
 StackpageSwitcherAnimation 结构体继承自 QObject，用于在 QStackedWidget 页面切换时提供平滑动画效果。它将新旧页面以左右滑动的方式过渡，支持自定义目标页索引、动画时长和动画方向，无需调用者自行管理动画细节。

内部结构
 AnimationInfo 嵌套结构体包含：

- new_index：切换后的目标页面索引
- toLeft：布尔值，若为 true 则从右向左滑入新页面；为 false 则从左向右滑入
- animation_duration：动画持续时长（毫秒），默认 400

静态方法说明
 process_animations 接口接收两个参数：

- binding_widget：待执行过渡动画的 QStackedWidget 对象
- animation_info：指向 AnimationInfo 结构体的指针，包含本次动画所需的信息

调用该方法后，函数会根据 animation_info 中的参数在 binding_widget 上创建并启动相应的动画。一般流程为：

1. 在切换前将目标页面（new_index）插入并定位到合适的入口位置（左侧或右侧视图外）。
2. 创建位移动画，使当前页面与目标页面在同一时刻以对称方向滑动。
3. 动画完成后，将目标页面设置为当前页面，并清理临时动画对象，保证下次调用时环境干净。

使用示例
 在页面管理逻辑中，当需要跳转到第 2 页且希望从右侧滑入时，构造一个 AnimationInfo：

```cpp
StackpageSwitcherAnimation::AnimationInfo info;
info.new_index = 1;       // QStackedWidget 的第二个页面
info.toLeft = true;       // 从右向左滑入
info.animation_duration = 500; // 持续 500 毫秒
StackpageSwitcherAnimation::process_animations(myStackedWidget, &info);
```

这样即可在不暴露动画细节的情况下，让 myStackedWidget 平滑过渡到指定页面。
