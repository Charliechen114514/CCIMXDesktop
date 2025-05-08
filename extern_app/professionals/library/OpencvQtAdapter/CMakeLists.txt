cmake_minimum_required(VERSION 3.19)
project(OpencvQtAdapter LANGUAGES CXX)

option(REQ_PROXY "Download externally needs proxy" OFF)
set(_DEFAULT_PROXY "http://127.0.0.1:7890")

if(REQ_PROXY)
    message(STATUS "Proxy is required due to the settings of REQ_PROXY")
    if(NOT DEFINED ENV{HTTP_PROXY})
        message(STATUS "HTTP_PROXY is not defined, set to default value: ${_DEFAULT_PROXY}")
        set(ENV{HTTP_PROXY} "${_DEFAULT_PROXY}")
    endif()

    if(NOT DEFINED ENV{HTTPS_PROXY})
        message(STATUS "HTTPS_PROXY is not defined, set to default value: ${_DEFAULT_PROXY}")
        set(ENV{HTTPS_PROXY} "${_DEFAULT_PROXY}")
    endif()
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
set(DEFAULT_OPENCV_DIR "" CACHE PATH "Path to OpenCV library")
set(_DEFAULT_OPENCV_DIR_MSVC "D:/stdcpp-library/opencvLibrary")
set(_DEFAULT_OPENCV_DIR_ARM "/home/charliechen/imx6ull/opencv_arm_res/lib/cmake/opencv4")
set(_DEFAULT_OPENCV_DIR_GCC "/home/charliechen/imx6ull/opencv_res/lib/cmake/opencv4")

if(MSVC)
    message(STATUS "Compiling with MSVC on Windows")
    if(NOT DEFAULT_OPENCV_DIR)
        set(DEFAULT_OPENCV_DIR ${_DEFAULT_OPENCV_DIR_MSVC})
    endif()
elseif(CMAKE_CXX_COMPILER MATCHES "arm.*-g\\+\\+")
    message(STATUS "Cross-compiling for ARM (IMX6ULL)")
    if(NOT DEFAULT_OPENCV_DIR)
        set(DEFAULT_OPENCV_DIR ${_DEFAULT_OPENCV_DIR_ARM})
    endif()
else()
    message(STATUS "Compiling for x86_64 or host (non-MSVC)")
    if(NOT DEFAULT_OPENCV_DIR)
        set(DEFAULT_OPENCV_DIR ${_DEFAULT_OPENCV_DIR_GCC})
    endif()
endif()

set(OpenCV_DIR "${DEFAULT_OPENCV_DIR}")
message(STATUS "OpenCV_DIR is set to: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

qt_standard_project_setup()

# Build the core library first
add_subdirectory(core_library)
add_subdirectory(core_library_test)

add_subdirectory(examples)
add_subdirectory(gui_example)
