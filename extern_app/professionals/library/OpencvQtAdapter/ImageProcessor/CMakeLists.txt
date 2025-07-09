cmake_minimum_required(VERSION 3.16)

project(ImageProcessor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        ImageProcessorWindow.cpp
        ImageProcessorWindow.h
        ImageProcessorWindow.ui
        image_processing_example/blur_image/BlurExample.h
        image_processing_example/blur_image/BlurExample.cpp
        image_processing_example/blur_image/BlurExample.ui
        image_processing_example/canny_example/CannyExample.h
        image_processing_example/canny_example/CannyExample.cpp image_processing_example/canny_example/CannyExample.ui
        image_processing_example/contours_query/ContoursQueryExample.h
        image_processing_example/contours_query/ContoursQueryExample.cpp
        image_processing_example/contours_query/ContoursQueryExample.ui
        image_processing_example/hist_drawer/HistDrawer.h
        image_processing_example/hist_drawer/HistDrawer.cpp image_processing_example/hist_drawer/HistDrawer.ui
        image_processing_example/gray_image/GrayExample.h
        image_processing_example/gray_image/GrayExample.cpp image_processing_example/gray_image/GrayExample.ui
        image_processing_example/face_detection/FaceDetectionExample.h
        image_processing_example/face_detection/FaceDetectionExample.cpp
        image_processing_example/face_detection/FaceDetectionExample.ui
)

qt_add_executable(ImageProcessor
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    sources/sources_demo.qrc

)
target_include_directories(ImageProcessor
    PRIVATE ..
    ../ui_interface/tools_stacked_widget
    ../ui_interface/convinients)
target_link_libraries(ImageProcessor
  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
  core_library
  ui_interface)

add_custom_command(TARGET ImageProcessor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_EXTERNAL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ImageProcessor> ${CCIMX_EXTERNAL_APP_BASE_DIR}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ImageProcessor)
endif()
set_target_properties(ImageProcessor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ImageProcessor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ImageProcessor)
endif()
