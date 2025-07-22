cmake_minimum_required(VERSION 3.19)
project(SimpleDrawer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(SimpleDrawer
    WIN32 MACOSX_BUNDLE
    main.cpp
    ui/DrawerWindow.cpp
    ui/DrawerWindow.h
    ui/DrawerWindow.ui
    ui/SimpleDrawerWidget.h ui/SimpleDrawerWidget.cpp ui/SimpleDrawerWidget.ui
    core/SimpleDrawingScene.h core/SimpleDrawingScene.cpp
    settings.h
    ui/SaveWindow.h ui/SaveWindow.cpp ui/SaveWindow.ui
    sources/icons.qrc
)

target_link_libraries(SimpleDrawer
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(SimpleDrawer
    PRIVATE . ./ui)

include(GNUInstallDirs)

install(TARGETS SimpleDrawer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(TARGET SimpleDrawer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SimpleDrawer> ${CCIMX_INSTALL_APP_BASE_DIR}
)

qt_generate_deploy_app_script(
    TARGET SimpleDrawer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
