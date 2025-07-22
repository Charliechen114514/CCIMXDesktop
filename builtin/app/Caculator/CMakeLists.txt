cmake_minimum_required(VERSION 3.19)
project(Caculator LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CoreSrc
    core/Parser.h core/Parser.cpp
    core/TreeNodeBase.h
    core/NumberNode.h core/NumberNode.cpp
    core/BinaryOpTreeNode.h core/BinaryOpTreeNode.cpp
    core/ParseExceptions.h
    core/UnaryOpTreeNode.h core/UnaryOpTreeNode.cpp
    core/FunctorTreeNode.h core/FunctorTreeNode.cpp
    core/ExpressionEvaluator.cpp core/ExpressionEvaluator.h)

add_library(parser_library STATIC ${CoreSrc})
target_include_directories(parser_library PUBLIC . ./core)
target_link_libraries(parser_library
                        PRIVATE
                        Qt::Core)

set(UiSrc
    ui/CaculatorMainWindow.cpp
    ui/CaculatorMainWindow.h
    ui/CaculatorMainWindow.ui
    ui/Tablet.h ui/Tablet.cpp ui/Tablet.ui
    ui/BonusFunctor.h ui/BonusFunctor.cpp ui/BonusFunctor.ui)

qt_add_executable(Caculator
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${UiSrc}
    sources/sources.qrc
)

target_include_directories(Caculator
    PRIVATE . ./ui)
target_link_libraries(Caculator
    PRIVATE
        parser_library
        Qt::Core
        Qt::Widgets
)

add_executable(test_parser test/test_parser.cpp)
target_link_libraries(test_parser PRIVATE parser_library Qt::Core)

add_custom_command(TARGET Caculator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CCIMX_INSTALL_APP_BASE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Caculator> ${CCIMX_INSTALL_APP_BASE_DIR}
)

include(GNUInstallDirs)

install(TARGETS Caculator
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Caculator
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
