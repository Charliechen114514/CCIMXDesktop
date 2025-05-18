# 📦 如何构建本项目？

![MSVC](https://img.shields.io/badge/MSVC-Support-blue)
![x86-GCC](https://img.shields.io/badge/x86--GCC-Support-brightgreen)
![Arm32-linux-gnueabihf-GCC](https://img.shields.io/badge/Arm32_linux_gnueabihf_GCC-support-red)

🔧 本项目是使用了C++编程语言编写的，面向I.MX6ULL 正点原子Alpha开发板的桌面项目，需要您的下位机环境已经至少部署了如下的基本环境：

- ⚙️ 基本的C/C++运行时环境（即具备C/C++库）
- 🖥️ 4.3寸或7寸LCD且具备触控芯片进行交互功能，且触控驱动已经加载成功可以正常工作。
- 🌐 对于网络部分的项目（包含天气预报APP），需要网卡驱动正常工作且可以介入互联网
- 🎨 QtCore / QtWidget / QtNetWork / QtGui / QtCharts / QtMultiMedia 的基本支持
- 📚 对于基于MuPDF的PDF浏览器，编译需要提供MuPDF的交叉编译静态库和头文件
- 📷 对于所有基于OpenCV的项目（包括但是不限于MediaPlayer，GeneralLocalCamera）需要提供OpenCV4.12.0的编译支持。
- 🔗 下位机如果使用了第三方的库，比如说ALSA-Lib是第三方的，如果是动态库，请确保下位机环境存在的同时，上位机交叉编译的时候也需要保证可以检索到交叉编译动态库。

## 🛠️ 本项目的编译事项

- 🔨 完成上述工作后，您可以使用——QtCreator的 CMake 配置界面，CMake-GUI对项目进行编译，目前笔者仍然在尝试优化配置逻辑（包含自动依赖检查），因此到目前为止，您仍然需要一部分的手改依赖配置来启动这个项目的编译
- ⚙️ 您可以调整INCLUDE_*APP来调整哪些APP是您想要的，哪些不需要，凡是不需要的APP只需要设置该变量为OFF即可。他就不会参与编译。
- 📁 需要设置`CCIMX_ALL_RELEASE_DIR_BASE`变量作为下载的一个基础。您需要创建CCIMX_ALL_RELEASE_DIR_BASE作为不同发行版的根基下载路径（Install Path）

# 📦 How to build this project?

![MSVC](https://img.shields.io/badge/MSVC-Support-blue)
![x86-GCC](https://img.shields.io/badge/x86--GCC-Support-brightgreen)
![Arm32-linux-gnueabihf-GCC](https://img.shields.io/badge/Arm32_linux_gnueabihf_GCC-support-red)

🔧 This project is written in C++ programming language, and is a desktop project for the i.MX6ULL Zhengdian Atom Alpha development board. It requires that your lower computer environment has at least deployed the following basic environment:

- ⚙️ Basic C/C++ runtime environment (that is, with C/C++ library)
- 🖥️ 4.3-inch or 7-inch LCD with touch chip interactive function, and the touch driver has been successfully loaded and can work normally.
- 🌐 For network projects (including weather forecast APP), the network card driver needs to work properly and can access the Internet
- 🎨 Basic support for QtCore / QtWidget / QtNetWork / QtGui / QtCharts / QtMultiMedia
- 📚 For PDF browsers based on MuPDF, compilation requires the cross-compiled static library and header files of MuPDF
- 📷 For all OpenCV-based projects (including but not limited to MediaPlayer, GeneralLocalCamera), OpenCV4.12.0 compilation support is required.
- 🔗 If the lower computer uses a third-party library, such as ALSA-Lib, which is a third-party library, if it is a dynamic library, please ensure that the lower computer environment exists, and the upper computer also needs to ensure that the cross-compiled dynamic library can be retrieved when cross-compiling.

## 🛠️ Compilation matters of this project

- 🔨 After completing the above work, you can use the CMake configuration interface of QtCreator, CMake-GUI to compile the project. At present, the author is still trying to optimize the configuration logic (including automatic dependency checking), so so far, you still need to manually modify some dependency configurations to start the compilation of this project
- ⚙️ You can adjust INCLUDE_*APP to adjust which APPs you want and which you don’t need. For all unnecessary APPs, just set the variable to OFF. It will not participate in the compilation.
- 📁 You need to set the `CCIMX_ALL_RELEASE_DIR_BASE` variable as a basis for downloading. you need to create CCIMX_ALL_RELEASE_DIR_BASE as the root download path (Install Path) of different distributions