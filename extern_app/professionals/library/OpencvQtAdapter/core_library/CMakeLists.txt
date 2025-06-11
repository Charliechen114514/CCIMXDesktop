cmake_minimum_required(VERSION 3.16)

project(core_library LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui)

set(CVImageSrc
    cvimage/CVImage.h
    cvimage_src/CVImage.cpp
    cvimage/CVImagePrivateOpencvImp.h
    cvimage_src/CVImagePrivateOpencvImp.cpp
    cvimage/CVImageImpl.h
    cvimage_src/CVImageImpl.cpp
    cvimage/CVTools.h
    cvimage_src/CVTools.cpp)

set(VideoPlayerSrc
    videoplayer/VideoPlayer.h videoplayer_src/VideoPlayer.cpp
    videoplayer/VideoPlayerImpl.h
    videoplayer/VideoPlayerOpencvImpl.h videoplayer_src/VideoPlayerOpencvImpl.cpp)

set(QtAdapter
    QtAdapter/QtAdaptTools.h
    QtAdapter/QtAdaptTools.cpp)

set(ImageProcSrc
    image_proc/image_proc_base.h
    image_proc/GrayProcessor.h image_proc_src/GrayProcessor.cpp
    image_proc_src/image_proc_opencv_impl/OpenCV_ProcessAdapter.h
    image_proc_src/image_proc_opencv_impl/OpenCV_ProcessAdapter.cpp
    image_proc/BlurProcessor.h
    image_proc_src/BlurProcessor.cpp
    image_proc/CannyProcessor.h
    image_proc_src/CannyProcessor.cpp
    image_proc/ContoursQueryProc.h
    image_proc_src/ContoursQueryProc.cpp)

add_library(core_library STATIC
    ${CVImageSrc}
    ${VideoPlayerSrc}
    ${QtAdapter}
    ${ImageProcSrc}


)

target_include_directories(
    core_library
    PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        # Add the source file dirent
        # as we need to include the header files
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cvimage>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/videoplayer>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/image_proc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/QtAdapter>
)

target_link_libraries(
    core_library
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
    PUBLIC
        ${OpenCV_LIBS}
)

target_compile_definitions(
    core_library
    PRIVATE
    CORE_LIBRARY_LIBRARY)
