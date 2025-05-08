cmake_minimum_required(VERSION 3.16)
project(examples LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

message(STATUS "Configuring the cvImage Example")
add_executable(CVImageExample cvImageExample.cpp)
target_include_directories(
    CVImageExample PRIVATE ..
)

target_compile_definitions(CVImageExample
  PRIVATE
        TEST_IMAGE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/image"
)

target_link_libraries(CVImageExample
    PRIVATE
        core_library
)

message(STATUS "Configuring the VideoPlayer Example")
add_executable(VideoPlayerOpenCVIMPLExample VideoExampleOpenCVIMPL.cpp)

target_include_directories(
    VideoPlayerOpenCVIMPLExample PRIVATE ..
)
target_compile_definitions(VideoPlayerOpenCVIMPLExample
  PRIVATE
        TEST_VIDEO_DIR="${CMAKE_CURRENT_SOURCE_DIR}/video"
)

target_link_libraries(VideoPlayerOpenCVIMPLExample
    PRIVATE
        core_library
        Qt::Core
)


include(GNUInstallDirs)
install(TARGETS CVImageExample
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS VideoPlayerOpenCVIMPLExample
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
