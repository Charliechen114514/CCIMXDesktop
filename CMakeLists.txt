cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX VERSION 2.4.0)

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
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Core)
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
    $<$<BOOL:${INCLUDE_CCOMMUNICATOR_APP}>:INCLUDE_CCOMMUNICATOR_APP>
)

message(STATUS "----------------------------------------------------")
message(STATUS "[CCIMXDesktop]: About to scan the extern apps builds")
add_subdirectory(builtin/app)
message(STATUS "----------------------------------------------------")
message(STATUS "[CCIMXDesktop]: About to scan the extern apps builds")
add_subdirectory(extern_app)
message(STATUS "----------------------------------------------------")

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
    ui/DesktopMainWindowInitHelper.h
    ui/DesktopMainWindowInitHelper.cpp
    ui/fast_settings/FastSettingsWidget.h
    ui/fast_settings/FastSettingsWidget.cpp
    ui/fast_settings/FastSettingsWidget.ui
    ui/UiTools.h ui/UiTools.cpp
    ui/appwidget.h ui/appwidget.cpp ui/appwidget.ui
    ui/stackpage_switcher_animation.h
    ui/stackpage_switcher_animation.cpp
    ui/downdockwidget.h ui/downdockwidget.cpp
    ui/downdockwidget.ui
    ui/desktoptoast.h ui/desktoptoast.cpp
    ui/wallpaperanimationhandler.h ui/wallpaperanimationhandler.cpp
    ui/UiTools/font_info_formater/FontInfoFormarter.cpp
    ui/UiTools/font_info_formater/FontInfoFormarter.h
    ui/internal_calendar/ModernCalendarWidget.cpp
    ui/internal_calendar/ModernCalendarWidget.h
    ui/UiTools/easing_curve_combox_setupper/EasingCurveComboxBoxSetuper.h 
    ui/UiTools/easing_curve_combox_setupper/EasingCurveComboxBoxSetuper.cpp
    ui/gauge_widget/GaugeWidget.cpp
    ui/gauge_widget/GaugeWidget.h
    ui/inform_toast_label/InformToastLabel.h
    ui/inform_toast_label/InformToastLabel.cpp
    ui/inform_toast_label/InformToastLabel.ui

)

set(CoreSubs
    core/users/UserInfo.h
    core/users/UserInfo.cpp
    core/users/DesktopUserInfo.h
    core/users/DesktopUserInfo.cpp
    core/page_switching_limiter/PageSwitchingLimiter.h
    core/page_switching_limiter/PageSwitchingLimiter.cpp
    core/coretools.h core/coretools.cpp
    core/labelStyler/LabelStyler.h
    core/labelStyler/LabelStyler.cpp
    core/labelStyler/LabelStyleReader.h
    core/labelStyler/LabelStyleReader.cpp
    core/desktop_dirent_manager/DesktopDirentLocationManager.h
    core/desktop_dirent_manager/DesktopDirentLocationManager.cpp
    core/desktop_dirent_manager/DesktopDirentInfoSettings.h)

set(WallPaperSrc
    core/wallpaper/WallPaperEngine.h core/wallpaper/WallPaperEngine.cpp
    core/wallpaper/WallPaperUtilsColliections.h core/wallpaper/WallPaperUtilsColliections.cpp
    sources/default_backgrounds/defaule_background_sources.qrc)

set(BuiltInPackage
    builtin/page/home_card_manager/HomeCardManager.h
    builtin/page/home_card_manager/HomeCardManager.cpp
    builtin/page/homepage.h builtin/page/homepage.cpp builtin/page/homepage.ui
    builtin/ui/pagefactory.h builtin/ui/pagefactory.cpp
    builtin/ui/clockwidget.h builtin/ui/clockwidget.cpp builtin/ui/clockwidget.ui
    builtin/ui/digitaltimewidget.h builtin/ui/digitaltimewidget.cpp)

