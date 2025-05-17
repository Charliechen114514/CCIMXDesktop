# 🧩 模块描述 

![Modules](https://img.shields.io/badge/Modules-6%20Core%20Components-blueviolet)

如果您希望修改模块以便更好地移植到您的嵌入式设备，以下是供开发人员参考的模块描述。

## 🔧 `app_wrapper` 

![Launcher](https://img.shields.io/badge/Component-System%20Launcher-important)

应用程序启动器和系统引导程序。它初始化 Qt 环境、设置全局样式并管理启动和关闭顺序。

------

## 🧬 `builtin`

![Builtin](https://img.shields.io/badge/Category-Core%20Utilities-yellowgreen)

包含嵌入在桌面环境中的核心系统工具和默认实用程序。

- `core/icm20608`
  ![Sensor](https://img.shields.io/badge/Driver-IMU%20Sensor-blue)
  **ICM-20608 IMU 传感器** 的驱动程序和逻辑，用于处理陀螺仪和加速度计的实时数据采集，并通过 I2C 接口连接。（补充：如果您使用其他芯片，也应该修改并重写内部函数）

- `gadgets`
  ![UI](https://img.shields.io/badge/Type-UI%20Widgets-9cf)
  界面友好的小工具，例如时钟、CPU/网络仪表或用于用户交互的快速启动图块。

- `page` 
  ![Navigation](https://img.shields.io/badge/Feature-Page%20Routing-ff69b4)
  用于内部 UI 路由的逻辑页面管理（例如，在主页、应用页面等之间切换）。

- `sources/localweather`
  ![Weather](https://img.shields.io/badge/Data-Weather%20API-green)
  用于获取或模拟本地天气数据的天气信息提供模块。

- `sources/netcard`
  ![Network](https://img.shields.io/badge/Service-Network%20Status-lightgrey)
  用于处理网卡信息、状态显示，并可能提供 IP/网络诊断。

- `ui`
  ![Theme](https://img.shields.io/badge/Style-UI%20Components-important)
  内置模块特有的 UI 组件，这些文件支持桌面本身的 UI 样式。

------

## ⚙️ `core`

![System](https://img.shields.io/badge/Layer-System%20Services-critical)

系统级服务和共享基类，例如全局上下文管理、信号总线或单例基础架构。可能包含跨模块使用的系统抽象。

------

## 🚀 `extern_app`

![Extensible](https://img.shields.io/badge/Architecture-Pluggable%20Apps-success)

第三方或用户可扩展的应用，集成到桌面系统中，但已模块化，方便添加/删除。您需要自己去下方对应的文档去翻阅其中的细节，需要注意的是，你只需要几乎0成本的修改就能将这些extern_app中的子项独立出来进行运行，作为您自己的一个项目进行改善和细化

------

## 🧩 `sources`

![Resources](https://img.shields.io/badge/Assets-UI%20Resources-blue)

桌面本身使用到的Ui资源，如果您需要替换成自己的资源，直接同名替换即可。

------

## 🎨 `ui`

![Theme](https://img.shields.io/badge/Design-Theme%20System-ff69b4)

顶级 UI 模板、主题或布局定义。可作为整个桌面样式或皮肤的基础。
