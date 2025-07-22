cmake_minimum_required(VERSION 3.19)
project(CCNetHelper LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network Concurrent)
set(CMAKE_CXX_STANDARD 20)
qt_standard_project_setup()

set(UiSrc
    ui/NetMainWindow.cpp
    ui/NetMainWindow.h
    ui/NetMainWindow.ui
    ui/SideBarWidget.cpp
    ui/SideBarWidget.h
    ui/SideBarWidget.ui
    ui/ToolBoxs.h ui/ToolBoxs.cpp ui/ToolBoxs.ui
    ui/InterfacesDisplayWidget.h ui/InterfacesDisplayWidget.cpp ui/InterfacesDisplayWidget.ui
    ui/fasttools.h
    ui/MainShowWidget.h ui/MainShowWidget.cpp ui/MainShowWidget.ui
    ui/Pinger.h ui/Pinger.cpp ui/Pinger.ui
    ui/Scanner.h ui/Scanner.cpp ui/Scanner.ui)

set(CoreSrc
    core/interfaces_query/InterfacesQuery.h core/interfaces_query/InterfacesQuery.cpp
    core/interfaces_query/FormatDisplayFactory.h core/interfaces_query/FormatDisplayFactory.cpp)

qt_add_executable(CCNetHelper
    WIN32 MACOSX_BUNDLE
    ${UiSrc}
    ${CoreSrc}
    main.cpp
    sources/icons.qrc
)

target_link_libraries(CCNetHelper
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Network
        Qt6::Concurrent
)

target_include_directories(CCNetHelper
    PRIVATE . ./ui)

include(GNUInstallDirs)

install(TARGETS CCNetHelper
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(TARGET CCNetHelper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CCNetHelper> ${CCIMX_INSTALL_APP_BASE_DIR}
)

qt_generate_deploy_app_script(
    TARGET CCNetHelper
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
