cmake_minimum_required(VERSION 3.19)
project(OpencvQtAdapter LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
message(STATUS "Recheck the OpenCV_DIR for package finding: ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)

qt_standard_project_setup()

# Build the core library first
add_subdirectory(core_library)
add_subdirectory(core_library_test)

add_subdirectory(examples)
add_subdirectory(gui_example)
