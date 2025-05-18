# 模块名称：PageFactory

## 功能概述

 PageFactory 类提供了构建桌面主窗口页面的静态接口，旨在快速生成首页与伪应用页面，并在内部完成应用卡片的布局与初始化。该工厂模式的设计使得页面构建逻辑集中管理，调用者无需关心卡片的创建与插入细节，只需使用简单的静态方法即可完成页面搭建。

## 类说明

 PageFactory 为纯静态工具类，其所有方法均为静态成员，无需实例化即可调用。该类面向桌面应用中的页面管理场景，能够根据提供的主窗口指针与资源路径，自动创建 QWidget 或 AppWidget 对象列表并返回给调用者。

## 静态方法说明

 build_home_page 方法接收一个 DesktopMainWindow 指针作为参数，返回一个 QWidget 指针，表示构建完成的首页容器。调用该方法后，首页内会预置若干应用卡片布局，并通过内部调用 place_appcards_in_empty_widgets 完成卡片与布局的绑定，最后将填充好的 QWidget 交付给主窗口进行显示。

build_pesudo_page 方法用于生成伪应用页面，其参数包括图标资源路径 pixpath、需要创建的页面数量 how_many 以及目标主窗口指针 mainWindow。方法会在内部针对指定数量调用 AppWidget 构造逻辑，并将创建好的 AppWidget 对象列表返回给调用者，以便进一步插入到 QStackedWidget 或 Dock 区域。

## 私有方法说明

 place_appcards_in_empty_widgets 为类内部使用的方法，接收一个 DesktopMainWindow 指针和一个空白 QWidget 容器。该方法会根据主窗口的配置遍历应用卡片列表，创建并初始化对应数量的 AppCardWidget，然后将其插入到传入的 QWidget 中完成布局设置。由于该方法仅供类内部在首页构建过程中调用，因此被声明为私有。

## 代码流程

 在程序初始化流程中，可调用 PageFactory::build_home_page 并将返回的 QWidget 作为首页加载到主窗口的堆叠窗口或中央窗口区域。对于需要展示占位或示例页面的场景，可使用 PageFactory::build_pesudo_page 提供图标路径和数量参数，并根据返回的 AppWidget 列表调用 PageSetuper::create_specified_page 或 add_to_dock 进行进一步处理。这样即可利用 PageFactory 集中化构建逻辑，快速完成页面原型搭建与界面预览。