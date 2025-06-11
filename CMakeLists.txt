# set the proxy with http https if you have direct trouble in visiting githubs
# set(ENV{http_proxy} "http://127.0.0.1:7890")
# set(ENV{https_proxy} "http://127.0.0.1:7890")
cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX VERSION 0.9.6)

message(STATUS "Importing cmake modules...")
set(CCDESKTOPABOUT_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${CCDESKTOPABOUT_CMAKE_DIR})
include(fast_logger)

message(STATUS "[CCIMXDesktop]: Dumping the message info...")
set(CCIMXDESKTOP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE STRING "Main Version Of CCIMXDesktop")
set(CCIMXDESKTOP_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE STRING "Sub Version Of CCIMXDesktop")
set(CCIMXDESKTOP_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE STRING "Patch Version Of CCIMXDesktop")
set(CCIMXDESKTOP_VERSION_FULL ${PROJECT_VERSION} CACHE STRING "Full Version Of CCIMXDesktop")
message(STATUS "[CCIMXDesktop]: You are building the CCIMXDestop with in the Version ${CCIMXDESKTOP_VERSION_FULL}")

set(CMAKE_AUTORCC ON)

# Documentation supports
option(CCIMX_DESKTOP_DOCGEN_REQ "Options for whether generate the document, Now Doxygen required" ON)

# Options for support
option(INCLUDE_WEATHER_APP "Build the Weather App" ON)
option(INCLUDE_PDF_BROWSER_APP "Build the PDF Browser App" ON)
option(INCLUDE_CAMERA_APP "Build the Camera App" ON)
option(INCLUDE_FILERAMBER_APP "Build the FileRamber App" ON)
option(INCLUDE_SYSTEMSTATUS_APP "Build the System Status App" ON)
option(INCLUDE_MEDIAPLAYER_APP "Build the MeidaPlayer App" ON)
option(INCLUDE_PROFESSIONAL_APP "Build the professional App Enabled" ON)
option(INCLUDE_NETHELPER_APP "Build the NetHelper Enable" ON)
option(INCLUDE_EASYNOTE_APP "Build the Markdown Editor" ON)
option(INCLUDE_GAME_APP "Build the Game Subpart" ON)
option(CCIMX_BUILD_TEST "Create the test cases and process build time test" OFF)
if(INCLUDE_PROFESSIONAL_APP)
    option(INCLUDE_OPENCV_QT_ADAPTER    "OpenCV Qt Convient Adapter"    ON)
    option(INCLUDE_LED_APP "Build the LEDController App" ON)
    option(INCLUDE_ENV_APP "Build the Environment App" ON)
    option(INCLUDE_SPORT_APP "Build the SportsHealth App" ON)
    add_compile_definitions(
        $<$<BOOL:${INCLUDE_LED_APP}>:INCLUDE_LED_APP>
        $<$<BOOL:${INCLUDE_ENV_APP}>:INCLUDE_ENV_APP>
        $<$<BOOL:${INCLUDE_SPORT_APP}>:INCLUDE_SPORT_APP>
    )
endif()

if(INCLUDE_GAME_APP)
    message(STATUS "[CCIMXDesktop]:  Games are performance required, with a bit long build")
    option(INCLUDE_DINO_GAME "Dinasour Game in Google Style!" ON)
    add_compile_definitions(
        $<$<BOOL:${INCLUDE_DINO_GAME}>:INCLUDE_DINO_GAME>
    )
endif()


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
qt_standard_project_setup()

# Options for the default use install
set(_DEF_RELEASE_BASE_MSVC_RELEASE  "D:/NewQtProjects/Release/")
set(_DEF_RELEASE_BASE_GCC_RELEASE   "/home/charliechen/imx6ull/qt683_project/CCDesktopRelease")

# Options for the MuPDF Path
set(MUPDF_INCLUDE_DIR "" CACHE PATH "MuPDF Include Directory")
set(MUPDF_LIB_DIR "" CACHE PATH "MuPDF Library Directory")

# Options for the Automatically generate documentations
set(CCIMX_DOXYGEN_DOCUMENT_BASE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Documentations/doxygen_styles CACHE PATH "Doxygen folders base")
set(CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile CACHE PATH "Doxygen template file path")

