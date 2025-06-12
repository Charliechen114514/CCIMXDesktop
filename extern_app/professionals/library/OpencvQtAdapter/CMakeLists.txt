cmake_minimum_required(VERSION 3.19)
project(OpencvQtAdapter LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
message(STATUS "Recheck the OpenCV_DIR for package finding: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

qt_standard_project_setup()

# Build the core library first
add_subdirectory(core_library)
add_subdirectory(ui_interface)
if(CCIMX_BUILD_TEST)
    add_subdirectory(core_library_test)
endif()
add_subdirectory(examples)
add_subdirectory(gui_example)
add_subdirectory(ui_interface_example)
if(INCLUDE_IMAGE_PROCESSOR)
    add_subdirectory(ImageProcessor)
endif()
