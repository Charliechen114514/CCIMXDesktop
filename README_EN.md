# 🖥️ CCIMXDESKTOP

![Qt](https://img.shields.io/badge/Qt-6.8.3-green)![OpenCV](https://img.shields.io/badge/OpenCV-4.12.0-blue)![MuPDF](https://img.shields.io/badge/MuPDF-supported-orange)![Qt](https://img.shields.io/badge/C++-17+-green)

🔌 Hello! This is a simple desktop and utility that can be used in a variety of embedded devices. For me, it started a suite tailored for the i.MX platform, combining built-in system gadgets and extensible external applications. Designed with Qt, the project is supporting integration with various hardware sensors and multimedia interfaces as much as possible.

## 🌐 Before you start, choose your language! 🌐

[🇬🇧 English Version](./README_EN.md) | [🇨🇳 Chinese](./README.md)

## 🌟 Project Overview 🌟

**CCIMXDESKTOP** provides a lightweight, extensible desktop environment optimized for embedded systems based on the NXP i.MX6ULL platform. It includes a range of built-in tools, device integration layers, and third-party applications, all presented in a unified user interface.

![i.MX6ULL](https://img.shields.io/badge/NXP-i.MX6ULL-yellow)
![Embedded](https://img.shields.io/badge/Platform-Embedded%20Linux-lightgrey)

Now, CCIMXDesktop supports one-click building including:

- 🏠 Basic desktop environment and application abstraction
- 🔧 Builtin Apps (Indoor temperature requires that the ICM20608 driver has been mounted and is available, and other sensors need to modify the interface content by themselves (just rewrite how to read) and network degree detection (requires Qt Networks Core to be supported))
- ☀️ WeatherAPP (requires your device to be able to connect to the Internet to be available)
- 📄 pdfReader (requires you to have the dependent static library of mupdf on your platform)
- 📁 FileRamber (file browser, with basic file navigation, Windows Tiny version of Explorer.exe)
- 📷 GeneralLocalCamera (This is a basic camera based on Opencv VideoCapture, which can realize the photo function)
- 📊 SystemState (View the CPU status, memory capacity status and process list of the running machine)
- 🎵 MediaPlayer (Your QMediaPlayer needs to support ALSA or other audio playback, and video playback requires OpenCV support)
- 💡 LEDController App (Light switch APP, requires Platform LED driver to be enabled)
- 🌡️ Environment App (AP3216C driver needs to be mounted)
- 🏃 SportHealth App (ICM20608 driver needs to be mounted)

------

## Some running screenshots

![image-20250518085608736](./README/image-20250518085608736.png)

![image-20250518085912716](./README/image-20250518085912716.png)

## 🛠️ Basic build technologies

![Qt](https://img.shields.io/badge/Qt-Core%20%26%20Network-41cd52)
![TSLIB](https://img.shields.io/badge/TSLIB-required-green)

For beginners mapping a basic desktop, the embedded device should support Qt6 core controls and core networking. Additionally, TSLIB and Linux framebuffer backends for display should be ready.

## 🛠️ Full build of technologies

![OpenCV](https://img.shields.io/badge/OpenCV-Camera%20Support-blue)

![MuPDF](https://img.shields.io/badge/MuPDF-PDF%20Rendering-orange)

- OpenCV for camera support
- MuPDF (for PDF rendering) (these are used for mupdf-based PDF readers)

------

## 🧩 Developer Reference

- [📖 Chinese Module Explanation](./Components-explain-CN.md)

---

## 📚Project Documentation

![GCC](https://img.shields.io/badge/GCC-cross--compile-yellowgreen)
![ARM](https://img.shields.io/badge/ARM-linux--gnueabihf-red)

If you are interested in the project production process and development documents, please refer to the Documentations folder.

Currently, this project fully supports the use of Doxygen to automatically generate customized documents. You can directly refer to [`Documentations/doxygen_style`](Documentations/doxygen_styles) for reading, or if you plan to customize the construction of this document, you need to refer to the build manual for customized modifications

> [🛠️ How to build this project? (X86 gcc, ARM-linux-gnueabihf-gcc and Windows GCC are all supported!)](Documentations/HOW_To_Build_The_Desktop.md)

## 💡 Future Plans

- 🚀 Plan to write and provide more external basic programs:

- 💬 Chat room (planned to be similar to QQ)

- ⏰ Alarm clock APP

- 🖼️ Image browser

- 🎨 Image processor

- ✏️ Simple text editor

- 🔌 Serial port assistant

- 🤖 Image processor local image processing and simple reasoning (face recognition)

------

## 📝 License

![License](https://img.shields.io/badge/License-MIT-brightgreen)

This project is based on the MIT license, welcome to port, modify and use at will!
