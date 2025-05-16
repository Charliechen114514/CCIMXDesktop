# CCIMXDESKTOP 

您好！这是一个可在多种嵌入式设备中使用的简单桌面和实用程序。对我来说，它启动了专为 i.MX 平台定制的套件，结合了内置系统小工具和可扩展的外部应用程序。该项目使用 Qt 设计，正在尽可能支持与各种硬件传感器和多媒体接口集成。

## 🌐 开始之前，选择你的语言！ 🌐

[English Version](./README_EN.md)

[中文](./README.md)

## 🌟 项目概述 🌟

**CCIMXDESKTOP** 提供了一个轻量级、可扩展的桌面环境，专为基于 NXP i.MX6ULL 平台的嵌入式系统优化。它包含一系列内置工具、设备集成层和第三方应用程序，所有这些都在一个统一的用户界面中呈现。

现在，CCIMXDesktop支持的一键构建包括：

- 基础的桌面环境和应用抽象
- Builtin Apps（室内气温需要已经挂载ICM20608驱动且可用，其他传感器需要自行修改接口内容（只需要重写如何读即可）与联网程度检测（需要Qt Networks Core 的基础被支持））
- WeatherAPP（需要您的设备可以联网才可用）
- pdfReader（需要您具备您平台上的mupdf的依赖静态库）
- FileRamber（文件浏览器，具备基本的文件导览，Windows Explorer.exe的Tiny版本）
- GeneralLocalCamera（这是基于Opencv VideoCapture的基础相机，可以实现拍照功能）
- SystemState（查看运行机的CPU状态，内存容量状态和进程列表）
- MediaPlayer（需要您的QMediaPlayer支持ALSA或者是其他的音频播放，视频播放需要OpenCV支持）
- 开关灯APP（开关灯APP，需要 Platform LED 驱动使能）
- 环境APP（AP3216C驱动需要被挂载）
- 姿态检测APP(ICM20608驱动需要被挂载)

------

## 🛠️ 基础构建所用技术

对于映射基础桌面的初学者来说，嵌入式设备应该支持 Qt6 核心控件和核心网络。此外，用于显示的 TSLIB 和 Linux 帧缓冲后端也应该已准备就绪。

## 🛠️ 完整构建所用技术

- OpenCV 用于摄像头支持
- MuPDF（用于 PDF 渲染）（这些用于基于 mupdf 的 PDF 阅读器）

------

## 🧩开发者参考

- [汉语模块说明](./Components-explain-CN.md)

---

## 📚项目文档

如果您对项目的制作流程和开发文档感兴趣，请参考Documentations文件夹

## 💡 未来计划

- 计划编写和提供更多的外部基础程序：
  - 聊天室
  - 图像浏览器
  - 图像处理器
  - 文本简单的编辑器
  - 串口助手
  - 图像处理器本地处理图像和做简单的推理（人脸识别）
------

## 📝 许可证

本项目基于 MIT 许可证，欢迎随意移植、修改和使用！