set(BONUS_APPCARD
    ui/appcardwidget.h ui/appcardwidget.cpp ui/appcardwidget.ui
    builtin/gadgets/netcardgadget.h builtin/gadgets/netcardgadget.cpp
    builtin/sources/netcard/netcards_src.qrc
    builtin/gadgets/localweathercard.h builtin/gadgets/localweathercard.cpp
    builtin/gadgets/larger_card/system_state/DiskUsageCardWidget.h
    builtin/gadgets/larger_card/system_state/DiskUsageCardWidget.cpp
    builtin/gadgets/larger_card/system_state/DiskUsageCardWidget.ui
    builtin/gadgets/larger_card/system_state/MemoryUsageCard.h
    builtin/gadgets/larger_card/system_state/MemoryUsageCard.cpp
    builtin/gadgets/larger_card/system_state/MemoryUsageCard.ui
)

set(BUILTIN_DRIVER_ADAPTER_SRC
    builtin/core/backlight/BackLightControllerSingleton.h
    builtin/core/backlight/BackLightControllerSingleton.cpp
    builtin/core/icm20608/icm20608_adapter.h
    builtin/core/icm20608/icm20608_adapter.cpp
    builtin/core/icm20608/icm20608.h)

set(BuiltInWindow_SettingsSrc
    builtin/window/settings_window/config_items/slide_settings/SlideSettings.h builtin/window/settings_window/config_items/slide_settings/SlideSettings.cpp builtin/window/settings_window/config_items/slide_settings/SlideSettings.ui
    builtin/window/settings_window/config_items/topsidebar/TopSideBarWidgetConfigures.h builtin/window/settings_window/config_items/topsidebar/TopSideBarWidgetConfigures.cpp builtin/window/settings_window/config_items/topsidebar/TopSideBarWidgetConfigures.ui
    builtin/window/settings_window/config_items/topsidebar/timesettings/TimeLabelSettings.h builtin/window/settings_window/config_items/topsidebar/timesettings/TimeLabelSettings.cpp builtin/window/settings_window/config_items/topsidebar/timesettings/TimeLabelSettings.ui
    builtin/ui/ColorSelectWidget.h builtin/ui/ColorSelectWidget.cpp builtin/ui/ColorSelectWidget.ui
    builtin/window/settings_window/SettingsWindow.h
    builtin/window/settings_window/SettingsWindow.cpp
    builtin/window/settings_window/SettingsWindow.ui
    builtin/window/settings_window/cores/ConfigureUiPairs.h
    builtin/window/settings_window/cores/ConfigureUiPairs.cpp
    builtin/window/settings_window/config_items/appwidgets_globalconfig/AppWidgetConfigures.h
    builtin/window/settings_window/config_items/appwidgets_globalconfig/AppWidgetConfigures.cpp
    builtin/window/settings_window/config_items/appwidgets_globalconfig/AppWidgetConfigures.ui
    builtin/window/settings_window/fake_app_entry/SettingsApp.h builtin/window/settings_window/fake_app_entry/SettingsApp.cpp
    builtin/window/settings_window/cores/SettingsPack.h
    builtin/core/backlight/BacklightController.h builtin/core/backlight/BacklightController.cpp
    builtin/core/backlight/BacklightControllerImpl.h builtin/core/backlight/BacklightControllerImpl.cpp
    builtin/window/settings_window/config_items/light_controller/LightConfigures.h builtin/window/settings_window/config_items/light_controller/LightConfigures.cpp builtin/window/settings_window/config_items/light_controller/LightConfigures.ui
    builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.h builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.cpp builtin/window/settings_window/config_items/wallpaper_settings/WallpaperConfigures.ui
    builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.h builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.cpp builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/FixedOptionWidget.ui
    builtin/window/settings_window/config_items/wallpaper_settings/utils/ImageListViewWidget.h builtin/window/settings_window/config_items/wallpaper_settings/utils/ImageListViewWidget.cpp
    builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.h builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.cpp builtin/window/settings_window/config_items/wallpaper_settings/option_widgets/SequenciedSettingsWidget.ui
    builtin/window/applauncher/ApplicationLauncherMainWindow.h builtin/window/applauncher/ApplicationLauncherMainWindow.cpp builtin/window/applauncher/ApplicationLauncherMainWindow.ui
    builtin/window/applauncher/fakeapps/AppLauncherApp.h builtin/window/applauncher/fakeapps/AppLauncherApp.cpp
)

