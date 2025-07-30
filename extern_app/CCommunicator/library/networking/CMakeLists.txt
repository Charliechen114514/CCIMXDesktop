find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
add_library(PeerConnectionCore
    PeerConnection.cpp PeerConnection.h
    NetInfo.h NetInfo.cpp)
target_include_directories(PeerConnectionCore PUBLIC .)

target_link_libraries(PeerConnectionCore
    PUBLIC
        Qt::Core
        Qt6::Network
)

add_library(DataProtocolizedController
    DataProtocolizedController.h
    DataProtocolizedController.cpp
    DataHeader.h
    DataHeader.cpp
    DataSinker.h
    FileSinker.h FileSinker.cpp
    ImageSinker.h ImageSinker.cpp
    MemorySinker.h MemorySinker.cpp
    DataSinkerRouter.h DataSinkerRouter.cpp
    ISinkerRouter.h
    MetaInfoSinker.h MetaInfoSinker.cpp
)

target_include_directories(DataProtocolizedController PUBLIC .)

target_link_libraries(DataProtocolizedController
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt6::Network
)






