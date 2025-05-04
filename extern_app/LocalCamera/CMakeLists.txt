cmake_minimum_required(VERSION 3.19)
project(LocalCamera LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia MultimediaWidgets)

qt_standard_project_setup()

qt_add_executable(LocalCamera
    WIN32 MACOSX_BUNDLE
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    DesktopToast.cpp DesktopToast.h
    sources/icons.qrc
)

target_link_libraries(LocalCamera
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
)

include(GNUInstallDirs)

install(TARGETS LocalCamera
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET LocalCamera
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
