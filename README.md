# CCIMXDESKTOP 🖥️ 

![CCIMXDesktopLogo](./CCIMXDesktopLogo.png)

![Qt](https://img.shields.io/badge/Qt-6.8.3-green)![OpenCV](https://img.shields.io/badge/OpenCV-4.12.0-blue)![MuPDF](https://img.shields.io/badge/MuPDF-supported-orange)![Qt](https://img.shields.io/badge/C++-17-green)![Version](https://img.shields.io/badge/Version-Released_2.0.1-red)

🔌 您好！这是一个可在携带LCD屏幕上IMX6ULL的嵌入式设备中使用的简单桌面和实用程序集合！本项目目前已经可以使用完全的C++17进行编译！

## 🌐 开始之前，选择你的语言！ 🌐

[🇬🇧 English Version](./README_EN.md) | [🇨🇳 中文](./README.md)

## 🌟 项目概述 🌟

![i.MX6ULL](https://img.shields.io/badge/NXP-i.MX6ULL-yellow)
![Embedded](https://img.shields.io/badge/Platform-Embedded%20Linux-lightgrey)

**CCIMXDesktop**是一个极简，轻量和高性能，基于Qt6.8.3的桌面环境框架，专门对以 NXP i.MX6ULL 平台为例的嵌入式系统定制（即跑不起重量级桌面服务但是却可以跑的起Qt程序的嵌入式系统），这里提供一系列常见的Qt内置工具封装，设备管理继承和内置的辅助应用程序，所有这些都在一个统一的用户界面中呈现。让您轻松愉快的可视化的使用带有LCD的嵌入式设备！

项目支持在Windows, Linux上位机和搭载具备基本环境（完备的根文件系统 + Qt + C++运行时环境）的ARM-Linux上运行



## 一些运行截图

0）预览视频（见B站）

[IMX6ULL小项目：写的一个跑在IMX6ULL上的基于Qt框架的超级小桌面](https://www.bilibili.com/video/BV1cTgnzvEtL?vd_source=7756b1d353ef340c2ab91e80642a8922)

1）启动加载时画面（截图版本：Release 2.0.0）

![image-20250722092731425](./README/image-20250722092731425.png)

2）主界面：HOME界面（截图版本：Release1.15.0）

![f5059a311e8e70a7db9225de6fc79a98](./README/f5059a311e8e70a7db9225de6fc79a98.png)

2）BuiltinAPP展示界面

![image-20250706142357134](./README/image-20250706142357134.png)

3）ExternAPP第三方可选构建配置

![image-20250623214716793](./README/image-20250623214716793.png)

4）APP设置桌面界面

![image-20250623214833847](./README/image-20250623214833847.png)

## 🛠️ 基础构建所用技术

![Qt](https://img.shields.io/badge/Qt-Core%20%26%20Network-41cd52)
![TSLIB](https://img.shields.io/badge/TSLIB-required-green)![TSLIB](https://img.shields.io/badge/QtCore-required-red)![TSLIB](https://img.shields.io/badge/QtWidget_QtGui-required-blue)![TSLIB](https://img.shields.io/badge/QtNetwork-required-purple)![TSLIB](https://img.shields.io/badge/QtMultiMedia_ALSA_Least-required-purple)![TSLIB](https://img.shields.io/badge/QtCharts-required-blue)

构建这个项目要求您已经完成对Qt6的移植（基础的必要移植包括TSLib做交互，QtCore QtWidget QtGui三件套，QtNetwork和最小至少支持ALSA音频播放的QtMultiMedia组件的支持），请您核查自己的构建是否足够支持构建本桌面和第三方应用程序！

提示：全量构建需要大约近10分钟（16线程），您可以根据需求动态调整，详细请参考构建文档

> [🛠️ 如何构建本项目？（支持 X86 gcc、ARM-linux-gnueabihf-gcc 和 Windows GCC）](Documentations/HOW_To_Build_The_Desktop.md)

## 🛠️ 完整构建所用技术

![OpenCV](https://img.shields.io/badge/OpenCV-Camera%20Support-blue)
![MuPDF](https://img.shields.io/badge/MuPDF-PDF%20Rendering-orange)

- OpenCV 用于摄像头支持和图像变换处理（如果您不使用OpenCV图像处理和任何对视频流的支持，可以不提供库，但是所有的相关APP会全部置为不构建！）
- MuPDF（用于 PDF 渲染）（这些用于基于 mupdf 的 PDF 阅读器，如果您不希望构建，可以不予理会MuPDF依赖，所有的相关APP会全部置为不构建！）

------

## 这里有什么？

现在，CCIMXDesktop支持的一键构建包括：
（注：标准最小依赖为：TSLib做交互📝，QtCore🔧 QtWidget🖼️ QtGui🎨 QtNetwork🌐四件套的基础支持）

#### 桌面本体功能💻

- 📦 基础的应用托管器 + 动态APP启动⚡

- 🖼️ 壁纸动画，托管功能🌀

- 🛠️ 基础的内建本体辅助APP（不可卸载🔒）

- 📜 日志管理系统，为CCIMXDesktop增加日志系统方便调试🔍和观察👀

- 📂 初步稳定的桌面私有文件夹系统

-   ℹ  初步搭建起来服务系统（消息通知系统）

- 🔌初步搭建起来的Widget插件系统（目前仅限HOME卡片组可用插件化）

- 👨最基本的用户信息系统

- 🗃️ 丝滑滑动卡片系统 ✨

  目前已注册的内建卡片类型 📦:

  - 📅 日历卡片
  - 🗓️ 日期卡片
  - 💾 硬存信息系统
  - 💾 内存信息系统
  - 👨 默认的用户信息卡片显示

#### 项目包含

| 功能 / 应用名称                                  | 依赖条件或备注                                     | 是否为内建程序 | 说明                                                         | 界面展示                                                     |
| ------------------------------------------------ | -------------------------------------------------- | -------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 🏠 CCIMX_Desktop本体                              | 标准最小依赖                                       | 是             | 核心框架，本体                                               | ![f5059a311e8e70a7db9225de6fc79a98](./README/f5059a311e8e70a7db9225de6fc79a98.png) |
| ℹ About App                                      | 标准最小依赖                                       | 是             | 简单的介绍本项目桌面的基本情况                               | ![image-20250614231912157](./README/image-20250614231912157.png) |
| ✏️ CCNoter（记事本）                              | 标准最小依赖                                       | 是             | 超级无敌轻量的记事本                                         | ![image-20250614231754881](./README/image-20250614231754881.png) |
| 📅CCCalendar（日历APP）                           | 标准最小依赖                                       | 是             | 超级无敌轻量的日历APP                                        | ![image-20250706142207503](./README/image-20250706142207503.png) |
| 🎨 SimpleDrawer（画图）                           | 标准最小依赖                                       | 是             | 超级无敌轻量的画图，类似Windows的“画图”                      | ![image-20250614232836661](./README/image-20250614232836661.png) |
| ☀️ WeatherAPP（天气应用）                         | 需设备具备联网能力（网络连接）                     | 可选           | 获取城市所在的天气预报，目前使用的API是心智天气的            | ![image-20250614232722896](./README/image-20250614232722896.png) |
| 📄 pdfReader（PDF阅读器）                         | MuPDF依赖库                                        | 可选           | 最基础的PDF浏览器，支持章节跳转和查看功能                    | ![image-20250614232706288](./README/image-20250614232706288.png) |
| 📁 FileRamber（文件浏览器）                       | 标准最小依赖                                       | 是             | 文件管理基础（文件浏览器，具备基本的文件导览，Windows Explorer.exe的Tiny版本） | ![image-20250614232241212](./README/image-20250614232241212.png) |
| 📷 GeneralLocalCamera（摄像头）                   | 需要OpenCV支持                                     | 可选           | 可以进行拍照                                                 | ![image-20250614232213554](./README/image-20250614232213554.png) |
| 📊 SystemState（系统状态查看）                    | 标准最小依赖                                       | 是             | 查看运行机的CPU状态，内存容量状态和进程列表                  | ![image-20250614232050420](./README/image-20250614232050420.png) |
| 🎵 MediaPlayer（音视频播放器）                    | QMediaPlayer支持ALSA或其他音频，视频需要OpenCV支持 | 可选           | 网易云风格的音视频播放器，既可以播放音频也可以播放视频，音频时展示网易云风格的界面！ | ![image-20250614232017544](./README/image-20250614232017544.png) |
| 💡 LEDController App（灯控制）                    | Platform LED驱动                                   | 可选           | 需硬件支持（开关灯APP，需要 Platform LED 驱动使能）          | ![image-20250614231942332](./README/image-20250614231942332.png) |
| 🌡️ Environment App（环境监测）                    | AP3216C传感器驱动                                  | 可选           | 需硬件支持（AP3216C驱动需要被挂载且正常驱动）                | ![image-20250614232559945](./README/image-20250614232559945.png) |
| 🏃 SportHealth App（运动健康）                    | ICM20608驱动                                       | 可选           | 需硬件支持（ICM20608驱动需要被挂载且正常驱动）               | ![image-20250614232631305](./README/image-20250614232631305.png) |
| 🖼️ ImageWalker（图像浏览器）                      | 标准最小依赖                                       | 是             | 最基础的图像信息浏览查看器，相当于丐版的Windows图像浏览器    | ![image-20250614232520438](./README/image-20250614232520438.png) |
| ✏️ Markdown阅读器                                 | 标准最小依赖                                       | 是             | 轻量级Markdown编辑预览（最基础的Markdown编辑 + 预览功能，支持草稿 / 加载保存Markdown与基础快捷功能） | ![image-20250614232450028](./README/image-20250614232450028.png) |
| 🛜 CCNetHelper（网络工具）                        | 需要网卡具备网络连接能力（网卡驱动正常）           | 可选           | 支持网卡信息查看，IP端口扫描和基本测试IP打通能力             | ![image-20250614231832285](./README/image-20250614231832285.png) |
| 🦖 Dinasour Game（小游戏）                        | 标准最小依赖                                       | 可选           | 是的，就是那个Google Dinasour Game，用Qt6 Widgets实现的版本 :) | ![image-20250614231727977](./README/image-20250614231727977.png) |
| 🧮 Calculator（计算器）                           | 标准最小依赖                                       | 是             | 基础工具（标准计算器）                                       | ![image-20250614231703148](./README/image-20250614231703148.png) |
| 🤖 ImageProcessor（图像处理和推理）               | OpenCV，推理库（如有）                             | 可选           | 需OpenCV支持及推理支持                                       | ![image-20250614232427874](./README/image-20250614232427874.png) |
| ⚙ Settings（设置界面）                           | 标准最小依赖                                       | 是             | 桌面壁纸、亮度和桌面应用风格设置                             | ![image-20250614232323164](./README/image-20250614232323164.png) |
| 🚀 Dynamic Application Launcher（动态应用启动器） | 标准最小依赖                                       | 是             | 第三方应用运行和管理                                         | ![image-20250614232401883](./README/image-20250614232401883.png) |

------

## 🧩开发者参考

- [📖 汉语模块说明](./Components-explain-CN.md)

---

## 📚项目文档

![GCC](https://img.shields.io/badge/GCC-cross--compile-yellowgreen)
![ARM](https://img.shields.io/badge/ARM-linux--gnueabihf-red)

如果您对项目的制作流程和开发文档感兴趣，请参考Documentations文件夹。有关构建流程及定制，请查阅构建手册：

> [🛠️ 如何构建本项目？（支持 X86 gcc、ARM-linux-gnueabihf-gcc 和 Windows GCC）](Documentations/HOW_To_Build_The_Desktop.md)

文档已通过 GitHub Actions 自动部署，访问：[CCIMXDesktop: Main Page](https://charliechen114514.github.io/CCIMXDesktop/)

## 💡 WIP与计划

### 🚀 计划优化的桌面本体工作：

- 增加下拉式菜单的快速设置通道（亮度调节等）
- 增加针对按键的桌面刷新功能（待下一个版本更新按钮驱动，按按钮强迫返回HOME界面）
- 开发与桌面深度集成的**待办事项/提醒应用**。支持在状态栏显示即将到来的提醒，锁屏界面显示重要提醒。（插件系统已经支持）
- 增强长时间没有反应后自动降低亮度和点击时增强亮度设置
- 计划增加锁屏功能

### 🚀 计划编写和提供更多的外部基础程序：

- 💬 聊天室（计划类似于QQ）
- ⏰ 闹钟APP
- 🔌 串口助手
- ✅ 任务清单

### 🚀文档计划

- 进一步更加明确的完善项目的设计文档部分，展开针对桌面逐步配置化的相关文档辅助说明

------

## 📝 许可证

![License](https://img.shields.io/badge/License-MIT-brightgreen)

本项目基于 MIT 许可证，欢迎随意移植、修改和使用！
