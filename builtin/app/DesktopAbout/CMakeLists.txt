cmake_minimum_required(VERSION 3.16)

project(DesktopAbout VERSION 0.1 LANGUAGES CXX)
set(CCDESKTOPABOUT_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH ${CCDESKTOPABOUT_CMAKE_DIR})
include(version_utils)
include(fast_logger)

setup_version_if_not_defined(VAR_NAME CCIMXDESKTOP_VERSION_MAJOR DEFAULT_VALUE 1)
setup_version_if_not_defined(VAR_NAME CCIMXDESKTOP_VERSION_MINOR DEFAULT_VALUE 0)
setup_version_if_not_defined(VAR_NAME CCIMXDESKTOP_VERSION_PATCH DEFAULT_VALUE 0)
check_and_setup_full_version()
set(CCIMXDESKTOP_ABOUT "CCIMXDesktop, Designed for Embedded Devices!")
set(CCIMXDESKTOP_AUTHOR "Charliechen114514@<https://github.com/Charliechen114514/CCIMXDesktop>")
set(CCIMXDESKTOP_NAME "CCIMXDesktop")
fast_project_message("we will setup application for the desktop version: ${CCIMXDESKTOP_VERSION_FULL}")

file(COPY ${CMAKE_SOURCE_DIR}/README.md
     DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/sources/doc)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/template/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.h
)

fast_project_message("generating the version header for the project done!")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SRC_FILE sources/src.qrc)

set(PROJECT_SOURCES
        main.cpp
        ui/AboutMainWindow.cpp
        ui/AboutMainWindow.h
        ui/AboutMainWindow.ui
        ui/DesktopAboutMainWidget.h
        ui/DesktopAboutMainWidget.cpp
        ui/DesktopAboutMainWidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

qt_add_executable(DesktopAbout
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${SRC_FILE}
        ui/ReadMeWidget.h ui/ReadMeWidget.cpp ui/ReadMeWidget.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DesktopAbout APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DesktopAbout SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DesktopAbout
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DesktopAbout PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# includ the generating version files
target_include_directories(DesktopAbout PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/generated
    ./ui
)

add_custom_command(TARGET DesktopAbout POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:DesktopAbout> ${CCIMX_ALL_RELEASE_DIR}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DesktopAbout)
endif()
set_target_properties(DesktopAbout PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DesktopAbout
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DesktopAbout)
endif()
