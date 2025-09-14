cmake_minimum_required(VERSION 3.16)

project(AlarmyClock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(BuiltIns    builtin/ui/clockwidget.cpp
                builtin/ui/clockwidget.h
                builtin/ui/clockwidget.ui
                builtin/ui/SideBarWidget.cpp
                builtin/ui/SideBarWidget.h
                builtin/ui/SideBarWidget.ui)

set(UiSrc   ui/clockwindow.cpp
            ui/clockwindow.h
            ui/clockwindow.ui
            ui/toolsbar.h
            ui/toolsbar.cpp
            ui/toolsbar.ui
            ui/edittimewidget.h ui/edittimewidget.cpp
            ui/timercreatorwindow.h ui/timercreatorwindow.cpp)

set(CoreSrc core/globaltimersrc.h
            core/globaltimersrc.cpp
            core/alarmynotifier.h core/alarmynotifier.cpp
            core/alarmynote.h core/alarmynote.cpp
            core/clockeventbroadcaster.h core/clockeventbroadcaster.cpp
            core/clockeventprocessor.h core/clockeventprocessor.cpp)

set(PROJECT_SOURCES
        main.cpp
        ${BuiltIns}
        ${UiSrc}
        ${CoreSrc}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Core)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    find_package(Qt6 REQUIRED COMPONENTS Core)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    find_package(Qt6 REQUIRED COMPONENTS Core)
    qt_add_executable(AlarmyClock
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AlarmyClock APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AlarmyClock SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AlarmyClock
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AlarmyClock PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(AlarmyClock PRIVATE Qt6::Core)
target_link_libraries(AlarmyClock PRIVATE Qt6::Widgets)
target_link_libraries(AlarmyClock PRIVATE Qt6::Core)
target_link_libraries(AlarmyClock PRIVATE Qt6::Widgets)
target_link_libraries(AlarmyClock PRIVATE Qt6::Core)
target_include_directories(AlarmyClock PRIVATE builtin/ui ui core)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AlarmyClock)
endif()
set_target_properties(AlarmyClock PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AlarmyClock
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AlarmyClock)
endif()

add_custom_command(TARGET AlarmyClock POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:AlarmyClock> ${CCIMX_INSTALL_APP_BASE_DIR}
)
