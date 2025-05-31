# First variables are the var name, with second def value optional
function(setup_version_if_not_defined)
    set(options "")
    set(oneValueArgs VAR_NAME DEFAULT_VALUE)
    set(multiValueArgs "")
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT DEFINED ARG_VAR_NAME)
        message(FATAL_ERROR "You must varify the VAR_NAME params")
    endif()

    if(NOT DEFINED ${ARG_VAR_NAME})
        if(DEFINED ARG_DEFAULT_VALUE)
            set(${ARG_VAR_NAME} ${ARG_DEFAULT_VALUE} CACHE STRING "version vars(Auto set)")
        else()
            set(${ARG_VAR_NAME} 1 CACHE STRING "version vars(Auto set)")
        endif()
        message(STATUS "set ${ARG_VAR_NAME}=${${ARG_VAR_NAME}} defaultly")
    else()
        message(STATUS "using the defined ${ARG_VAR_NAME}=${${ARG_VAR_NAME}}")
    endif()

    set(${ARG_VAR_NAME} ${${ARG_VAR_NAME}} PARENT_SCOPE)
endfunction()

# this functions setup full if using def defined
function(check_and_setup_full_version)
    if(NOT DEFINED CCIMXDESKTOP_VERSION_FULL)
        if(NOT DEFINED CCIMXDESKTOP_VERSION_MAJOR OR
           NOT DEFINED CCIMXDESKTOP_VERSION_MINOR OR
           NOT DEFINED CCIMXDESKTOP_VERSION_PATCH)
            message(FATAL_ERROR "CCIMXDESKTOP_VERSION_MAJOR/MINOR/PATCH are not defined！")
        endif()

        set(CCIMXDESKTOP_VERSION_FULL
            "${CCIMXDESKTOP_VERSION_MAJOR}.${CCIMXDESKTOP_VERSION_MINOR}.${CCIMXDESKTOP_VERSION_PATCH}"
            CACHE STRING "Full versions"
        )
        message(STATUS "already set CCIMXDESKTOP_VERSION_FULL=${CCIMXDESKTOP_VERSION_FULL}")
    else()
        message(STATUS "using defined CCIMXDESKTOP_VERSION_FULL=${CCIMXDESKTOP_VERSION_FULL}")
    endif()
    # export out the symbols
    set(CCIMXDESKTOP_VERSION_FULL ${CCIMXDESKTOP_VERSION_FULL} PARENT_SCOPE)
endfunction()
