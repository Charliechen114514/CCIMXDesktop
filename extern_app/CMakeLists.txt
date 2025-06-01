if (INCLUDE_WEATHER_APP)
    message(STATUS "Ready to build the Weather APP due to the INCLUDE_WEATHER_APP")
    add_subdirectory(WeatherApp)
endif()

if (INCLUDE_PDF_BROWSER_APP)
    message(STATUS "Ready to build the PDF Browser due to the INCLUDE_PDF_BROWSER_APP")
    add_subdirectory(pdfReader)
endif()

if (INCLUDE_CAMERA_APP)
    message(STATUS "Ready to build the Camera App due to the INCLUDE_CAMERA_APP")
    add_subdirectory(GeneralLocalCamera)
endif()

if (INCLUDE_FILERAMBER_APP)
    message(STATUS "Ready to build the FileRamber due to the INCLUDE_FILERAMBER_APP")
    add_subdirectory(FileRamber)
endif()

if (INCLUDE_SYSTEMSTATUS_APP)
    message(STATUS "Ready to build the System Status App due to the INCLUDE_SYSTEMSTATUS_APP")
    add_subdirectory(SystemState)
endif()

if (INCLUDE_MEDIAPLAYER_APP)
    message(STATUS "Ready to build the Media Player App due to the INCLUDE_MEDIAPLAYER_APP")
    add_subdirectory(MediaPlayer)
endif()

if(INCLUDE_PROFESSIONAL_APP)
    message(STATUS "Professional App is enabled due to the INCLUDE_PROFESSIONAL_APP")
    add_subdirectory(professionals)
endif()

if(INCLUDE_NETHELPER_APP)
    message(STATUS "NetHelper App is enabled due to the INCLUDE_NETHELPER_APP")
    add_subdirectory(NetHelper)
endif()
