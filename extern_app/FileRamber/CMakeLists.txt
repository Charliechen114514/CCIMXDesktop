cmake_minimum_required(VERSION 3.19)
project(FileRamber LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Concurrent)

set(UiSrc
    Ui/MainWindow.cpp
    Ui/MainWindow.h
    Ui/MainWindow.ui
    Ui/CCIMXFileSystemModel.h
    Ui/CCIMXFileSystemModel.cpp)

set(CoreSrc
    Core/FileInfoProvider.h Core/FileInfoProvider.cpp
    Core/FileNameProviders.h Core/FileNameProviders.cpp)

qt_standard_project_setup()

qt_add_executable(FileRamber
    WIN32 MACOSX_BUNDLE
    ${UiSrc}
    ${CoreSrc}
    main.cpp
    Core/FileCountInfo.h Core/FileCountInfo.cpp
    Core/DirentSizeCounter.h Core/DirentSizeCounter.cpp
    Core/FileTypeInfo.h Core/FileTypeInfo.cpp
    source/icons.qrc
    Ui/FileInfoDisplayWidget.h Ui/FileInfoDisplayWidget.cpp Ui/FileInfoDisplayWidget.ui
    Core/FileRamberTools.h Core/FileRamberTools.cpp

)

target_link_libraries(FileRamber
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Concurrent
)
target_include_directories(FileRamber PRIVATE . ./Ui ./Core)
include(GNUInstallDirs)

install(TARGETS FileRamber
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET FileRamber
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