set(UPPER_TOOLBAR_SRC
    ui/topstatusbar/battery/BatteryStatusbarIcon.h ui/topstatusbar/battery/BatteryStatusbarIcon.cpp
    ui/topstatusbar/TopSideBarWidget.h ui/topstatusbar/TopSideBarWidget.cpp ui/topstatusbar/TopSideBarWidget.ui
    ui/topstatusbar/StatusBarIconWidget.h ui/topstatusbar/StatusBarIconWidget.cpp
    ui/topstatusbar/StaticStatusBarIconWidget.h ui/topstatusbar/StaticStatusBarIconWidget.cpp ui/topstatusbar/StaticStatusBarIconWidget.ui
    ui/topstatusbar/netstat/NetStatusStatusBarIconWidget.h ui/topstatusbar/netstat/NetStatusStatusBarIconWidget.cpp
    ui/topstatusbar/DefaultLabelName.h
    ui/topstatusbar/netstat/NetStatusChangedEvent.h
    builtin/core/netability_scanner/NetAbilityScanner.h builtin/core/netability_scanner/NetAbilityScanner.cpp
    builtin/core/netability_scanner/NetAbilityScanEnum.h
    builtin/core/global_clock_src/GlobalClockSources.h builtin/core/global_clock_src/GlobalClockSources.cpp
    ui/topstatusbar/time_display/TimeDisplayIconWidget.h ui/topstatusbar/time_display/TimeDisplayIconWidget.cpp ui/topstatusbar/time_display/TimeDisplayIconWidget.ui
)

set(ICONQRC_SRC
    builtin/sources/localweather/localweather.qrc
    builtin/sources/other_icons.qrc
    ui/topstatusbar/topstatusbar_icons.qrc
    ui/splash_window/splash_src.qrc
    icons.qrc)

set(START_STAGE_SRC
    ui/splash_window/CCIMX_DesktopSplashWindow.h
    ui/splash_window/CCIMX_DesktopSplashWindow.cpp)

set(LIBRARY_SRC
    library/limited_value/ValueLimiter.hpp
    library/simple_gerseter/simple_getseter.hpp
    library/qt_relative/genbound_progressbar/BoundProgressBarFactory.hpp
    library/random_gen_value/random_gen_value.h
    library/platforms/DiskUsage.h
    library/platforms/DiskUsage.cpp
    library/platforms/MemoryStateQuery.cpp
    library/platforms/MemoryStateQuery.h
    library/fileio/FileIOUtils.h
    library/fileio/FileIOUtils.cpp
    library/FileDefs.h
    library/qt_relative/mouse_press_manager/MouseManager.h library/qt_relative/mouse_press_manager/MouseManager.cpp
    library/qt_relative/mouse_press_manager/MouseProcessor.h library/qt_relative/mouse_press_manager/MouseProcessor.cpp
    library/qt_relative/mouse_press_manager/MouseRecorder.h
    library/qt_relative/auto_step_init/AutoStepIniter.h library/qt_relative/auto_step_init/AutoStepIniter.cpp
    library/qt_relative/auto_step_init/AutoStepInitTask.h library/qt_relative/auto_step_init/AutoStepInitTask.cpp
    library/qt_relative/fileio/QtFileIO.h
    library/qt_relative/fileio/QtFileIO.cpp
    library/qt_relative/file_monitor/FileMonitor.h
    library/qt_relative/file_monitor/FileMonitor.cpp
    )

