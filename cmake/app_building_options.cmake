# Documentation supports
option(CCIMX_DESKTOP_DOCGEN_REQ "Options for whether generate the document, Now Doxygen required" ON)

# Options for support
option(INCLUDE_WEATHER_APP "Build the Weather App" ON)
option(INCLUDE_PDF_BROWSER_APP "Build the PDF Browser App" ON)
option(INCLUDE_CAMERA_APP "Build the Camera App" ON)
option(INCLUDE_FILERAMBER_APP "Build the FileRamber App" ON)
option(INCLUDE_SYSTEMSTATUS_APP "Build the System Status App" ON)
option(INCLUDE_MEDIAPLAYER_APP "Build the MeidaPlayer App" ON)
option(INCLUDE_PROFESSIONAL_APP "Build the professional App Enabled" ON)
option(INCLUDE_NETHELPER_APP "Build the NetHelper Enable" ON)
option(INCLUDE_EASYNOTE_APP "Build the Markdown Editor" ON)
option(INCLUDE_GAME_APP "Build the Game Subpart" ON)
option(CCIMX_BUILD_TEST "Create the test cases and process build time test" OFF)
if(INCLUDE_PROFESSIONAL_APP)
    option(INCLUDE_OPENCV_QT_ADAPTER    "OpenCV Qt Convient Adapter"    ON)
    if(INCLUDE_OPENCV_QT_ADAPTER)
        option(INCLUDE_IMAGE_PROCESSOR    "Simple Image Processor example based on OpenCV"    ON)
        add_compile_definitions(
            $<$<BOOL:${INCLUDE_IMAGE_PROCESSOR}>:INCLUDE_IMAGE_PROCESSOR>)
    endif()
    option(INCLUDE_LED_APP "Build the LEDController App" ON)
    option(INCLUDE_ENV_APP "Build the Environment App" ON)
    option(INCLUDE_SPORT_APP "Build the SportsHealth App" ON)
    add_compile_definitions(
        $<$<BOOL:${INCLUDE_LED_APP}>:INCLUDE_LED_APP>
        $<$<BOOL:${INCLUDE_ENV_APP}>:INCLUDE_ENV_APP>
        $<$<BOOL:${INCLUDE_SPORT_APP}>:INCLUDE_SPORT_APP>
    )
endif()

if(INCLUDE_GAME_APP)
    message(STATUS "[CCIMXDesktop]:  Games are performance required, with a bit long build")
    option(INCLUDE_DINO_GAME "Dinasour Game in Google Style!" ON)
    add_compile_definitions(
        $<$<BOOL:${INCLUDE_DINO_GAME}>:INCLUDE_DINO_GAME>
    )
endif()
