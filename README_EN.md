# CCIMXDESKTOP 🖥️

![CCIMXDesktopLogo](./CCIMXDesktopLogo.png)

![Qt](https://img.shields.io/badge/Qt-6.8.3-green)![OpenCV](https://img.shields.io/badge/OpenCV-4.12.0-blue)![MuPDF](https://img.shields.io/badge/MuPDF-supported-orange)![Qt](https://img.shields.io/badge/C++-23+-green)![Version](https://img.shields.io/badge/Version-Released_1.0.0-red)

🔌 Hello! This is a simple desktop and utility collection that can be used in a variety of embedded devices! This project currently requires C++23 to compile (it's worth noting that you can compile with C++17, but any projects that require C++23 will need minor modifications)

## 🌐 Before you get started, choose your language! 🌐

[🇬🇧 English Version](./README_EN.md) | [🇨🇳 Chinese](./README.md)

## 🌟 Project Overview 🌟

**CCIMXDESKTOP** provides a lightweight, extensible desktop environment optimized for embedded systems based on the NXP i.MX6ULL platform. It includes a range of built-in tools, device integration layers, and built-in helper applications, all presented in a unified user interface.

![i.MX6ULL](https://img.shields.io/badge/NXP-i.MX6ULL-yellow)
![Embedded](https://img.shields.io/badge/Platform-Embedded%20Linux-lightgrey)

Now, CCIMXDesktop supports one-click builds including:

- 🏠 Supports dynamic loading of built-in or external applications (single launch or persistence to the desktop) and the most basic desktop configurable interface (setting application supports brightness adjustment (non-arm platform is a pseudo interface, no actual effect is provided), static wallpaper switching (PPT translation style, gradient style and fixed display style))
- 🏠 Supports recording click frequency and dynamically adjusting the DockWidget bottom sidebar
- ℹ About App (a brief introduction to the basic situation of the desktop of this project)
- ✏️ CCNoter (super lightweight notepad)
- 🎨SimpleDrawer (super lightweight drawing, similar to Windows "Paint")
- 🔧 Builtin Apps (Indoor temperature requires that the ICM20608 driver has been mounted and is available, other sensors need to modify the interface content by themselves (just rewrite how to read) and network degree detection (requires Qt Networks Core to be supported))
- ☀️ WeatherAPP (requires your device to be able to connect to the Internet to be available)
- 📄 pdfReader (requires you to have the dependent static library of mupdf on your platform)
- 📁 FileRamber (file browser, with basic file navigation, Tiny version of Windows Explorer.exe)
- 📷 GeneralLocalCamera (this is a basic camera based on Opencv VideoCapture, which can realize the photo function)
- 📊 SystemState (view the CPU status, memory capacity status and process list of the running machine)
- 🎵 MediaPlayer (requires your QMediaPlayer to support ALSA or other audio playback, and OpenCV support is required for video playback)
- 💡 LEDController App (Light switch APP, requires Platform LED driver to be enabled)
- 🌡️ Environment App (AP3216C driver needs to be mounted)
- 🏃 SportHealth App (ICM20608 driver needs to be mounted)
- 🖼️ ImageWalker (the most basic image information browser, equivalent to the Windows image browser for beggars)
- ✏️ MarkDown reader (the most basic Markdown editing + preview function, supports draft/load and save Markdown and basic shortcut functions)
- 🛜 CCNetHelper (supports network card information viewing, IP port scanning and basic test IP connection capabilities)
- 🦖Dinasour Game! (Yes, that Google Dinasour Game, implemented with Qt6 Widgets :) )
- 🧮Caculator Pocket calculator (standard calculator)
- 🤖ImageProcessor (image processor processes images locally and does simple reasoning (face recognition))
- ⚙ Settings (provides desktop wallpaper, brightness settings (not yet implemented on ARM platform) and AppWidget style settings)
- 🚀Dynamic Application Launcher (supports running third-party and can persist into the desktop!)

------

## Some running screenshots

1) Main interface: HOME interface (screenshot version: PreRelease1.0.0)

![image-20250613225001667](./README/image-20250613225001667.png)

2) BuiltinAPP display interface

![image-20250613225142493](./README/image-20250613225142493.png)

3) ExternAPP third-party optional build configuration

![image-20250613225155327](./README/image-20250613225155327.png)

4) APP settings desktop interface

![image-20250613224911141](./README/image-20250613224911141.png)

## 🛠️ Technologies used to build the foundation

![Qt](https://img.shields.io/badge/Qt-Core%20%26%20Network-41cd52)
![TSLIB](https://img.shields.io/badge/TSLIB-required-green)![TSLIB](https://img.shields.io/badge/QtCore-required-red)![TSLIB](https://img.shields.io/badge/QtWidget_QtGui-required-blue)![TSLIB](https://img.shields.io/badge/QtNetwork-required-purple)![TSLIB](https://img.shields.io/badge/QtMultiMedia_ALSA_Least-required-purple)

Building this project requires that you have completed the porting of Qt6 (the basic necessary porting includes TSLib for interaction, QtCore QtWidget QtGui three-piece set, QtNetwork and at least QtMultiMedia component support for ALSA audio playback). Please check whether your build is sufficient to support the building of this desktop and third-party applications!

Tip: The full build takes about 10 minutes (16 threads), you can adjust it dynamically according to your needs, please refer to the build document for details

> [🛠️ How to build this project? (Supports X86 gcc, ARM-linux-gnueabihf-gcc and Windows GCC)](Documentations/HOW_To_Build_The_Desktop.md)

## 🛠️ Full build of technologies

![OpenCV](https://img.shields.io/badge/OpenCV-Camera%20Support-blue)

![MuPDF](https://img.shields.io/badge/MuPDF-PDF%20Rendering-orange)

- OpenCV for camera support and image transform processing (if you don't use OpenCV image processing and any support for video streaming, you can leave out the library, but all related apps will be set to not build!)

- MuPDF (for PDF rendering) (These are used for PDF readers based on mupdf. If you don't want to build, you can ignore MuPDF dependencies and all related apps will be set to not build!)

------

## 🧩 Developer Reference

- [📖 Chinese Module Explanation](./Components-explain-CN.md)

---

## 📚 Project Documentation

![GCC](https://img.shields.io/badge/GCC-cross--compile-yellowgreen)
![ARM](https://img.shields.io/badge/ARM-linux--gnueabihf-red)

If you are interested in the project production process and development documents, please refer to the Documentations folder. For the build process and customization, please refer to the build manual:

> [🛠️ How to build this project? (Supports X86 gcc, ARM-linux-gnueabihf-gcc and Windows GCC)](Documentations/HOW_To_Build_The_Desktop.md)

The document has been automatically deployed through GitHub Actions, visit: [CCIMXDesktop: Main Page](https://charliechen114514.github.io/CCIMXDesktop/)

## 💡 WIP (some WIP Third Party Apps under development)

- 💬 Chat room (planned to be similar to QQ)
- Support the top status bar to display basic information
- Configurable HOME interface

## 💡 Future plans

🚀 Plan to write and provide more external basic programs:

- ⏰ Alarm clock APP
- 🔌 Serial port assistant
- ✅ Task list

------

## 📝 License

![License](https://img.shields.io/badge/License-MIT-brightgreen)

This project is based on the MIT license, and you are welcome to port, modify and use it at will!
