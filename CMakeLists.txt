cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX VERSION 0.9.9)

message(STATUS "Importing cmake modules...")
set(CCDESKTOPABOUT_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${CCDESKTOPABOUT_CMAKE_DIR})
include(fast_logger)

message(STATUS "[CCIMXDesktop]: Dumping the message info...")
set(CCIMXDESKTOP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CCIMXDESKTOP_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CCIMXDESKTOP_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CCIMXDESKTOP_VERSION_FULL ${PROJECT_VERSION})
message(STATUS "[CCIMXDesktop]: You are building the CCIMXDestop with in the Version ${CCIMXDESKTOP_VERSION_FULL}")

set(CMAKE_AUTORCC ON)
set(LOCAL_DEF_FILE_NAME "CCIMXDesktopLocalDefaults")
set(TEMPLATE_FILE_NAME "CCIMXDesktopBuildConfigs")
include(app_building_options)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
qt_standard_project_setup()

if(DEFINED LOCAL_CONFIG_FILE AND EXISTS "${LOCAL_CONFIG_FILE}")
    message(STATUS "[CCIMXDesktop]: Using manually specified local config file: ${LOCAL_CONFIG_FILE}")
    include("${LOCAL_CONFIG_FILE}")
else()
    set(DEFAULT_LOCAL_CONFIG "${CMAKE_CURRENT_LIST_DIR}/${LOCAL_DEF_FILE_NAME}.cmake")
    if(EXISTS "${DEFAULT_LOCAL_CONFIG}")
        message(STATUS "[CCIMXDesktop]: Using default local config file: ${DEFAULT_LOCAL_CONFIG}")
        include("${DEFAULT_LOCAL_CONFIG}")
    else()
        message(FATAL_ERROR
            "No configuration file is provided or found,
            you are supposed to do followings:
            [1] Copy a template file in ${CMAKE_CURRENT_LIST_DIR}/configs/${TEMPLATE_FILE_NAME}.cmake.template
            [2] Rename it ${LOCAL_DEF_FILE_NAME}.cmake and place it in root path of the projects
            [or] you can pass with -DLOCAL_CONFIG_FILE=<config file>, but be careful the path should be exsited, else we will
                 still fallback to the searching in ${CMAKE_CURRENT_LIST_DIR}/${LOCAL_DEF_FILE_NAME}.cmake")
    endif()
endif()

# This part aims to find the Cross compile
# If you only get the arm mupdf compiles, do notice to select the
# correct kits with correct arch and compilers
include(install_helper)
ensure_base_release_dir()
include(third_party_validator)
# Global Check the dependencies
check_opencv_app()
check_mupdf_session()
check_cross_alsa_library()

message(STATUS "[CCIMXDesktop]: About to check the extern app: ")
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

# As the configuration cmake included, configure the template desktop_settings_sessions
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/configs/desktop_settings.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/desktop_settings.h)


message(STATUS "[CCIMXDesktop]: About to check the CCIMXDesktop Main Face Dependencies...")

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

set(WallPaperSrc
    core/wallpaper/WallPaperEngine.h core/wallpaper/WallPaperEngine.cpp
    core/wallpaper/WallPaperUtilsColliections.h core/wallpaper/WallPaperUtilsColliections.cpp
    sources/default_backgrounds/defaule_background_sources.qrc)

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

set(BuiltInWindow_SettingsSrc
    builtin/window/settings_window/SettingsWindow.h
    builtin/window/settings_window/SettingsWindow.cpp
    builtin/window/settings_window/SettingsWindow.ui
    builtin/window/settings_window/cores/ConfigureUiPairs.h
    builtin/window/settings_window/cores/ConfigureUiPairs.cpp
    builtin/window/settings_window/config_items/appwidgets_globalconfig/AppWidgetConfigures.h
    builtin/window/settings_window/config_items/appwidgets_globalconfig/AppWidgetConfigures.cpp
    builtin/window/settings_window/config_items/appwidgets_globalconfig/AppWidgetConfigures.ui)

qt_add_executable(CCIMX_Desktop
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${DesktopMain}
    ${AppWrapper}
    ${UiSubs}
    ${CoreSubs}
    ${WallPaperSrc}
    ${BuiltInPackage}
    ${BONUS_APPCARD}
    ${BuiltInWindow_SettingsSrc}
    ${BUILT_IN_ICM20608_Support}
    icons.qrc
    builtin/sources/localweather/localweather.qrc
    builtin/sources/other_icons.qrc
    builtin/window/settings_window/fake_app_entry/SettingsApp.h builtin/window/settings_window/fake_app_entry/SettingsApp.cpp
    builtin/window/settings_window/cores/SettingsPack.h
    builtin/core/backlight/BacklightController.h builtin/core/backlight/BacklightController.cpp
    builtin/core/backlight/BacklightControllerImpl.h builtin/core/backlight/BacklightControllerImpl.cpp
    builtin/window/settings_window/config_items/light_controller/LightConfigures.h builtin/window/settings_window/config_items/light_controller/LightConfigures.cpp builtin/window/settings_window/config_items/light_controller/LightConfigures.ui
    builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.h builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.cpp builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.ui
    builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.h builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.cpp builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.ui
    builtin/window/settings_window/config_items/wallpaper_settings/utils/ImageListViewWidget.h builtin/window/settings_window/config_items/wallpaper_settings/utils/ImageListViewWidget.cpp
    builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.h builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.cpp builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.ui

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
target_include_directories(CCIMX_Desktop
    PRIVATE
    .
    ./ui
    ./builtin/ui
    ${CMAKE_CURRENT_BINARY_DIR}/generated)

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
