cmake_minimum_required(VERSION 3.19)
project(pdfReader LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# Auto RCC for the automatic compile of qrc
set(CMAKE_AUTORCC   ON)
qt_standard_project_setup()

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)

# This part aims to find the Cross compile
# If you only get the arm mupdf compiles, do notice to select the
# correct kits with correct arch and compilers

if(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    message(STATUS "Detected cross compiler: ${COMPILER_NAME}")
    set(MUPDF_INCLUDE_DIR /home/charliechen/imx6ull/mupdf_res/include)
    set(MUPDF_LIB_DIR /home/charliechen/imx6ull/mupdf_res)
    # Bonus Compile Supports
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mfpu=neon -mfloat-abi=hard")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mfpu=neon -mfloat-abi=hard")
elseif(MSVC)
    set(MUPDF_INCLUDE_DIR "D:/stdcpp-library/mupdf")
    # Fuck MSVC, The Debug Level disequal makes the linkage
    # impossible, we have to make a seperate change
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(MUPDF_LIB_DIR "D:/stdcpp-library/mupdf/Debug")
    else()
        set(MUPDF_LIB_DIR "D:/stdcpp-library/mupdf/Release")
    endif()
else()
    message(STATUS "Detected desktop compiler: ${COMPILER_NAME}")
    set(MUPDF_INCLUDE_DIR /home/charliechen/imx6ull/mupdfdebug/include)
    set(MUPDF_LIB_DIR /home/charliechen/imx6ull/mupdfdebug)
endif()


message(STATUS "Now install the mupdf settings!")
message(STATUS "The include dirent is: ${MUPDF_INCLUDE_DIR}")
include_directories(
    ${MUPDF_INCLUDE_DIR}
    .
    ./ui
    ./mupdf_adapter
    ./ui_tools
)

message(STATUS "The library dirent is: ${MUPDF_LIB_DIR}")


add_library(mupdf STATIC IMPORTED)
if(MSVC)
    set_target_properties(mupdf PROPERTIES
        IMPORTED_LOCATION ${MUPDF_LIB_DIR}/libmupdf.lib
    )
else()
    set_target_properties(mupdf PROPERTIES
        IMPORTED_LOCATION ${MUPDF_LIB_DIR}/libmupdf.a
)
endif()

add_library(mupdf-third STATIC IMPORTED)
if(MSVC)
    set_target_properties(mupdf-third PROPERTIES
        IMPORTED_LOCATION ${MUPDF_LIB_DIR}/libthirdparty.lib
    )
else()
    set_target_properties(mupdf-third PROPERTIES
        IMPORTED_LOCATION ${MUPDF_LIB_DIR}/mupdf-third.a
)
endif()

# Library Collections
if(MSVC)
    set(LIBRARY_COLLECTIONS mupdf mupdf-third)
else()
    set(LIBRARY_COLLECTIONS         mupdf
                                    mupdf-third
                                    m)
endif()


set(MainEntry
        main.cpp)
set(MainDisplayWindow
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        ui/ccpdfscrollarea.h 
        ui/ccpdfscrollarea.cpp)

set(MetaWindowModule
    ui/metainfowindow.h
    ui/metainfowindow.cpp
    ui/metainfowindow.ui)

set(MuPdfAdapter
    mupdf_adapter/ccpdfdocument.h mupdf_adapter/ccpdfdocument.cpp
    mupdf_adapter/ccpdfviewer.h mupdf_adapter/ccpdfviewer.cpp
    mupdf_adapter/ccpdfviewer.ui)

set(MuPdfTools
    	mupdf_tools/mupdf_tools.h mupdf_tools/mupdf_tools.cpp
	mupdf_tools/ccpdfnavigationpolicy.h mupdf_tools/ccpdfnavigationpolicy.cpp
    	mupdf_tools/ccpdfzoommanagepolicy.h mupdf_tools/ccpdfzoommanagepolicy.cpp)

set(UiTools
	ui_tools/uipagenavigationpolicy.h ui_tools/uipagenavigationpolicy.cpp
    	ui_tools/SideBarWidget.ui ui_tools/SideBarWidget.h ui_tools/SideBarWidget.cpp
    	ui_tools/toolssidebar.h ui_tools/toolssidebar.cpp ui_tools/toolssidebar.ui)

qt_add_executable(pdfReader
    WIN32 MACOSX_BUNDLE
    ${MainEntry}
    ${MainDisplayWindow}
    ${MuPdfAdapter}
    ${MuPdfTools}
    ${MetaWindowModule}
    ${UiTools}
    icons.qrc
    mupdf_adapter/ccpdfchaptercreator.h mupdf_adapter/ccpdfchaptercreator.cpp
)

add_custom_command(TARGET pdfReader POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pdfReader> ${CCIMX_ALL_RELEASE_DIR}
)

target_link_libraries(pdfReader
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${LIBRARY_COLLECTIONS}
)

include(GNUInstallDirs)

install(TARGETS pdfReader
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET pdfReader
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
