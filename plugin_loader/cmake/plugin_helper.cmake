function(add_qt_plugin_with_json target class version)
    message(STATUS "[CCIMXDesktop] Handling the target ${target}")
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(json_out "${CMAKE_CURRENT_BINARY_DIR}/${class}_plugin.json")
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/plugin.json.in"
        "${json_out}"
        @ONLY
    )

    message(STATUS ${ARG_SOURCES})
    qt_add_plugin(${target}
        CLASS_NAME ${class}
        ${ARG_SOURCES} "${json_out}"
    )

    target_include_directories(${target}
        PRIVATE "${CMAKE_CURRENT_BINARY_DIR}"
    )

    target_link_libraries(${target}
        PRIVATE Qt6::Core Qt6::Widgets
                Qt6::Network
    )

    if(DEFINED PLUGINWIDGET_PLUGIN_RELEASE_DIR AND EXISTS "${PLUGINWIDGET_PLUGIN_RELEASE_DIR}")
        message(STATUS "[CCIMXDesktop] Installing plugin ${target} to ${PLUGINWIDGET_PLUGIN_RELEASE_DIR}")

        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${target}>"
            "${PLUGINWIDGET_PLUGIN_RELEASE_DIR}"
            COMMENT "[CCIMXDesktop] Copied ${target} binary to ${PLUGINWIDGET_PLUGIN_RELEASE_DIR}"
        )

    else()
        message(WARNING "[CCIMXDesktop] PLUGINWIDGET_PLUGIN_RELEASE_DIR is not defined or not a directory. Skip installing ${target}.")
    endif()
endfunction()

