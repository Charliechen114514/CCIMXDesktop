message(STATUS "Start Plugin System Management!")
include(cmake/plugin_helper.cmake)

add_subdirectory(plugin_cards)
set(PLUGINWIDGET_BUILDTIME_DIR "${PLUGINWIDGET_BUILDTIME_DIR}" PARENT_SCOPE)
set(PLUGINWIDGET_PLUGIN_RELEASE_DIR "${PLUGINWIDGET_PLUGIN_RELEASE_DIR}" PARENT_SCOPE)




