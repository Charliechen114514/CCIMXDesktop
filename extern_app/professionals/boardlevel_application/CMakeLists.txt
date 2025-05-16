# Board Level Requires the Actual Test in IMX6ULL with sensors
# So, only using arm compilers make sense of actual use

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)
# Auto generate the CCIMX_ALL_RELEASE_DIR and base app dir
if(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    message(STATUS "Cross compile detected, so this will compile in the real adapters")
    # defines in the file with real adapters
    add_compile_definitions(USE_REAL_ADAPTER)
else()
    message(STATUS "Non-arm platform detected, so choose to compile the pesudo one")
endif()


add_subdirectory(Environment)
add_subdirectory(LightController)
add_subdirectory(SportsHealth)











