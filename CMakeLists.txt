# set the proxy with http https if you have direct trouble in visiting githubs
# set(ENV{http_proxy} "http://127.0.0.1:7890")
# set(ENV{https_proxy} "http://127.0.0.1:7890")

cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX VERSION 0.9.3)
message(STATUS "Dumping the message info...")
set(CCIMXDESKTOP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE STRING "Main Version Of CCIMXDesktop")
set(CCIMXDESKTOP_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE STRING "Sub Version Of CCIMXDesktop")
set(CCIMXDESKTOP_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE STRING "Patch Version Of CCIMXDesktop")
set(CCIMXDESKTOP_VERSION_FULL ${PROJECT_VERSION} CACHE STRING "Full Version Of CCIMXDesktop")
message(STATUS "You are building the CCIMXDestop with in the Version ${CCIMXDESKTOP_VERSION_FULL}")

set(CMAKE_AUTORCC ON)

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
    message(STATUS "[Warning in Information Level] Games are performance required, with a bit long build")
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

option(CCIMX_DESKTOP_DOCGEN_REQ "Options for whether generate the document, Now Doxygen required" ON)
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

    set(CCIMX_ALL_RELEASE_DIR_BASE "${_default_release_base}" CACHE PATH "Base release install path for deployment")
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
    add_compile_definitions(ARM_BUILD)
else()
    message(STATUS "GCC compiler detected, so build release in the x86 dirent")
    set(CCIMX_ALL_RELEASE_DIR ${CCIMX_ALL_RELEASE_DIR_BASE}/x86 CACHE PATH "Deploy the install root directory")
    set(CCIMX_EXTERNAL_APP_BASE_DIR "${CCIMX_ALL_RELEASE_DIR}")
endif()

# Global Check the dependencies
# Try To figure out OpenCV
message(STATUS  "About to Check the OpenCV Due to the Required of the MediaPlayer And professional apps")
find_package(OpenCV)
if(OpenCV_FOUND)
    message("OpenCV is found, accept the compile of the MediaPlayer and so on related")
    set(INCLUDE_MEDIAPLAYER_APP ON)
    set(INCLUDE_CAMERA_APP ON)
else()
    message("OpenCV is not found, If you install the opencv in a non-standard path, please specify the OpenCV_DIR")
    set(INCLUDE_MEDIAPLAYER_APP OFF)
    set(INCLUDE_CAMERA_APP OFF)
endif()

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
function(validate_path var_name out_result)
    set(is_valid FALSE)
    if(DEFINED ${var_name} AND NOT "${${var_name}}" STREQUAL "")
        if(EXISTS "${${var_name}}" AND IS_DIRECTORY "${${var_name}}")
            set(is_valid TRUE)
        endif()
    endif()
    set(${out_result} ${is_valid} PARENT_SCOPE)
endfunction()

function(MuPDF_MSVC_Build_Tips)
    message(STATUS "Hey, Here is a tips: ")
    message(STATUS  "MSVC's library is Debug level required, so"
                    "if you are using a debug build, you must specify to the debug library, else link failed :|")
endfunction()

message(STATUS "About to check the MuPDF paths, dumping for the user first!")
message(STATUS "The MuPDF include dirent is: ${MUPDF_INCLUDE_DIR}")
message(STATUS "The MuPDF library dirent is: ${MUPDF_LIB_DIR}")
validate_path(MUPDF_INCLUDE_DIR MUPDF_INCLUDE_VALID)
validate_path(MUPDF_LIB_DIR MUPDF_LIB_VALID)

if(MUPDF_INCLUDE_VALID AND MUPDF_LIB_VALID)
    message(STATUS "MuPDF is specified, and also are valid.")
    set(INCLUDE_PDF_BROWSER_APP ON)
    if(MSVC)
        MuPDF_MSVC_Build_Tips()
    endif()
else()
    message(WARNING "MuPDF paths are invalid. Skipping build PDF Browser.")
    message(WARNING "You need to specify the MuPDF_INCLUDE_DIR and MUPDF_LIB_DIR in the CMake GUI")
    set(INCLUDE_PDF_BROWSER_APP OFF)
endif()



