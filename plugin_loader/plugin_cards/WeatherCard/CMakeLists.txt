include(../../cmake/plugin_helper.cmake)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_qt_plugin_with_json(WeatherCard WeatherCard "1.0"
        SOURCES
        ./WeatherCard.h
        ./WeatherCard.cpp
        ./WeatherCard.ui
        ./WeatherRequestEngine.h
        ./WeatherRequestEngine.cpp
        ./WeatherData.h
        ./QueryCached.h
        ./QueryCached.cpp
        ./DesktopPluginWidgetBase.h
)

target_sources(WeatherCard
  PRIVATE
    sources.qrc
)

add_custom_command(TARGET WeatherCard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PLUGINWIDGET_PLUGIN_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:WeatherCard> ${PLUGINWIDGET_PLUGIN_RELEASE_DIR}
)


