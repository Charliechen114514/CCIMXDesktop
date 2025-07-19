set(PLUGINWIDGET_PLUGIN_RELEASE_DIR "${CCIMX_ALL_RELEASE_DIR}/Runtime/plugins")
message(STATUS
    "Widget Plugins will be set at installed in
    ${PLUGINWIDGET_PLUGIN_RELEASE_DIR}")

file(GLOB CHILD_CMAKELISTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} */CMakeLists.txt)
set(PLUGINWIDGET_BUILDTIME_DIR "")
foreach(sub_cmake ${CHILD_CMAKELISTS})
    get_filename_component(sub_dir ${sub_cmake} DIRECTORY)
    list(APPEND PLUGINWIDGET_BUILDTIME_DIR ${sub_dir})
endforeach()

foreach(sub_dir ${PLUGINWIDGET_BUILDTIME_DIR})
    message(STATUS "[CCIMXDesktop] Detected the Plugin Dirent: ${sub_dir}")
    add_subdirectory(${sub_dir})
endforeach()

set(PLUGINWIDGET_BUILDTIME_DIR "${PLUGINWIDGET_BUILDTIME_DIR}" PARENT_SCOPE)
set(PLUGINWIDGET_PLUGIN_RELEASE_DIR "${PLUGINWIDGET_PLUGIN_RELEASE_DIR}" PARENT_SCOPE)



