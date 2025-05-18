# 模块名称 DownDockWidget

## 功能概述

 DownDockWidget 是一个轻量级的停靠容器，继承自 QWidget，用于在桌面主界面底部以水平布局方式承载多个 AppWidget 实例，提供快速访问和切换功能。

## 类说明

 DownDockWidget 在构造时初始化其 UI 布局，并维护一个内部 QWidget（internal_widget）作为实际的布局承载区。通过 set_dock_apps 方法，可以批量设置需要停靠的 AppWidget 对象列表；该方法会替换内部现有的停靠项，并在布局中按顺序添加新的卡片组件。

## 构造与析构

 explicit DownDockWidget(QWidget *parent = nullptr)
 构造函数接收一个可选的父 QWidget 指针，用于将停靠栏嵌入至上层布局中。函数内部会调用 UI 类生成器创建界面元素，并准备好水平布局容器。
 ~DownDockWidget()
 析构函数负责释放与 UI 相关的资源，确保停止显示时不会产生内存泄漏。

## 公有方法

 void set_dock_apps(const QList<AppWidget*>& apps)
 该方法接收一个 AppWidget 指针列表，表示本次需要展示在停靠区的应用卡片。调用后，内部成员 dock_apps 会被更新为此列表，并调用私有方法 replace_docks 来重建布局：清除旧的停靠项、将新的 AppWidget 逐个插入到 internal_widget 的布局中，实现界面刷新。

## 私有成员与方法

 Ui::DownDockWidget* ui
 指向通过 Qt Designer 生成的 UI 类，用于访问布局和控件。
 QList<AppWidget\*> dock_apps
 保存当前停靠栏中的所有 AppWidget 对象引用，用于在布局替换时重建界面。
 QWidget* internal_widget
 实际用于承载 AppWidget 对象的容器，通常配置了水平布局，用以排列多个卡片。
 void replace_docks()
 私有辅助方法，在 dock_apps 更新后被调用，用于清空 internal_widget 中的旧子控件，并将 dock_apps 中的每个 AppWidget 添加到布局，同时可在添加时设置间距、对齐或尺寸策略。

## 使用示例

 在主窗口初始化完成后，可创建 DownDockWidget 并添加到主界面的底部停靠区域。随后将 AppWidget 列表传入 set_dock_apps，例如：

```cpp
QList<AppWidget*> favoriteApps = {appWidget1, appWidget2, appWidget3};
downDockWidget->set_dock_apps(favoriteApps);
```

这样，指定的应用卡片便会按顺序出现在底部停靠栏，用户可以点击它们快速切换或启动对应的应用。
