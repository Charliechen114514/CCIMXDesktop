cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX)
set(CMAKE_AUTORCC ON)

# Options for support
option(INCLUDE_WEATHER_APP "Build the Weather App" ON)
option(INCLUDE_PDF_BROWSER_APP "Build the PDF Browser App" ON)
option(INCLUDE_CAMERA_APP "Build the Camera App" ON)
option(INCLUDE_FILERAMBER_APP "Build the FileRamber App" ON)
option(INCLUDE_SYSTEMSTATUS_APP "Build the System Status App" ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
qt_standard_project_setup()

# Options for the default use install
set(_DEF_RELEASE_BASE_MSVC_RELEASE  "D:/NewQtProjects/Release/")
set(_DEF_RELEASE_BASE_GCC_RELEASE   "/home/charliechen/imx6ull/qt683_project/CCDesktopRelease")

# This part aims to find the Cross compile
# If you only get the arm mupdf compiles, do notice to select the
# correct kits with correct arch and compilers
message(STATUS "Ready to select the install path for the cross compile")
# if the CCIMX_ALL_RELEASE_DIR_BASE is not defined, set it to a default value
if(NOT DEFINED CCIMX_ALL_RELEASE_DIR_BASE OR CCIMX_ALL_RELEASE_DIR_BASE STREQUAL "")
    message(STATUS "CCIMX_ALL_RELEASE_DIR_BASE is not defined, set to default value")
    if(MSVC)
        message(STATUS "MSVC compiler detected, assume you are in Windows")
        set(_default_release_base ${_DEF_RELEASE_BASE_MSVC_RELEASE})
    else()
        set(_default_release_base ${_DEF_RELEASE_BASE_GCC_RELEASE})
    endif()

    if(NOT IS_DIRECTORY "${_default_release_base}")
        message(FATAL_ERROR
            "Default path '${_default_release_base}' does not exist. Please manually specify CCIMX_ALL_RELEASE_DIR_BASE "
            "in the top level CMakeLists.txt, or, "
            "You are supposed to use cmake-gui to set the path.")
    else()
        message(STATUS "Pass check of the default path: '${_default_release_base}'")
    endif()

    set(CCIMX_ALL_RELEASE_DIR_BASE "${_default_release_base}" PATH "Base release install path for deployment")
else()
    message(STATUS "CCIMX_ALL_RELEASE_DIR_BASE is defined: ${CCIMX_ALL_RELEASE_DIR_BASE}")
    if(NOT IS_DIRECTORY "${CCIMX_ALL_RELEASE_DIR_BASE}")
        message(FATAL_ERROR
            "Specified CCIMX_ALL_RELEASE_DIR_BASE does not exist: ${CCIMX_ALL_RELEASE_DIR_BASE}")
    endif()
endif()

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
# Auto generate the CCIMX_ALL_RELEASE_DIR and base app dir
if(MSVC)
    message(STATUS "MSVC compiler detected, so build release in the msvc dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/msvc CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ${CCIMX_ALL_RELEASE_DIR})
elseif(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    message(STATUS "Cross compile detected, so build release in the arm dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/arm32 CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ".")
else()
    message(STATUS "GCC compiler detected, so build release in the x86 dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/x86 CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR "${CCIMX_ALL_RELEASE_DIR}")
endif()


message(STATUS "About to check the extern app: ")
add_compile_definitions(
    $<$<BOOL:${INCLUDE_WEATHER_APP}>:INCLUDE_WEATHER_APP>
    $<$<BOOL:${INCLUDE_PDF_BROWSER_APP}>:INCLUDE_PDF_BROWSER_APP>
    $<$<BOOL:${INCLUDE_CAMERA_APP}>:INCLUDE_CAMERA_APP>
    $<$<BOOL:${INCLUDE_FILERAMBER_APP}>:INCLUDE_FILERAMBER_APP>
    $<$<BOOL:${INCLUDE_SYSTEMSTATUS_APP}>:INCLUDE_SYSTEMSTATUS_APP>
)

add_subdirectory(extern_app)

include_directories(
    .
    ./ui
    ./builtin/ui
)

set(DesktopMain
    ui/desktopmainwindow.cpp
    ui/desktopmainwindow.h
    ui/desktopmainwindow.ui)

set(AppWrapper
    app_wrapper/applicationwrapper.h
    app_wrapper/applicationwrapper.cpp
    app_wrapper/pagesetuper.h app_wrapper/pagesetuper.cpp)

set(UiSubs
    ui/appwidget.h ui/appwidget.cpp ui/appwidget.ui
    ui/stackpage_switcher_animation.h
    ui/stackpage_switcher_animation.cpp
    ui/downdockwidget.h ui/downdockwidget.cpp
    ui/downdockwidget.ui
    ui/desktoptoast.h ui/desktoptoast.cpp
    ui/wallpaperanimationhandler.h ui/wallpaperanimationhandler.cpp)

set(CoreSubs
    core/coretools.h core/coretools.cpp)

set(BuiltInPackage
    builtin/page/homepage.h builtin/page/homepage.cpp builtin/page/homepage.ui
    builtin/ui/pagefactory.h builtin/ui/pagefactory.cpp
    builtin/ui/clockwidget.h builtin/ui/clockwidget.cpp builtin/ui/clockwidget.ui
    builtin/ui/digitaltimewidget.h builtin/ui/digitaltimewidget.cpp)

set(BONUS_APPCARD
    ui/appcardwidget.h ui/appcardwidget.cpp ui/appcardwidget.ui
    builtin/gadgets/netcardgadget.h builtin/gadgets/netcardgadget.cpp
    builtin/sources/netcard/netcards_src.qrc
    builtin/gadgets/localweathercard.h builtin/gadgets/localweathercard.cpp
)

set(BUILT_IN_ICM20608_Support
    builtin/core/icm20608/icm20608_adapter.h
    builtin/core/icm20608/icm20608_adapter.cpp
    builtin/core/icm20608/icm20608.h)


qt_add_executable(CCIMX_Desktop
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${DesktopMain}
    ${AppWrapper}
    ${UiSubs}
    ${CoreSubs}
    ${BuiltInPackage}
    ${BONUS_APPCARD}
    ${BUILT_IN_ICM20608_Support}
    icons.qrc
    builtin/sources/localweather/localweather.qrc
    desktop_settings.h
)

add_custom_command(TARGET CCIMX_Desktop POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CCIMX_Desktop> ${CCIMX_ALL_RELEASE_DIR}
)

target_link_libraries(CCIMX_Desktop
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Network
)

target_compile_definitions(
    CCIMX_Desktop PRIVATE
    _EXTERNAPP_INSTALL_DIR=\"${CCIMX_EXTERNAL_APP_BASE_DIR}\"
)

include(GNUInstallDirs)

install(TARGETS CCIMX_Desktop
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET CCIMX_Desktop
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

message(STATUS  "About to dump the message of the building in order to ensure the settings")
message(STATUS  "-----------------------------------------------------")
message(STATUS "Install Issue End: ")
message(STATUS "-----------------------------------------------------")
message(STATUS "The base dirent of installations:   CCIMX_ALL_RELEASE_DIR_BASE = ${CCIMX_ALL_RELEASE_DIR_BASE}")
message(STATUS "current kits installations:         CCIMX_ALL_RELEASE_DIR      = ${CCIMX_ALL_RELEASE_DIR}")
message(STATUS "Extern app install locations:       CCIMX_EXTERNAL_APP_BASE_DIR= ${CCIMX_EXTERNAL_APP_BASE_DIR}")
message(STATUS "-----------------------------------------------------")
message(STATUS "Dumping the external apps: ")
message(STATUS "Weather Application Built status Due to INCLUDE_WEATHER_APP: ${INCLUDE_WEATHER_APP}")
message(STATUS "PDF Browser Built status Due to INCLUDE_PDF_BROWSER_APP: ${INCLUDE_PDF_BROWSER_APP}")
message(STATUS "Camera Application Built status Due to INCLUDE_CAMERA_APP: ${INCLUDE_CAMERA_APP}")
message(STATUS "File Ramber Built status due to INCLUDE_FILERAMBER_APP: ${INCLUDE_FILERAMBER_APP}")
message(STATUS "System State Built due to INCLUDE_SYSTEMSTATUS_APP: ${INCLUDE_SYSTEMSTATUS_APP}")
message(STATUS "-----------------------------------------------------")





