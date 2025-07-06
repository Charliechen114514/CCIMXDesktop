cmake_minimum_required(VERSION 3.16)

project(ui_interface VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Gui)

set(PROJECT_SOURCES
    params_sliderbar/FloatSlideBar.h
    params_sliderbar/FloatSlideBar.cpp
    tool_left_widgets/ToolLeftWidgets.h
    tool_left_widgets/ToolLeftWidgets.cpp
    tools/SimpleTools.h tools/SimpleTools.cpp
    tools_stacked_widget/ToolsStackedWidget.h tools_stacked_widget/ToolsStackedWidget.cpp tools_stacked_widget/ToolsStackedWidget.ui
    convinients/ImageProcessingWidget.h convinients/ImageProcessingWidget.cpp convinients/ImageProcessingWidget.ui
    convinients/ImageResultDisplayer.h convinients/ImageResultDisplayer.cpp convinients/ImageResultDisplayer.ui
    convinients/ImageLabel.cpp convinients/ImageLabel.h
    ui_sources.qrc
)

add_library(ui_interface
    ${PROJECT_SOURCES}
)

target_include_directories(ui_interface PRIVATE
  . ./tool_left_widgets ./convinients)
target_link_libraries(ui_interface PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Gui
  core_library)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ui_interface)
endif()
set_target_properties(ui_interface PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ui_interface
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ui_interface)
endif()
