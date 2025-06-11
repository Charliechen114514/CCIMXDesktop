# CCIMXDESKTOP 🖥️ 

![CCIMXDesktopLogo](./CCIMXDesktopLogo.png)

![Qt](https://img.shields.io/badge/Qt-6.8.3-green)![OpenCV](https://img.shields.io/badge/OpenCV-4.12.0-blue)![MuPDF](https://img.shields.io/badge/MuPDF-supported-orange)![Qt](https://img.shields.io/badge/C++-23+-green)![Version](https://img.shields.io/badge/Version-0.9.8-red)

🔌 您好！这是一个可在多种嵌入式设备中使用的简单桌面和实用程序集合！这个项目目前需要使用C++23进行编译（值得一提的是，您可以使用C++17编译，但是需要少许的修改任何要求使用C++23的项目）

## 🌐 开始之前，选择你的语言！ 🌐

[🇬🇧 English Version](./README_EN.md) | [🇨🇳 中文](./README.md)

## 🌟 项目概述 🌟

**CCIMXDESKTOP** 提供了一个轻量级、可扩展的桌面环境，专为基于 NXP i.MX6ULL 平台的嵌入式系统优化。它包含一系列内置工具、设备集成层和内置的辅助应用程序，所有这些都在一个统一的用户界面中呈现。

![i.MX6ULL](https://img.shields.io/badge/NXP-i.MX6ULL-yellow)
![Embedded](https://img.shields.io/badge/Platform-Embedded%20Linux-lightgrey)

现在，CCIMXDesktop支持的一键构建包括：

- 🏠 基础的桌面环境和应用抽象
- 🏠 记录点击频率从而动态调整的DockWidget
- ℹ About App（简单的介绍本项目桌面的基本情况）
- ✏️ CCNoter（超级无敌轻量的记事本）
- 🎨SimpleDrawer（超级无敌轻量的画图，类似Windows的“画图”）
- 🔧 Builtin Apps（室内气温需要已经挂载ICM20608驱动且可用，其他传感器需要自行修改接口内容（只需要重写如何读即可）与联网程度检测（需要Qt Networks Core 的基础被支持））
- ☀️ WeatherAPP（需要您的设备可以联网才可用）
- 📄 pdfReader（需要您具备您平台上的mupdf的依赖静态库）
- 📁 FileRamber（文件浏览器，具备基本的文件导览，Windows Explorer.exe的Tiny版本）
- 📷 GeneralLocalCamera（这是基于Opencv VideoCapture的基础相机，可以实现拍照功能）
- 📊 SystemState（查看运行机的CPU状态，内存容量状态和进程列表）
- 🎵 MediaPlayer（需要您的QMediaPlayer支持ALSA或者是其他的音频播放，视频播放需要OpenCV支持）
- 💡 LEDController App（开关灯APP，需要 Platform LED 驱动使能）
- 🌡️ Environment App（AP3216C驱动需要被挂载）
- 🏃 SportHealth App (ICM20608驱动需要被挂载)
- 🖼️ ImageWalker（最基础的图像信息浏览查看器，相当于丐版的Windows图像浏览器）
- ✏️ MarkDown阅读器（最基础的Markdown编辑 + 预览功能，支持草稿 / 加载保存Markdown与基础快捷功能）
- 🛜 CCNetHelper（支持网卡信息查看，IP端口扫描和基本测试IP打通能力）
- 🦖Dinasour Game!（是的，就是那个Google Dinasour Game，用Qt6 Widgets实现的版本 :) ）
- 🧮Caculator 口袋计算器（标准的计算器）

------

## 一些运行截图

![image-20250518085608736](./README/image-20250518085608736.png)

![image-20250518085912716](./README/image-20250518085912716.png)

## 🛠️ 基础构建所用技术

![Qt](https://img.shields.io/badge/Qt-Core%20%26%20Network-41cd52)
![TSLIB](https://img.shields.io/badge/TSLIB-required-green)![TSLIB](https://img.shields.io/badge/QtCore-required-red)![TSLIB](https://img.shields.io/badge/QtWidget_QtGui-required-blue)![TSLIB](https://img.shields.io/badge/QtNetwork-required-purple)![TSLIB](https://img.shields.io/badge/QtMultiMedia_ALSA_Least-required-purple)

构建这个项目要求您已经完成对Qt6的移植（基础的必要移植包括TSLib做交互，QtCore QtWidget QtGui三件套，QtNetwork和最小至少支持ALSA音频播放的QtMultiMedia组件的支持），请您核查自己的构建是否足够支持构建本桌面和第三方应用程序！

## 🛠️ 完整构建所用技术

![OpenCV](https://img.shields.io/badge/OpenCV-Camera%20Support-blue)
![MuPDF](https://img.shields.io/badge/MuPDF-PDF%20Rendering-orange)

- OpenCV 用于摄像头支持和图像变换处理（如果您不使用OpenCV图像处理和任何对视频流的支持，可以不提供库，但是所有的相关APP会全部置为不构建！）
- MuPDF（用于 PDF 渲染）（这些用于基于 mupdf 的 PDF 阅读器，如果您不希望构建，可以不予理会MuPDF依赖，所有的相关APP会全部置为不构建！）

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

## 💡 WIP（一些正在开发的WIP Third Party App）

- 🤖 图像处理器本地处理图像和做简单的推理（人脸识别）
- ⚙ 基础的设置（类似IOS，但是很多是观赏性较为强）

## 💡 未来计划

🚀 计划编写和提供更多的外部基础程序：
- 💬 聊天室（计划类似于QQ）
- ⏰ 闹钟APP
- 🔌 串口助手
- ✅ 任务清单

------

## 📝 许可证

![License](https://img.shields.io/badge/License-MIT-brightgreen)

本项目基于 MIT 许可证，欢迎随意移植、修改和使用！
