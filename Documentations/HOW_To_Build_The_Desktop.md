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

- 🔨 完成上述工作后，您可以使用——
  - （方式1）QtCreator的 CMake 配置界面，CMake-GUI对项目进行编译，但是这个方式无法区分具体的配置项目，笔者保留是因为历史原因和默认的支持原因
  - （方式2：推介）：您需要复制`configs/CCIMXDesktopBuildConfigs.cmake.template`到如下可选的方案：
    - 方案1：复制到项目的根文件夹下，将`CCIMXDesktopBuildConfigs.cmake.template`重命名为`CCIMXDesktopLocalDefaults.cmake`，填写您需要的依赖项目路径
    - 方案2：如果您不希望放置到项目的根文件夹下和认为`CCIMXDesktopLocalDefaults.cmake`的名称不自由，可以自由的放置到您想放置的位置上，随后设置`LOCAL_CONFIG_FILE`变量指向您的cmake配置文件，如果配置文件并不存在，将会fallback到方案一的检查上，如果方案一检索失败，将会报错！

下面的部分是针对配置文件的说明：

- ⚙️ 您可以调整INCLUDE\_*\_APP来调整哪些APP是您想要的，哪些不需要，凡是不需要的APP只需要设置该变量为OFF即可。他就不会参与编译。（这个您可以设置`INCLUDE_*_APP`的值进行决定是否构建）

- ⚙️ 注意，现在如果不提供依赖的配置项的话，对应的App不会参与编译。
  - OpenCV若安装在非标准路径下，需要指定OpenCV_DIR作为下载的根路径（这个路径需要直接存在OpenCVConfig.cmake文件）
  - MuPDF则需要指定`MUPDF_INCLUDE_DIR`和`MUPDF_LIB_DIR`，您可能需要查看CMake的构建日志进行具体的调整

- 📁 需要设置`_DEF_RELEASE_BASE_MSVC_RELEASE`变量或者是`_DEF_RELEASE_BASE_GCC_RELEASE`作为下载的一个基础。这取决于您采用的编译器

  > 将这个进行分离是因为镜像构建的方便性，当然，如果您确定只使用其中一款编译器，可以不定义另外的量

## 自动文档生成

📚本项目支持使用Doxygen自动化扫描生成文档，为此，您需要开启对自动化文档构建的支持。

如果您希望定制您自己的Doxygen文档风格，您需要注意CMake中以下的构建变量

### 一、启用文档生成功能

要启用文档自动生成功能，请您确保Doxygen是存在的，然后设置配置文件中的这些变量：

```
# Options for the Automatically generate documentations
set(CCIMX_DOXYGEN_DOCUMENT_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Documentations/doxygen_styles CACHE PATH "Doxygen folders base")
set(CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile CACHE PATH "Doxygen template file path")
```

> 注意：
>
> - `DCCIMX_DESKTOP_DOCGEN_REQ`控制文档的构建和生成总开关，关闭后文档将不会配置成为一个可以被构建的可构建项目
> - `CCIMX_DOXYGEN_DOCUMENT_BASE_PATH`：**用于指定生成文档的输出目录，需事先存在。**
> - `CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE`：**指定用于生成文档的 Doxyfile 模板路径，需为有效文件。建议在项目根目录的DoxyFile作为模板修改**

### 二、构建文档目标

启用后，CMake 会添加一个 `doc` 目标，你可以通过以下方式生成文档：

```
cmake --build . --target doc
```

该命令会调用 Doxygen 执行文档生成流程，输出位于 `CCIMX_DOXYGEN_DOCUMENT_BASE_PATH` 所指定的路径下。当然，构建输出日志也会生成原生的OUTPUT信息以供您确认和查看



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

- 🔨 After completing the above work, you can use——
- (Method 1) QtCreator's CMake configuration interface, CMake-GUI to compile the project, but this method cannot distinguish specific configuration projects. The author retains it for historical reasons and default support reasons
- (Method 2: Recommended): You need to copy `configs/CCIMXDesktopBuildConfigs.cmake.template` to the following optional solutions:
- Solution 1: Copy to the root folder of the project, rename `CCIMXDesktopBuildConfigs.cmake.template` to `CCIMXDesktopLocalDefaults.cmake`, and fill in the path of the dependent project you need
- Solution 2: If you do not want to place it in the root folder of the project and think that the name of `CCIMXDesktopLocalDefaults.cmake` is not free, you can freely place it where you want, and then set the `LOCAL_CONFIG_FILE` variable to point to your cmake configuration file. If the configuration file does not exist, it will fallback to the check in Solution 1. If the search in Solution 1 fails, an error will be reported!

The following section is a description of the configuration file:

- ⚙️ You can adjust INCLUDE\_*\_APP to adjust which APPs you want and which you don’t need. For any unnecessary APP, just set the variable to OFF. It will not participate in the compilation. (You can set the value of `INCLUDE_*_APP` to decide whether to build)

- ⚙️ Note that if you do not provide the dependent configuration items, the corresponding App will not participate in the compilation.

- If OpenCV is installed in a non-standard path, you need to specify OpenCV_DIR as the root path for download (this path needs to directly exist in the OpenCVConfig.cmake file)
- For MuPDF, you need to specify `MUPDF_INCLUDE_DIR` and `MUPDF_LIB_DIR`. You may need to check the CMake build log for specific adjustments

- 📁 You need to set the `_DEF_RELEASE_BASE_MSVC_RELEASE` variable or `_DEF_RELEASE_BASE_GCC_RELEASE` as a basis for download. This depends on the compiler you use

> This is separated because of the convenience of image building. Of course, if you are sure to use only one of the compilers, you don’t need to define another variable

## Automatic document generation

📚This project supports the use of Doxygen to automatically scan and generate documents. To do this, you need to enable support for automatic document building. 

If you want to customize your own Doxygen documentation style, you need to pay attention to the following build variables in CMake

### 1. Enable documentation generation

To enable the automatic documentation generation function, please make sure Doxygen exists, and then set these variables in the configuration file:

```
# Options for the Automatically generate documentations
set(CCIMX_DOXYGEN_DOCUMENT_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Documentations/doxygen_styles CACHE PATH "Doxygen folders base")
set(CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile CACHE PATH "Doxygen template file path")
```

> Note:
>
> - `DCCIMX_DESKTOP_DOCGEN_REQ` controls the overall switch of document building and generation. After turning it off, the document will not be configured as a buildable project that can be built
> - `CCIMX_DOXYGEN_DOCUMENT_BASE_PATH`: **Used to specify the output directory for generating documents, which must exist in advance. **
> - `CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE`: **Specifies the Doxyfile template path used to generate documents, which must be a valid file. It is recommended to modify the DoxyFile in the project root directory as a template**

### 2. Build documentation target

After enabling, CMake will add a `doc` target, and you can generate documentation in the following ways:

```
cmake --build . --target doc
```

This command will call Doxygen to execute the document generation process, and the output is located in the path specified by `CCIMX_DOXYGEN_DOCUMENT_BASE_PATH`. Of course, the build output log will also generate native OUTPUT information for you to confirm and view