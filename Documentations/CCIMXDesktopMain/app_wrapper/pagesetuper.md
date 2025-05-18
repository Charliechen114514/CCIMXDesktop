# 模块名称：PageSetuper

功能概述：PageSetuper 命名空间提供了一系列函数和数据结构，用于在桌面主窗口中快速创建和管理应用页面布局。它支持根据应用图标地址和名称动态生成单应用页面、批量创建实际应用页面、创建用户指定页面容器以及将应用界面添加到底部停靠区域。

## 数据结构说明

PageSetupSessionRequest 结构体封装了一次页面创建会话所需的请求信息，其中 pixmap_addr 表示应用图标资源路径，app_name 表示应用名称，app 指向对应的 ApplicationWrapper 对象，用于在创建页面时关联后台进程控制。

### 常量说明

 APP_ICON_SZ 表示应用图标在页面布局中使用的统一像素尺寸，值为 48。

### 接口函数说明

 create_one_app_only_page_append 接口用于在给定的堆叠窗口和主窗口中追加单个应用页面。传入参数 widget 指定承载页面的 QStackedWidget 容器，mainWindow 指定所属的 DesktopMainWindow，sessionRequest 列表中每个元素包含一次页面创建所需的信息。函数返回新创建的 AppWidget 对象列表，调用方可根据需要进行后续绑定和信号连接。

create_real_app 接口用于在主窗口中批量创建所有注册的实际应用页面。传入参数 mainWindow 表示目标 DesktopMainWindow，函数内部依据预定义的应用配置生成对应的 AppWidget 并插入到合适的容器中，最终返回所有创建的 AppWidget 对象列表。

create_specified_page 接口用于在指定的堆叠窗口中插入用户自定义的页面容器。widget 为目标的 QStackedWidget，paged_widget 为用户构造好的 QWidget 页面对象。该函数不返回值，调用后指定页面即已添加至堆叠窗口，可通过 setCurrentIndex 等方法切换显示。

add_to_dock 接口用于将一组应用页面添加到底部停靠区。downdock 参数指定目标的 DownDockWidget 停靠容器，mainWindow 参数指定所属的 DesktopMainWindow，widgets 参数为需添加的 AppWidget 对象列表。调用后对应的页面项将出现在底部停靠栏以供快速切换。

## 使用示例

 在程序初始化阶段，可先准备若干 PageSetupSessionRequest 对象，调用 create_one_app_only_page_append 将单页面生成并追加到堆叠窗口，同时捕获返回的 AppWidget 列表。随后可根据实际需求调用 add_to_dock 将这些页面映射到底部停靠区。对于需要批量加载的场景，则直接调用 create_real_app 获取所有已注册应用的页面。对于特殊界面，可先自行构造 QWidget，然后调用 create_specified_page 将其插入到指定的堆叠窗口中以实现扩展功能。