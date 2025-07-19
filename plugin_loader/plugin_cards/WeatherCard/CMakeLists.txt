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



