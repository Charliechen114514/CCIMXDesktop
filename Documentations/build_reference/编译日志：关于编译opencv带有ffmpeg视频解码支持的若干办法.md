# 编译日志：关于编译opencv带有ffmpeg视频解码支持的若干办法

## 前言

​	笔者这里是封装了简单的OpenCV视频播放抽象，然后却发现移植到Ubuntu和开发板上都罢工的事情，原来是Windows平台下我们是默认下载了ffmpeg的库的，但是在泛Linux平台下却不一定，因此，我们需要自己手动的构建ffmpeg + opencv联合编译。

​	值得一题的是，因为笔者这里的IMX6ULL上没有硬件解码芯片，因此笔者需要自己客制化ffmpeg，所以这里笔者打算介绍一下ffmpeg的编译方式 + OpenCV如何进一步的进行调整

## 编译ffmpeg

​	由于我当时是想将ffmpeg同时用在作为QMultiMedia的后端，因此我下载了我使用的Qt6.8.3推介的ffmpeg分支：

```
git clone --branch n7.1 https://git.ffmpeg.org/ffmpeg.git ffmpeg
```

​	这个是文档中给出的，地址在[Building FFmpeg from source on Linux | Qt Multimedia | Qt 6.9.0](https://doc.qt.io/qt-6/qtmultimedia-building-ffmpeg-linux.html)，当然，你可以自己选择根据自己项目的ffmpeg，这里跟我们的OpenCV编译是没有关系的，但是ffmpeg的接口在不同的版本不一样，所以你最好是看看opencv要的是哪个版本的接口（看Documentations），笔者因为编译的是最新的OpenCV4.12.0，所以这个branch的ffmpeg当然能用。

​	下载好了ffmpeg后，写一个构建脚本表明自己需要哪些东西被编译：

```
➜  cat auto.sh 
./configure \
  --prefix=/home/charliechen/imx6ull/ffmpeg-arm-dynamic \
  --cross-prefix=arm-linux-gnueabihf- \
  --target-os=linux \
  --arch=arm \
  --enable-cross-compile \
  --disable-static \
  --enable-shared \
  --disable-doc \
  --disable-programs \
  --disable-everything \
  --enable-avformat \
  --enable-avcodec \
  --enable-avutil \
  --enable-swresample \
  --enable-swscale \
  --enable-decoder=mp3,aac,flac,h264 \
  --enable-demuxer=mp3,aac,flac,h264,mov,matroska \
  --enable-parser=mp3,aac,h264 \
  --enable-protocol=file \
  --disable-network \
  --disable-iconv \
  --disable-zlib \
  --disable-bzlib \
  --disable-encoders \
  --disable-muxers \
  --disable-filters \
  --disable-hwaccels \
  --disable-postproc \
  --disable-debug \
  --extra-cflags="-O2 -march=armv7-a -mfpu=neon -mfloat-abi=hard"
```

​	这里笔者说明一下这些参数的含义，这里是交叉编译成动态库的版本，笔者发现默认的OpenCV是需要ffmpeg动态库的，当然你可以设置CMake要的FFMPEG是静态连接，但是笔者没有尝试，这个留给大家尝试

- `--prefix=/home/charliechen/imx6ull/ffmpeg-arm-dynamic`
  **作用**：指定 FFmpeg 的安装路径，编译后的库和头文件会安装到这个目录。
  **用途**：方便后续程序链接动态库。
- `--cross-prefix=arm-linux-gnueabihf-`
  **作用**：指定交叉编译工具链的前缀（如 `arm-linux-gnueabihf-gcc`）。
  **用途**：用于 ARM 平台的交叉编译。
- `--target-os=linux`
  **作用**：指定目标操作系统为 Linux。
  **用途**：确保生成适用于 Linux 的二进制文件。
- `--arch=arm`
  **作用**：指定目标 CPU 架构为 ARM。
  **用途**：生成 ARM 指令集的代码。
- `--enable-cross-compile`
  **作用**：显式启用交叉编译模式。
  **用途**：确保配置脚本正确处理交叉编译环境。

- `--disable-static`
  **作用**：禁用静态库（`.a` 文件）的生成。
  **用途**：减少编译输出体积，仅生成动态库。
- `--enable-shared`
  **作用**：启用动态库（`.so` 文件）的生成。
  **用途**：生成动态链接库，便于多程序共享。

- `--disable-doc`
  **作用**：跳过文档生成。
  **用途**：减少编译时间和依赖。
- `--disable-programs`
  **作用**：不编译 `ffmpeg`、`ffplay` 等命令行工具。
  **用途**：仅生成库文件，适用于嵌入式场景。
- `--disable-everything`
  **作用**：禁用所有默认启用的组件。
  **用途**：允许后续通过 `--enable-xxx` 手动启用需要的功能，实现极致裁剪。
- `--enable-avformat`、`--enable-avcodec` 等
  **作用**：选择性启用核心库（如封装、编解码、工具库等）。
  **用途**：仅保留必要的功能模块。

- `--enable-decoder=mp3,aac,flac,h264`
  **作用**：仅启用指定的解码器（MP3、AAC、FLAC、H.264）。
  **用途**：减少不必要的解码器，节省空间。
- `--enable-demuxer=mp3,aac,flac,h264,mov,matroska`
  **作用**：启用指定的解复用器（支持 MP3、AAC、FLAC、H.264、MOV、MKV 等容器格式）。
  **用途**：仅支持目标平台需要的容器格式。
- `--enable-parser=mp3,aac,h264`
  **作用**：启用指定的解析器（用于解码前的数据解析）。
  **用途**：优化解码流程。
- `--enable-protocol=file`
  **作用**：仅启用 `file` 协议（本地文件访问）。
  **用途**：禁用网络功能（如 HTTP、RTMP），提高安全性。

- `--disable-network`
  **作用**：彻底禁用所有网络相关功能。
  **用途**：嵌入式设备可能不需要网络流媒体支持。
- `--disable-iconv`、`--disable-zlib`、`--disable-bzlib`
  **作用**：禁用字符编码转换、Zlib/BZip2 压缩支持。
  **用途**：进一步减少依赖和体积。
- `--disable-encoders`、`--disable-muxers`
  **作用**：禁用所有编码器和复用器。
  **用途**：仅需解码功能时使用。
- `--disable-filters`、`--disable-hwaccels`、`--disable-postproc`
  **作用**：禁用滤镜、硬件加速和后处理。
  **用途**：简化功能，适用于资源受限设备。
- `--disable-debug`
  **作用**：禁用调试信息。
  **用途**：减少二进制体积，提高性能。

- `--extra-cflags="-O2 -march=armv7-a -mfpu=neon -mfloat-abi=hard"`
  **作用**：传递额外的编译选项：
  - `-O2`：启用优化，平衡性能和体积。
  - `-march=armv7-a`：指定 ARMv7-A 架构（i.MX6ULL 的 Cortex-A7 兼容）。
  - `-mfpu=neon`：启用 NEON 浮点加速指令。
  - `-mfloat-abi=hard`：使用硬件浮点（与工具链配置一致）。
    **用途**：针对目标芯片优化性能。

​	为了UBuntu上位机也Mirror一份环境，我们只需要稍微改一下架构即可。

```
./configure \
  --prefix=/home/charliechen/imx6ull/ffmpeg-x86 \
  --target-os=linux \
  --disable-static \
  --enable-shared \
  --disable-doc \
  --disable-programs \
  --disable-everything \
  --enable-avformat \
  --enable-avcodec \
  --enable-avutil \
  --enable-swresample \
  --enable-swscale \
  --enable-decoder=mp3,aac,flac,h264 \
  --enable-demuxer=mp3,aac,flac,h264,mov,matroska \
  --enable-parser=mp3,aac,h264 \
  --enable-protocol=file \
  --disable-network \
  --disable-iconv \
  --disable-zlib \
  --disable-bzlib \
  --disable-encoders \
  --disable-muxers \
  --disable-filters \
  --disable-hwaccels \
  --disable-postproc \
  --disable-debug
```

> PS：如果交叉编译它告诉你LD的时候文件格式非法，转向make clean清理构建的同时export LD=/path/to/cross_compile_ld即可，说明LD连接器还是用了宿主机的。

## OpenCV对接

​	OpenCV的对接上，笔者看了非常多的博客，发现这些博客对pkgconfig和CMake构建系统的认知匮乏，绕了好大的弯子，实际上，完全可以通过给定pkgconfig的环境变量解决这个事情。

### 上位机的编译

​	对于上位机的编译，我们跟往常一样，只需要在同一个shell中给定pkgconfig的搜索路径即可

```
export PKG_CONFIG_PATH=/path/to/x86/ffmpeg/lib/pkgconfig;$PKG_CONFIG_PATH  # 指向检索ffmpeg的pkgconfig路径即可
```

​	之后，我们在同一个环境下起cmake-gui,让cmake-gui继承环境变量，就可以让CMake找到我们的ffmpeg了，注意的是，让CMake决议认为ffmpeg不存在的原因非常多，如果你这样搞不定，去检索FFMPEG的cmake文件下打日志解决，看看哪些地方被否掉了导致判定ffmpeg不存在。

​	需要注意的是，你必须看到这样的结果日志：

```
--   FFMPEG:                      YES
--     avcodec:                   YES (ver x.x.x)
--     avformat:                  YES (ver x.x.x)
--     avutil:                    YES (ver x.x.x)
...
```

​	任何一点不一样，你的ffmpeg就会集成失败，问题留到后面是很麻烦的，立马解决。

### 下位机ARM32编译

​	OpenCV禁掉了使用PKG_CONFIG_PATH来指定交叉编译库路径的可能。

```
OpenCV disables pkg-config to avoid using of host libraries. Consider using PKG_CONFIG_LIBDIR to specify target SYSROOT
```

​	这个事情我们的CMake日志就告诉了我们的解决方案，是转向定义：

```
export PKG_CONFIG_LIBDIR=/path/to/arm/ffmpeg/lib/pkgconfig;$PKG_CONFIG_LIBDIR
```

​	现在就可以了。然后剩下的配置如法炮制即可。没有任何其他的变化！



