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
- ⚙️ 您可以调整INCLUDE\_*\_APP来调整哪些APP是您想要的，哪些不需要，凡是不需要的APP只需要设置该变量为OFF即可。他就不会参与编译。
- ⚙️ 注意，现在如果不提供依赖的配置项的话，对应的App不会参与编译。
  - OpenCV若安装在非标准路径下，需要指定OpenCV_DIR作为下载的根路径（这个路径需要直接存在OpenCVConfig.cmake文件）
  - MuPDF则需要指定`MUPDF_INCLUDE_DIR`和`MUPDF_LIB_DIR`，这个变量名称很可能之后会发生变化，您可能需要查看CMake的构建日志进行具体的调整
- 📁 需要设置`CCIMX_ALL_RELEASE_DIR_BASE`变量作为下载的一个基础。您需要创建CCIMX_ALL_RELEASE_DIR_BASE作为不同发行版的根基下载路径（Install Path）

#  📦  How to build this project?

![MSVC]( https://img.shields.io/badge/MSVC-Support-blue )
![x86-GCC]( https://img.shields.io/badge/x86--GCC-Support-brightgreen )
![Arm32-linux-gnueabihf-GCC]( https://img.shields.io/badge/Arm32_linux_gnueabihf_GCC-support-red )
🔧  This project is written in the C++programming language and is a desktop project for the I.MX6ULL Point Atom Alpha development board. Your lower computer environment needs to have deployed at least the following basic environments:
-  ⚙️  Basic C/C++runtime environment (i.e. with C/C++libraries)
-  🖥️  4.3-inch or 7-inch LCD with touch chip for interactive function, and the touch driver has been successfully loaded and can work normally.
-  🌐  For the network part of the project (including the weather forecast APP), the network card driver needs to work normally and can access the Internet
-  🎨  Basic support for QtCore/QtWidget/QtNetWork/QtGui/QtCharts/QtMultiMedia
-  📚  For MuPDF based PDF browsers, compiling requires providing MuPDF's cross compiled static library and header files
-  📷  For all OpenCV based projects (including but not limited to MediaPlayer, GeneralLocalCamera), OpenCV4.12.0 compilation support is required.
-  🔗  If the lower computer uses third-party libraries, such as ALSA Lib which is a third-party dynamic library, please ensure that the lower computer environment exists and that the upper computer can retrieve the cross compiled dynamic library during cross compilation.
##  🛠️  Compilation matters for this project
-  🔨  After completing the above work, you can use the CMake configuration interface of QtCreator to compile the project. However, I am still trying to optimize the configuration logic (including automatic dependency checking). Therefore, so far, you still need to manually modify some dependency configurations to start the compilation of this project
-  ⚙️  You can adjust the INCLUDE_ * _ APP to determine which apps are what you want and which are not. For apps that are not needed, simply set the variable to OFF. He will not participate in the compilation.
-  ⚙️  Note that if dependent configuration items are not provided now, the corresponding app will not participate in compilation.
-If OpenCV is installed in a non-standard path, OpenCV_DIR needs to be specified as the download root path (this path needs to directly exist in the OpenCVConfig. cmake file)
-For MuPDF, you need to specify 'MUPDF-INCLUDE-DIR' and 'MUPDF_LIB-DIR'. The variable name is likely to change in the future, and you may need to check the construction logs of CMake for specific adjustments
-  📁  We need to set the 'CCIMX_LAL-RELEASE-DIR-BASE' variable as a basis for downloading. You need to create CCIMX_LAL-RELEASE-DIR-BASE as the basic download path (Install Path) for different distributions