# CCIMXDESKTOP 🖥️

![CCIMXDesktopLogo](./CCIMXDesktopLogo.png)

![Qt](https://img.shields.io/badge/Qt-6.8.3-green)![OpenCV](https://img.shields.io/badge/OpenCV-4.12.0-blue)![MuPDF](https://img.shields.io/badge/MuPDF-supported-orange)![Qt](https://img.shields.io/badge/C++-17+-green)![Version](https://img.shields.io/badge/Version-0.9.2-red)

🔌 Hello! This is a simple desktop and utility that can be used in a variety of embedded devices. For me, it kicks off a suite tailored for the i.MX platform, combining built-in system gadgets and extensible external applications. Designed using Qt, the project is working on supporting integration with a wide range of hardware sensors and multimedia interfaces wherever possible.

## 🌐 Before you get started, choose your language! 🌐

[🇬🇧 English Version](./README_EN.md) | [🇨🇳 Chinese](./README.md)

## 🌟 Project Overview 🌟

**CCIMXDESKTOP** provides a lightweight, extensible desktop environment optimized for embedded systems based on the NXP i.MX6ULL platform. It includes a range of built-in tools, device integration layers, and third-party applications, all presented in a unified user interface.

![i.MX6ULL](https://img.shields.io/badge/NXP-i.MX6ULL-yellow)
![Embedded](https://img.shields.io/badge/Platform-Embedded%20Linux-lightgrey)

Now, CCIMXDesktop supports one-click builds including:

- 🏠 Basic desktop environment and application abstraction
- 🏠 DockWidget that records click frequency and dynamically adjusts
- ℹ About App (a brief introduction to the basic situation of the desktop of this project)
- ✏️ CCNoter (super lightweight notepad)
- 🎨SimpleDrawer (super lightweight drawing, similar to Windows "Paint")
- 🔧 Builtin Apps (Indoor temperature requires that the ICM20608 driver has been mounted and is available. Other sensors need to modify the interface content by themselves (just rewrite how to read) and network degree detection (requires Qt Networks Core to be supported))
- ☀️ WeatherAPP (requires your device to be connected to the Internet to be available)
- 📄 pdfReader (requires you to have the dependent static library of mupdf on your platform)
- 📁 FileRamber (file browser, with basic file navigation, Tiny version of Windows Explorer.exe)
- 📷 GeneralLocalCamera (this is a basic camera based on Opencv VideoCapture, which can realize the photo function)
- 📊 SystemState (view the CPU status, memory capacity status and process list of the running machine)
- 🎵 MediaPlayer (requires your QMediaPlayer to support ALSA or other audio playback, video playback requires OpenCV support)
- 💡 LEDController App (switch light APP, requires Platform LED driver to be enabled)
- 🌡️ Environment App (AP3216C driver needs to be mounted)
- 🏃 SportHealth App (ICM20608 driver needs to be mounted)

-------

## Some running screenshots

![image-20250518085608736](./README/image-20250518085608736.png)

![image-20250518085912716](./README/image-20250518085912716.png)

## 🛠️ Technologies used for basic builds

![Qt](https://img.shields.io/badge/Qt-Core%20%26%20Network-41cd52)
![TSLIB](https://img.shields.io/badge/TSLIB-required-green)

For beginners mapping a basic desktop, the embedded device should support Qt6 core widgets and core networking. In addition, TSLIB and Linux framebuffer backends for display should also be ready.

## 🛠️ Full build of technologies

![OpenCV](https://img.shields.io/badge/OpenCV-Camera%20Support-blue)
![MuPDF](https://img.shields.io/badge/MuPDF-PDF%20Rendering-orange)

- OpenCV for camera support
- MuPDF (for PDF rendering) (these are used in mupdf-based PDF readers)

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
>
> The document has been automatically deployed on Gihub Actions: Project document address [CCIMXDesktop: Main Page](https://charliechen114514.github.io/CCIMXDesktop/)

## 💡 Future plans

- 🚀 Plan to write and provide more external basic programs:
- 💬 Chat room (planned to be similar to QQ)
- ⏰ Alarm clock APP
- 🖼️ Image browser
- 🎨 Image processor
- ✏️ MarkDown reader
- 🛜 Network viewing assistant
- 🧮 Pocket calculator
- 🔌 Serial port assistant
- ✅ Task list
- 🤖 Image processor processes images locally and performs simple reasoning (face recognition)
- ⚙ Basic settings (similar to IOS, but many are more ornamental)

------

## 📝 License

![License](https://img.shields.io/badge/License-MIT-brightgreen)

This project is based on the MIT license, and you are welcome to port, modify and use it at will!
