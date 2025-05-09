cmake_minimum_required(VERSION 3.16)

project(test_cvImage LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GOOGLE_TEST_URL https://github.com/google/googletest.git)
set(GOOGLE_TEST_TAG v1.17.0)
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY    ${GOOGLE_TEST_URL}
  GIT_TAG           ${GOOGLE_TEST_TAG}
)
set(gtest_build_tests OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED)

add_executable(
    test_cvImage main.cpp tst_test_cvimage.cpp
)

target_include_directories(
    test_cvImage PRIVATE ..
)

target_link_libraries(test_cvImage
    PRIVATE
    Threads::Threads
    gtest
    gtest_main
    core_library
)

target_compile_definitions(test_cvImage
  PRIVATE
    TEST_IMAGE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/testdata/image"
)

add_test(   NAME test_cvImage
            COMMAND test_cvImage)

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
if(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
  message(STATUS "Escape the test post invoke due to the cross compile case")
else()
add_custom_command(TARGET test_cvImage
                   POST_BUILD
                   COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
                   COMMENT "Running unit tests after build")
endif()