# Global Compile Specifications
if(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    if(INCLUDE_MEDIAPLAYER_APP)
        message(STATUS "Cross compile detected, For QMediaPlayer we need to link the backend")
        message(STATUS "If you are using a different backend, you need to specify belowing by yourself")
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

message(STATUS "About to check the CCIMXDesktop Main Face Dependencies...")
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

if(CCIMX_DESKTOP_DOCGEN_REQ)
    find_package(Doxygen)

    if(DOXYGEN_FOUND)
        if(NOT DEFINED CCIMX_DOXYGEN_DOCUMENT_BASE_PATH)
            message(FATAL_ERROR "CCIMX_DOXYGEN_DOCUMENT_BASE_PATH is not defined")
        endif()
        if(NOT DEFINED CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE)
            message(FATAL_ERROR "CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE is not defined")
        endif()

        if(NOT EXISTS ${CCIMX_DOXYGEN_DOCUMENT_BASE_PATH})
            message(FATAL_ERROR "CCIMX_DOXYGEN_DOCUMENT_BASE_PATH path does not exist: ${CCIMX_DOXYGEN_DOCUMENT_BASE_PATH}")
        endif()
        if(NOT EXISTS ${CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE})
            message(FATAL_ERROR "CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE file does not exist: ${CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE}")
        endif()

        set(DOXYGEN_IN ${CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE})
        set(DOXYGEN_OUT ${CCIMX_DOXYGEN_DOCUMENT_BASE_PATH})

        add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message(WARNING "Doxygen not found, documentation target will not be available")
    endif()
else()
    message(STATUS "We do not need to generate the documentations, "
        "as the CCIMX_DESKTOP_DOCGEN_REQ is ${CCIMX_DESKTOP_DOCGEN_REQ}")
endif()


message(STATUS  "About to dump the message of the building in order to ensure the settings")
message(STATUS  "-----------------------------------------------------")
message(STATUS  "CCIMXDestop Version: ${CCIMXDESKTOP_VERSION_FULL}")
message(STATUS  "CCIMXDestop Main Version: ${CCIMXDESKTOP_VERSION_MAJOR}")
message(STATUS  "CCIMXDestop Sub Version: ${CCIMXDESKTOP_VERSION_MINOR}")
message(STATUS  "CCIMXDestop Patch Version: ${CCIMXDESKTOP_VERSION_PATCH}")
message(STATUS  "-----------------------------------------------------")
message(STATUS "Install Issue End: ")
message(STATUS "-----------------------------------------------------")
message(STATUS "The base dirent of installations:   CCIMX_ALL_RELEASE_DIR_BASE = ${CCIMX_ALL_RELEASE_DIR_BASE}")
message(STATUS "Current kits installations:         CCIMX_ALL_RELEASE_DIR      = ${CCIMX_ALL_RELEASE_DIR}")
message(STATUS "Extern app install locations:       CCIMX_EXTERNAL_APP_BASE_DIR= ${CCIMX_EXTERNAL_APP_BASE_DIR}")
message(STATUS "-----------------------------------------------------")
message(STATUS "Dumping the built in apps")
message(STATUS "About Application: introducing the desktop with support")
message(STATUS "About SimpleDrawer: Simple and Free drawer to notify your imaginations")
message(STATUS "About CCIMXNoter: Must Basic Notypad in CCIMXDesktop utilities")
message(STATUS "About ImageWalker: Simple and Free Image Browsing App, which is really easy lol")
message(STATUS "-----------------------------------------------------")
message(STATUS "Dumping the external apps: ")
message(STATUS "Weather Application Built status Due to INCLUDE_WEATHER_APP:    ${INCLUDE_WEATHER_APP}")
message(STATUS "PDF Browser Built status Due to INCLUDE_PDF_BROWSER_APP:        ${INCLUDE_PDF_BROWSER_APP}")
message(STATUS "Camera Application Built status Due to INCLUDE_CAMERA_APP:      ${INCLUDE_CAMERA_APP}")
message(STATUS "File Ramber Built status due to INCLUDE_FILERAMBER_APP:         ${INCLUDE_FILERAMBER_APP}")
message(STATUS "System State Built due to INCLUDE_SYSTEMSTATUS_APP:             ${INCLUDE_SYSTEMSTATUS_APP}")
message(STATUS "Media Player Built due to INCLUDE_MEDIAPLAYER_APP:              ${INCLUDE_MEDIAPLAYER_APP}")
message(STATUS "Professional App Built status due to INCLUDE_PROFESSIONAL_APP:  ${INCLUDE_PROFESSIONAL_APP}")
message(STATUS "LED Controller Built status due to INCLUDE_LED_APP:             ${INCLUDE_LED_APP}")
message(STATUS "Environment Built status due to INCLUDE_ENV_APP:                ${INCLUDE_ENV_APP}")
message(STATUS "Sports Health Built status due to INCLUDE_SPORT_APP:            ${INCLUDE_SPORT_APP}")
message(STATUS "OpenCV Adapters Built status due to INCLUDE_OPENCV_QT_ADAPTER:  ${INCLUDE_OPENCV_QT_ADAPTER}")
message(STATUS "Net Helper App Built status due to INCLUDE_NETHELPER_APP:       ${INCLUDE_NETHELPER_APP}")
message(STATUS "EasyNote Built due to INCLUDE_EASYNOTE_APP:                     ${INCLUDE_EASYNOTE_APP}")
message(STATUS "-----------------------------------------------------")
message(STATUS "Dumping the game apps: ")
message(STATUS "CCIMX_DinoGame Built status due to INCLUDE_DINO_GAME:           ${INCLUDE_DINO_GAME}")
message(STATUS "-----------------------------------------------------")
message(STATUS "Dumping Documentations summon issues: ")
message(STATUS "Doxygen Documentations Built status due to CCIMX_DESKTOP_DOCGEN_REQ: ${CCIMX_DESKTOP_DOCGEN_REQ}")
if(CCIMX_DESKTOP_DOCGEN_REQ)
    message(STATUS "Doxygen Documentations Template: ${CCIMX_DOXYGEN_DOCUNENT_DOXYFILE_TEMPLATE}")
    message(STATUS "Doxygen Documentations Base Dirent: ${CCIMX_DOXYGEN_DOCUMENT_BASE_PATH}")
    message(STATUS "Doxygen Documentations Output Dirent: ${DOXYGEN_OUT}")
    message(STATUS "To Summon the Documentations, you need to run cmake --build . --target doc in your build dirent to process your local documentation build!")
else()
    message(STATUS "If you need to generate the documentations, please set the CCIMX_DESKTOP_DOCGEN_REQ to ON")
endif()
message(STATUS "-----------------------------------------------------")