# This part aims to find the Cross compile
# If you only get the arm mupdf compiles, do notice to select the
# correct kits with correct arch and compilers
message(STATUS "[CCIMXDesktop]: Ready to select the install path for the cross compile")
# if the CCIMX_ALL_RELEASE_DIR_BASE is not defined, set it to a default value
if(NOT DEFINED CCIMX_ALL_RELEASE_DIR_BASE OR CCIMX_ALL_RELEASE_DIR_BASE STREQUAL "")
    message(STATUS "CCIMX_ALL_RELEASE_DIR_BASE is not defined, set to default value")
    if(MSVC)
        message(STATUS "[CCIMXDesktop]: MSVC compiler detected, assume you are in Windows")
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
        message(STATUS "[CCIMXDesktop]: Pass check of the default path: '${_default_release_base}'")
    endif()
    set(CCIMX_ALL_RELEASE_DIR_BASE "${_default_release_base}" CACHE PATH "Base release install path for deployment")
else()
    if(NOT IS_DIRECTORY "${CCIMX_ALL_RELEASE_DIR_BASE}")
        message(FATAL_ERROR
            "Specified CCIMX_ALL_RELEASE_DIR_BASE does not exist: ${CCIMX_ALL_RELEASE_DIR_BASE}")
    endif()
endif()

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
# Auto generate the CCIMX_ALL_RELEASE_DIR and base app dir
if(MSVC)
    message(STATUS "[CCIMXDesktop]: MSVC compiler detected, so build release in the msvc dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/msvc CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ${CCIMX_ALL_RELEASE_DIR})
elseif(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    message(STATUS "[CCIMXDesktop]: Cross compile detected, so build release in the arm dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/arm32 CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR ".")
    add_compile_definitions(ARM_BUILD)
else()
    message(STATUS "[CCIMXDesktop]: GCC compiler detected, so build release in the x86 dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/x86 CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR "${CCIMX_ALL_RELEASE_DIR}")
endif()
include(third_party_validator)
# Global Check the dependencies
# Try To figure out OpenCV
check_opencv_app()
# Check the MuPDF
#     set(MUPDF_INCLUDE_DIR "D:/stdcpp-library/mupdf")
#     # Fuck MSVC, The Debug Level disequal makes the linkage
#     # impossible, we have to make a seperate change
#     MSCV's
#     set(MUPDF_LIB_DIR "D:/stdcpp-library/mupdf/Debug")
#     set(MUPDF_LIB_DIR "D:/stdcpp-library/mupdf/Release")
#     GCC
#     set(MUPDF_INCLUDE_DIR /home/charliechen/imx6ull/mupdfdebug/include)
#     set(MUPDF_LIB_DIR /home/charliechen/imx6ull/mupdfdebug)
check_mupdf_session()

# Global Compile Specifications
if(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    if(INCLUDE_MEDIAPLAYER_APP)
        message(STATUS "[CCIMXDesktop]: Cross compile detected, For QMediaPlayer we need to link the backend")
        message(STATUS "[CCIMXDesktop]: If you are using a different backend, you need to specify belowing by yourself")
        set(ALSA_LIBRARY_PATH   "/home/charliechen/imx6ull/alsalib_res/lib")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath-link=${ALSA_LIBRARY_PATH}")
    endif()
endif()

message(STATUS "About to check the extern app: ")
add_compile_definitions(
    $<$<BOOL:${INCLUDE_WEATHER_APP}>:INCLUDE_WEATHER_APP>
    $<$<BOOL:${INCLUDE_PDF_BROWSER_APP}>:INCLUDE_PDF_BROWSER_APP>
    $<$<BOOL:${INCLUDE_CAMERA_APP}>:INCLUDE_CAMERA_APP>
    $<$<BOOL:${INCLUDE_FILERAMBER_APP}>:INCLUDE_FILERAMBER_APP>
    $<$<BOOL:${INCLUDE_SYSTEMSTATUS_APP}>:INCLUDE_SYSTEMSTATUS_APP>
    $<$<BOOL:${INCLUDE_MEDIAPLAYER_APP}>:INCLUDE_MEDIAPLAYER_APP>
    $<$<BOOL:${INCLUDE_NETHELPER_APP}>:INCLUDE_NETHELPER_APP>
    $<$<BOOL:${INCLUDE_EASYNOTE_APP}>:INCLUDE_EASYNOTE_APP>
)

add_subdirectory(builtin/app)
add_subdirectory(extern_app)

message(STATUS "[CCIMXDesktop]: About to check the CCIMXDesktop Main Face Dependencies...")
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

# About the Document generations sessions
check_doxygen_session()

# import the build status dumping function
include(final_dumping)
dumping_build()
