# this is a utils functions to fast mark the message origin project
function(project_message)
    set(options)
    set(oneValueArgs LEVEL PREFIX)
    set(multiValueArgs MESSAGE)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # default we set STATUS
    if(NOT ARG_LEVEL)
        set(ARG_LEVEL STATUS)
    endif()

    # fetch from the project name automatically
    if(NOT DEFINED LOGGER_PROJECT_NAME)
        if(DEFINED PROJECT_NAME)
            set(LOGGER_PROJECT_NAME ${PROJECT_NAME})
        else()
            set(LOGGER_PROJECT_NAME "UNKNOWN_PROJECT")
        endif()
        set(LOGGER_PROJECT_NAME ${LOGGER_PROJECT_NAME} CACHE INTERNAL "当前项目名")
    endif()

    # build up the prefix
    set(full_prefix "[${LOGGER_PROJECT_NAME}]")
    if(ARG_PREFIX)
        string(APPEND full_prefix "[${ARG_PREFIX}]")
    endif()

    # make things full_message
    string(JOIN " " full_message ${full_prefix} ${ARG_MESSAGE})
    message(${ARG_LEVEL} "${full_message}")
endfunction()

# 可选：定义快捷函数
function(fast_project_message)
    project_message(MESSAGE ${ARGV})
endfunction()