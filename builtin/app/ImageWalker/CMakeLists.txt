cmake_minimum_required(VERSION 3.19)
project(ImageWalker LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(UiSrc
    ui/ImageWalkerWindow.cpp
    ui/ImageWalkerWindow.h
    ui/ImageWalkerWindow.ui
    ui/ImageBrowser.h ui/ImageBrowser.cpp ui/ImageBrowser.ui
    ui/ImageInfoWindow.h ui/ImageInfoWindow.cpp ui/ImageInfoWindow.ui
    ui/ImageLabel.h ui/ImageLabel.cpp)

set(CoreSrc
    core/ImageCore.h core/ImageCore.cpp)
qt_add_executable(ImageWalker
    WIN32 MACOSX_BUNDLE
    ${UiSrc}
    ${CoreSrc}
    main.cpp
    sources/icons.qrc
)

target_link_libraries(ImageWalker
    PRIVATE
        Qt::Core
        Qt::Widgets
)

target_include_directories(ImageWalker
    PRIVATE
    . ./ui ./core)

include(GNUInstallDirs)

install(TARGETS ImageWalker
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ImageWalker
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

add_custom_command(TARGET ImageWalker POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_EXTERNAL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ImageWalker> ${CCIMX_EXTERNAL_APP_BASE_DIR}
)
