cmake_minimum_required(VERSION 3.19)
project(GeneralLocalCamera LANGUAGES CXX)
SET(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

find_package(OpenCV REQUIRED)
include_directories(. ./Core ./Ui)

qt_standard_project_setup()

set(UiSource
    Ui/CameraWindow.cpp
    Ui/CameraWindow.h
    Ui/CameraWindow.ui
    Ui/CameraDisplayWidget.h
    Ui/CameraDisplayWidget.cpp
    Ui/CameraDisplayWidget.ui
    Ui/DesktopToast.cpp
    Ui/DesktopToast.h)

set(CoreSource
    Core/CameraDeviceSelector.h
    Core/CameraDeviceSelector.cpp
    Core/CameraCapture.h
    Core/CameraCapture.cpp
    Core/PhotoSaver.h
    Core/PhotoSaver.cpp)


qt_add_executable(GeneralLocalCamera
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${UiSource}
    ${CoreSource}
    sources/icons.qrc
)

add_custom_command(TARGET GeneralLocalCamera POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:GeneralLocalCamera> ${CCIMX_ALL_RELEASE_DIR}
)

target_include_directories(GeneralLocalCamera PRIVATE ${OpenCV_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS}/opencv2)

target_link_libraries(GeneralLocalCamera
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${OpenCV_LIBS}
)

include(GNUInstallDirs)

install(TARGETS GeneralLocalCamera
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET GeneralLocalCamera
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
