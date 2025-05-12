cmake_minimum_required(VERSION 3.19)
project(MediaPlayer LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

set(DEFAULT_OPENCV_DIR "" CACHE PATH "Path to OpenCV library")
set(_DEFAULT_OPENCV_DIR_MSVC "D:/stdcpp-library/opencvLibrary")
set(_DEFAULT_OPENCV_DIR_ARM "/home/charliechen/imx6ull/opencv_arm_res/lib/cmake/opencv4")
set(_DEFAULT_OPENCV_DIR_GCC "/home/charliechen/imx6ull/opencv_res/lib/cmake/opencv4")
set(MEDIAPLAYER_ALSA_LIBRARY "/home/charliechen/imx6ull/alsalib_res/lib" CACHE PATH "Path to the ALSA Library")
if(MSVC)
    message(STATUS "Compiling with MSVC on Windows")
    if(NOT DEFAULT_OPENCV_DIR)
        set(DEFAULT_OPENCV_DIR ${_DEFAULT_OPENCV_DIR_MSVC})
    endif()
elseif(CMAKE_CXX_COMPILER MATCHES "arm.*-g\\+\\+")
    message(STATUS "Cross-compiling for ARM (IMX6ULL)")
    if(NOT DEFAULT_OPENCV_DIR)
        set(DEFAULT_OPENCV_DIR ${_DEFAULT_OPENCV_DIR_ARM})
        # For IMX6ULL, we need to add the hard float support
    endif()
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -march=armv7-a -mfpu=neon -mfloat-abi=hard")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv7-a -mfpu=neon -mfloat-abi=hard")
    set(ALSA_LIBRARY_PATH ${MEDIAPLAYER_ALSA_LIBRARY})
    message(STATUS "Select the building ALSA Library =${ALSA_LIBRARY_PATH}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${ALSA_LIBRARY_PATH}")
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

set(MediaBaseSource
    base/CVImage.cpp base/CVImage.h
    base/CVImageImpl.cpp base/CVImageImpl.h
    base/CVImagePrivateOpencvImp.cpp base/CVImagePrivateOpencvImp.h
    base/CVTools.cpp base/CVTools.h
    base/VideoPlayer.cpp
    base/VideoPlayer.h
    base/VideoPlayerImpl.cpp
    base/VideoPlayerImpl.h
    base/VideoPlayerOpencvImpl.cpp
    base/VideoPlayerOpencvImpl.h
    base/MediaPlayer.h base/MediaPlayer.cpp
    base/QtAdaptTools.cpp base/QtAdaptTools.h
)

set(CoreSoruce
    core/MediaEnableSelectFactory.h
    core/MediaEnableSelectFactory.cpp
    core/UiTools.h core/UiTools.cpp
    core/CCMediaPlayList.h core/CCMediaPlayList.cpp)

set(UiSource
    ui/MediaPlayerWindow.cpp
    ui/MediaPlayerWindow.h
    ui/MediaPlayerWindow.ui
    ui/DiskMusic.h ui/DiskMusic.cpp ui/DiskMusic.ui
    ui/MediaInfoWindow.h ui/MediaInfoWindow.cpp ui/MediaInfoWindow.ui
    ui/PlayListMainWindow.h ui/PlayListMainWindow.cpp ui/PlayListMainWindow.ui)


qt_add_executable(MediaPlayer
    WIN32 MACOSX_BUNDLE
    ${MediaBaseSource}
    ${UiSource}
    ${CoreSoruce}
    main.cpp
    sources/icons.qrc
    ui/ScrollingLabel.h ui/ScrollingLabel.cpp ui/ScrollingLabel.ui
)

target_include_directories(MediaPlayer
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${OPENCV_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

target_link_libraries(MediaPlayer
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Multimedia
        ${OpenCV_LIBS}
)

add_custom_command(TARGET MediaPlayer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MediaPlayer> ${CCIMX_ALL_RELEASE_DIR}
)

include(GNUInstallDirs)

install(TARGETS MediaPlayer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET MediaPlayer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
