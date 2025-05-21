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

## 自动文档生成

📚本项目支持使用Doxygen自动化扫描生成文档，为此，您需要开启对自动化文档构建的支持。默认下，文档生成在[`Documentations/doxygen_style`](Documentations/doxygen_styles)下， 您可以点击[这里](doxygen_styles/html/index.html)进行直接的阅读

如果您希望定制您自己的Doxygen文档风格，您需要注意CMake中以下的构建变量

### 一、启用文档生成功能

要启用文档自动生成功能，请在 CMake 配置命令中定义变量：

```
cmake -DCCIMX_DESKTOP_DOCGEN_REQ=ON \
      -DCCIMX_DOXYGEN_DOCUMENT_BASE_PATH=/your/output/path \
      -DCCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE=/your/path/Doxyfile \
      ..
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



- # How to build this project?

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
  - ⚙️ You can adjust INCLUDE\_*\_APP to adjust which APPs you want and which you don’t need. For any unnecessary APP, just set the variable to OFF. It will not participate in the compilation.
  - ⚙️ Note that if you do not provide the dependent configuration items now, the corresponding App will not participate in the compilation.
  - If OpenCV is installed in a non-standard path, you need to specify OpenCV_DIR as the root path for downloads (this path needs to directly exist in the OpenCVConfig.cmake file)
  - For MuPDF, you need to specify `MUPDF_INCLUDE_DIR` and `MUPDF_LIB_DIR`. This variable name is likely to change later. You may need to check the CMake build log for specific adjustments
  - 📁 You need to set the `CCIMX_ALL_RELEASE_DIR_BASE` variable as a basis for downloads. You need to create CCIMX_ALL_RELEASE_DIR_BASE as the root download path (Install Path) for different distributions

  ## Automatic document generation

  📚This project supports the use of Doxygen to automatically scan and generate documents. To do this, you need to enable support for automatic document building. By default, the documentation is generated under [`Documentations/doxygen_style`](Documentations/doxygen_styles), you can click [here](doxygen_styles/html/index.html) to read it directly

  If you want to customize your own Doxygen documentation style, you need to pay attention to the following build variables in CMake

  ### 1. Enable documentation generation function

  To enable automatic documentation generation, define the variable in the CMake configuration command:

  ```
  cmake -DCCIMX_DESKTOP_DOCGEN_REQ=ON \
  -DCCIMX_DOXYGEN_DOCUMENT_BASE_PATH=/your/output/path \
  -DCCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE=/your/path/Doxyfile \
  ..
  ```

  > Note:
  >
  > - `DCCIMX_DESKTOP_DOCGEN_REQ` controls the overall switch of document building and generation. When it is turned off, the document will not be configured as a buildable project that can be built.
  > - `CCIMX_DOXYGEN_DOCUMENT_BASE_PATH`: **Used to specify the output directory for generating documents, which must exist in advance. **
  > - `CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE`: **Specifies the Doxyfile template path for generating documents, which must be a valid file. It is recommended to modify the DoxyFile in the project root directory as a template**

  ### 2. Build document target

  After enabling, CMake will add a `doc` target, and you can generate documents in the following ways:

  ```
  cmake --build . --target doc
  ```

  This command will call Doxygen to execute the document generation process, and the output is located in the path specified by `CCIMX_DOXYGEN_DOCUMENT_BASE_PATH`. Of course, the build output log will also generate native OUTPUT information for you to confirm and view