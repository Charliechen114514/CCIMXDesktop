cmake_minimum_required(VERSION 3.19)
project(SystemState LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Charts)

set(UiSrc
    Ui/SystemStateWindow.cpp
    Ui/SystemStateWindow.h
    Ui/SystemStateWindow.ui
    Ui/stackpage_switcher_animation.cpp Ui/stackpage_switcher_animation.h
    Ui/CPUUsageChart.h Ui/CPUUsageChart.cpp Ui/CPUUsageChart.ui
    Ui/MemoryUsageChart.h Ui/MemoryUsageChart.cpp Ui/MemoryUsageChart.ui
    Ui/ProcessBrowserWidget.h Ui/ProcessBrowserWidget.cpp Ui/ProcessBrowserWidget.ui
)

set(CoreSrc
    Core/MemoryInfoFetcher.h
    Core/MemoryInfoFetcher.cpp
    Core/CPUStateFetcher.h Core/CPUStateFetcher.cpp
    Core/ProcessBroswer.h Core/ProcessBroswer.cpp)

set(PlatformAdapter
    platforms/PlatformDriverFactory.h
    platforms/PlatformDriverFactory.cpp)

if(WIN32)
    message(STATUS "Build As the Windows Driver Platform")
    set(PlatformDriver platforms/Win32PlatformDrivers.h platforms/Win32PlatformDrivers.cpp)
else()
    message(STATUS "Build As the Linux or *nix Platform")
endif()

include_directories(. ./Ui ./Core ./platform)

qt_standard_project_setup()

qt_add_executable(SystemState
    WIN32 MACOSX_BUNDLE
    ${UiSrc}
    ${CoreSrc}
    ${PlatformDriver}
    ${PlatformAdapter}
    main.cpp
    sources/icons.qrc
)

add_custom_command(TARGET SystemState POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SystemState> ${CCIMX_ALL_RELEASE_DIR}
)

target_link_libraries(SystemState
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Charts
)

include(GNUInstallDirs)

install(TARGETS SystemState
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SystemState
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
