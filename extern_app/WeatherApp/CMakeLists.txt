cmake_minimum_required(VERSION 3.19)
project(WeatherApp LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS
            Core Widgets Network Charts)

qt_standard_project_setup()

include_directories(
    . ./MainWindow ./Core ./Ui)

set(MainWindow
    MainWindow/WeatherAppMainWindow.cpp
    MainWindow/WeatherAppMainWindow.h
    MainWindow/WeatherAppMainWindow.ui)

set(AppCore
    Core/MyWeatherRequest.h  Core/MyWeatherRequest.cpp
    Core/AppWeatherRequest.h Core/AppWeatherRequest.cpp)

set(AuxyUi
    Ui/DesktopToast.h Ui/DesktopToast.cpp
    Ui/WeatherChartWidget.h Ui/WeatherChartWidget.cpp Ui/WeatherChartWidget.ui
    Ui/StackPageSwitcher.h Ui/StackPageSwitcher.cpp
    Ui/WeatherDailyCard.h Ui/WeatherDailyCard.cpp Ui/WeatherDailyCard.ui)

set(IconSrc sources/icons.qrc)

qt_add_executable(WeatherApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${MainWindow}
    ${AppCore}
    ${AuxyUi}
    ${IconSrc}
)

add_custom_command(TARGET WeatherApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_EXTERNAL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:WeatherApp> ${CCIMX_EXTERNAL_APP_BASE_DIR}
)


target_link_libraries(WeatherApp
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Network
        Qt6::Charts
)

include(GNUInstallDirs)

install(TARGETS WeatherApp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET WeatherApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# This is a demo key, for u, u should submit the result
target_compile_definitions(
    WeatherApp PRIVATE
    _DEF_WEATHER_PRIVATE_KEY=\"SfRRwRAYLfFfTKQoi\")

target_compile_definitions(
    WeatherApp PRIVATE
    _DEF_WEATHER_URL=\"http://api.seniverse.com/v3/weather/daily.json\"
)
