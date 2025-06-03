cmake_minimum_required(VERSION 3.19)
project(CCIMX_DinoGame LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 23)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets MultiMedia)

qt_standard_project_setup()

set(CoreSrc
    core/FrameProvider.h core/FrameProvider.cpp
    core/SoundEffectPlayer.h core/SoundEffectPlayer.cpp
    core/FlushRequester.h core/FlushRequester.cpp
    core/EventManager.h core/EventManager.cpp
    core/ScoreManager.h core/ScoreManager.cpp
    core/ObstacleListManager.h core/ObstacleListManager.cpp
    core/ObstacleType.h
    core/DifficultyManager.h core/DifficultyManager.cpp
    core/DifficultyType.h)

set(UiSrc
    ui/DinasourGameWindow.cpp
    ui/DinasourGameWindow.h
    ui/DinasourGameWindow.ui
    ui/DinasourGameMainWidget.h
    ui/DinasourGameMainWidget.cpp
    ui/FigureFrameFetcher.h ui/FigureFrameFetcher.cpp
    ui/SceneDrawer.h ui/SceneDrawer.cpp
    ui/GroundLineProviders.h ui/GroundLineProviders.cpp)

set(SettingsSrc
    settings/setting_scene.h
    settings/settings_common.h
    settings/settings_soundeffect.h
    settings/settings_figure.h
    settings/settings_score.h)

set(FigureLevelSrc
    figure/FigureObject.h
    figure/FigureObject.cpp
    figure/dinasour/Dinasour.h figure/dinasour/Dinasour.cpp
    figure/obstacle/Obsticals.h figure/obstacle/Obsticals.cpp
    figure/obstacle/CactusObsticals.h figure/obstacle/CactusObsticals.cpp
    figure/obstacle/BirdObsticals.h figure/obstacle/BirdObsticals.cpp
)

qt_add_executable(CCIMX_DinoGame
    WIN32 MACOSX_BUNDLE
    ${UiSrc}
    ${SettingsSrc}
    ${CoreSrc}
    ${FigureLevelSrc}
    main.cpp
    sources/sources.qrc
)

target_link_libraries(CCIMX_DinoGame
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Multimedia
)

target_include_directories(CCIMX_DinoGame
    PRIVATE . ./ui)

include(GNUInstallDirs)

install(TARGETS CCIMX_DinoGame
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(TARGET CCIMX_DinoGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_ALL_RELEASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CCIMX_DinoGame> ${CCIMX_ALL_RELEASE_DIR}
)


qt_generate_deploy_app_script(
    TARGET CCIMX_DinoGame
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
