cmake_minimum_required(VERSION 3.19)
project(CCCalendar LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(CalendarWidgetSrc
    ui/calendar_widget/ModernCalendarWidget.h
    ui/calendar_widget/ModernCalendarWidget.cpp
    sources/icons.qrc)


qt_add_executable(CCCalendar
    WIN32 MACOSX_BUNDLE
    main.cpp
    CalendarWindow.cpp
    CalendarWindow.h
    CalendarWindow.ui
    ${CalendarWidgetSrc}
    ui/panel_widget/PanelWidget.h ui/panel_widget/PanelWidget.cpp
    ui/date_noter/DateNoter.h ui/date_noter/DateNoter.cpp ui/date_noter/DateNoter.ui
    ui/date_icon/DateIcon.h ui/date_icon/DateIcon.cpp
    core/DateDescriberFormatter.h core/DateDescriberFormatter.cpp
    core/Noter.h core/Noter.cpp
    ui/note_creator/NoteCreatorWindow.h ui/note_creator/NoteCreatorWindow.cpp ui/note_creator/NoteCreatorWindow.ui
    ui/color_picker/ColorPicker.h ui/color_picker/ColorPicker.cpp
)

target_link_libraries(CCCalendar
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(CCCalendar PRIVATE Qt6::Widgets)
target_link_libraries(CCCalendar PRIVATE Qt6::Widgets)
target_link_libraries(CCCalendar PRIVATE Qt6::Widgets)
target_include_directories(CCCalendar PRIVATE
    ui/calendar_widget ui ui/date_icon core ui/color_picker)
include(GNUInstallDirs)

install(TARGETS CCCalendar
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

add_custom_command(TARGET CCCalendar POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:CCCalendar> ${CCIMX_INSTALL_APP_BASE_DIR}
)

qt_generate_deploy_app_script(
    TARGET CCCalendar
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
