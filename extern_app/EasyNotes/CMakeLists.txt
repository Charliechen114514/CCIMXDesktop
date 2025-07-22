cmake_minimum_required(VERSION 3.19)
project(EasyNotes LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTORCC ON)
qt_standard_project_setup()

set(UiSrc
    ui/EasyNoteMainWindow.cpp
    ui/EasyNoteMainWindow.h
    ui/EasyNoteMainWindow.ui
    ui/SideBarWidget.cpp
    ui/SideBarWidget.h
    ui/SideBarWidget.ui
    ui/LeftSideBar.h
    ui/LeftSideBar.cpp
    ui/LeftSideBar.ui
    ui/MainSideBar.cpp
    ui/MainSideBar.h
    ui/MainSideBar.ui
)

qt_add_executable(EasyNotes
    WIN32 MACOSX_BUNDLE
    ${UiSrc}
    main.cpp
    core/TemperaryCacher.h core/TemperaryCacher.cpp
    sources/icons.qrc
)

target_link_libraries(EasyNotes
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(EasyNotes
    PRIVATE
    . ./ui)

include(GNUInstallDirs)

install(TARGETS EasyNotes
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


add_custom_command(TARGET EasyNotes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:EasyNotes> ${CCIMX_INSTALL_APP_BASE_DIR}
)

qt_generate_deploy_app_script(
    TARGET EasyNotes
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
