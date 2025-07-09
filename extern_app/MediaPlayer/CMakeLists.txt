cmake_minimum_required(VERSION 3.19)
project(MediaPlayer LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)
find_package(OpenCV REQUIRED)

qt_standard_project_setup()

set(MediaBaseSource
    base/CVImage.cpp base/CVImage.h
    base/CVImageImpl.cpp base/CVImageImpl.h
    base/CVImagePrivateOpencvImp.cpp base/CVImagePrivateOpencvImp.h
    base/CVTools.cpp base/CVTools.h
    base/VideoPlayer.cpp
    base/VideoPlayer.h

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
    ui/PlayListMainWindow.h ui/PlayListMainWindow.cpp ui/PlayListMainWindow.ui
    ui/ScrollingLabel.h ui/ScrollingLabel.cpp ui/ScrollingLabel.ui)


qt_add_executable(MediaPlayer
    WIN32 MACOSX_BUNDLE
    ${MediaBaseSource}
    ${UiSource}
    ${CoreSoruce}
    main.cpp
    sources/icons.qrc
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
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_EXTERNAL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:MediaPlayer> ${CCIMX_EXTERNAL_APP_BASE_DIR}
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