set(Loggy_SRC
    core/loggers/CCIMXDesktopLoggerCenter.h core/loggers/CCIMXDesktopLoggerCenter.cpp
    core/loggers/DesktopLoggerBackends.h core/loggers/DesktopLoggerBackends.cpp
    core/loggers/ConsoleLogger.h core/loggers/ConsoleLogger.cpp
    core/loggers/decorator/console_color/ConsoleColorDecorator.h core/loggers/decorator/console_color/ConsoleColorDecorator.cpp
    core/loggers/base_components/message_comsumer/ConsoleConsumer.h core/loggers/base_components/message_comsumer/ConsoleConsumer.cpp
    core/loggers/base_components/message_comsumer/LoggerBaseConsumer.h
    core/loggers/base_components/format_factory/FormativeFactory.h
    core/loggers/base_components/format_factory/plain_format/PlainFormarter.h core/loggers/base_components/format_factory/plain_format/PlainFormarter.cpp
    core/loggers/base_components/format_factory/standard_format/StandardFormater.h core/loggers/base_components/format_factory/standard_format/StandardFormater.cpp
    core/loggers/DesktopLoggerConvinients.h core/loggers/DesktopLoggerConvinients.cpp
    )

set(CardsSrc
    ui/card_stack/CardStackWidget.h ui/card_stack/CardStackWidget.cpp
    builtin/gadgets/larger_card/DateShowCard.h
    builtin/gadgets/larger_card/DateShowCard.cpp
    builtin/gadgets/larger_card/UserInfoCard.h
    builtin/gadgets/larger_card/UserInfoCard.cpp
    )

set(InternalServer
    core/server/toast_file_gen_and_receiver/ToastGenerator.h core/server/toast_file_gen_and_receiver/ToastGenerator.cpp
    core/server/toast_file_gen_and_receiver/ToastMetaProtocol.h
    core/server/toast_file_gen_and_receiver/ToastReceiver.h core/server/toast_file_gen_and_receiver/ToastReceiver.cpp
    core/server/toast_file_gen_and_receiver/ToastMetaProtocol.cpp
    core/server/toast_file_gen_and_receiver/ToastProxy.h core/server/toast_file_gen_and_receiver/ToastProxy.cpp
    core/server/toast_file_gen_and_receiver/ToastPostServer.h core/server/toast_file_gen_and_receiver/ToastPostServer.cpp
    core/server/DesktopServerBase.h
    core/server/plugin_server/DesktopPluginServer.h
    core/server/plugin_server/DesktopPluginServer.cpp
    core/server/server_hooks/DesktopCardHook.h
    core/server/server_hooks/DesktopCardHook.cpp
    core/server/DesktopServerHookBase.h
    core/server/plugin_server/PluginValidator.h
    core/server/plugin_server/PluginValidator.cpp
    core/server/timer_server/timerservermonitoring.h core/server/timer_server/timerservermonitoring.cpp
    core/server/timer_server/TimeServerType.h
    core/server/timer_server/timerhandleserver.h core/server/timer_server/timerhandleserver.cpp
    core/server/timer_server/screen_server/screendetectorserver.h core/server/timer_server/screen_server/screendetectorserver.cpp)

set(PluginAbstractSrc
    plugin_loader/plugin_base/DesktopPluginWidgetBase.h)

add_subdirectory(plugin_loader)

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
    ${BUILTIN_DRIVER_ADAPTER_SRC}
    ${UPPER_TOOLBAR_SRC}
    ${ICONQRC_SRC}
    ${START_STAGE_SRC}
    ${LIBRARY_SRC}
    ${Loggy_SRC}
    ${CardsSrc}
    ${InternalServer}
    ${PluginAbstractSrc}
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
target_link_libraries(CCIMX_Desktop PRIVATE Qt6::Core)
target_include_directories(CCIMX_Desktop
    PRIVATE
    .
    ui
    builtin/ui
    ui/topstatusbar
    ui/internal_calendar
    ui/card_stack
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
