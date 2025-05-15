# CCIMXDESKTOP

​	Hello!!! This is a Simple Desktop And Utils Which can be used in Multiple Embedded Devices. for me, it starts the suite tailored for the i.MX platform, combining built-in system gadgets and extendable external apps. This project is designed to try it best with Qt and supports integration with various hardware sensors and multimedia interfaces.

## 🌐 Language For Starting Tour 🌐

[English Version](./README_EN.md)

[中文](./README.md)

## 🌟 Project Overview 🌟

**CCIMXDESKTOP** provides a lightweight, extensible desktop environment specifically optimized for embedded systems based on the NXP i.MX6ULL platform. It includes a series of built-in tools, device integration layers, and third-party apps, all presented in a cohesive user interface.

Currently, CCIMXDesktop supports one-click building including:

- Basic desktop environment and application abstraction
- Builtin Apps (Indoor temperature requires that the ICM20608 driver has been mounted and is available, and other sensors need to modify the interface content by themselves (just rewrite how to read) and network degree detection (requires Qt Networks Core to be supported))
- WeatherAPP (requires your device to be connected to the Internet to be available)
- pdfReader (requires you to have the dependent static library of mupdf on your platform)
- FileRamber (file browser, with basic file navigation, Tiny version of Windows Explorer.exe)
- GeneralLocalCamera (This is a basic camera based on Opencv VideoCapture, which can realize the photo taking function)
- SystemState (view the CPU status, memory capacity status and process list of the running machine)
- MediaPlayer (your QMediaPlayer needs to support ALSA or other audio playback, and video playback requires OpenCV support)
- Light switch APP(Light switch APP requires Platform LED driver to be enabled)
- Environment APP (AP3216C driver needs to be mounted)

------

## 🛠️ Technologies Used for Base Build

For beginners mappings the base desktop, it is simple that Qt6 Core Widgets And Core Networks should be supported in the  Embedded devices. And TSLIB and Linux framebuffer backend for display should be ready also.

## 🛠️ Technologies Used for FULL Build

- OpenCV For the Camera Support
- MuPDF (for PDF rendering)     (These is used for the mupdf based pdfreader)

------

## 🧩 Developer Reference

- [Module Explanations](Components-explain-EN.md)

---

## 📚Project Documentation

If you are interested in the project production process and development documents, please refer to the Documentations folder

## 💡 Future Plans

- Plan to write and provide more external basic programs:

  - Chat room
  - Image browser
  - Image processor
  - Simple text editor
  - Audio player
  - Serial port assistant
  - Image processor local processing of images and simple reasoning (face recognition)
  - Posture detection APP

------

## 📝 License

This project is based on MIT License, feel free to transplant, modified and use!
