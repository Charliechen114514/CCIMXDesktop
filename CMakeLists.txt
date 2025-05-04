cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)

# This part aims to find the Cross compile
# If you only get the arm mupdf compiles, do notice to select the
# correct kits with correct arch and compilers

if(MSVC)
    set(CCIMX_ALL_RELEASE_DIR_BASE "D:/NewQtProjects/Release/")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/msvc/ CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ${CCIMX_ALL_RELEASE_DIR})
elseif(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    add_compile_definitions(ARM_BUILD)
    set(CCIMX_ALL_RELEASE_DIR_BASE "/home/charliechen/imx6ull/qt683_project/CCDesktopRelease")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/arm32/ CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ".")
else()
    set(CCIMX_ALL_RELEASE_DIR_BASE "/home/charliechen/imx6ull/qt683_project/CCDesktopRelease")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/x86/ CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ${CCIMX_ALL_RELEASE_DIR})
endif()

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

message(STATUS
        "Ready to build the Weather APP due to the INCLUDE_WEATHER_APP")
add_subdirectory(extern_app/WeatherApp)

message(STATUS
        "Ready to build the PDF Browser due to the INCLUDE_PDF_BROWSER_APP")
add_subdirectory(extern_app/pdfReader)

message(STATUS
        "Ready to build the Camera App due to the INCLUDE_CAMERA_APP")
add_subdirectory(extern_app/GeneralLocalCamera)

message(STATUS
        "Ready to build the FileRamber due to the INCLUDE_FILERAMBER_APP")
add_subdirectory(extern_app/FileRamber)
