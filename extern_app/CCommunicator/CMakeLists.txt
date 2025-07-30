cmake_minimum_required(VERSION 3.19)
project(CCIMXCommunicate LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_subdirectory(library)

set(core_src
    core/ListContextInfo.h core/ListContextInfo.cpp
    core/SessionDrawDelegate.h core/SessionDrawDelegate.cpp
    core/SessionContextRole.h
    core/ConnectionUtils.h core/ConnectionUtils.cpp
    core/sessions/Session.h core/sessions/Session.cpp
    core/sessions/SessionInfo.h core/sessions/SessionInfo.cpp
    core/sessions/SessionError.h core/sessions/SessionError.cpp
    core/sessions/SessionProtos.h
    core/sessions/SessionHub.h core/sessions/SessionHub.cpp
    core/historyContainers/MetaMessages.h core/historyContainers/MetaMessages.cpp
    core/historyContainers/HistoryContainers.h
    core/historyContainers/HistoryContainers.cpp)

set(ui_src
    ui/CommunicateMainWindow.cpp
    ui/CommunicateMainWindow.h
    ui/CommunicateMainWindow.ui
    ui/ToolSide/ToolPanel.h ui/ToolSide/ToolPanel.cpp
    ui/ToolSide/ToolsEnum.h
    ui/communication_main/ChatListPanel.h
    ui/communication_main/ChatListPanel.cpp
    ui/communication_main/ChatBubble.h
    ui/communication_main/ChatBubble.cpp
    ui/communication_main/ChatMainPanel.h
    ui/communication_main/ChatMainPanel.cpp
    ui/selfInfo/InfoWidget.h ui/selfInfo/InfoWidget.cpp
    ui/connectors/ConnectorsWidget.h ui/connectors/ConnectorsWidget.cpp
    ui/connectors/ConnectorDelegate.h ui/connectors/ConnectorDelegate.cpp
    ui/connectors/ConnectorEnumType.h
    ui/connectors/AddPanel.h ui/connectors/AddPanel.cpp
    ui/communication_main/CommunicatableStatus.h
    ui/communication_main/HistoryManagerSchedular.h
    ui/communication_main/HistoryManagerSchedular.cpp
    ui/settings/SettingsWidget.h
    ui/settings/SettingsWidget.cpp)

qt_add_executable(CCIMXCommunicate
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${ui_src}
    ${core_src}
)

target_link_libraries(CCIMXCommunicate
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Network
        DataProtocolizedController
        PeerConnectionCore
)
target_include_directories(CCIMXCommunicate PRIVATE
    . ./ui ./ui/communication_main ./ui/ToolSide)

include(GNUInstallDirs)

install(TARGETS CCIMXCommunicate
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET CCIMXCommunicate
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

add_custom_command(TARGET CCIMXCommunicate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CCIMXCommunicate> ${CCIMX_INSTALL_APP_BASE_DIR}
)

install(SCRIPT ${deploy_script})
