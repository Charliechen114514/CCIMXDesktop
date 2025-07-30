message(STATUS "Ready to build the test")
find_package(Qt6 REQUIRED COMPONENTS Test)
add_executable(test_p2p test.cpp)

target_link_libraries(test_p2p PRIVATE PeerConnectionCore)

add_executable(test_protocal test_protocal.cpp)
target_link_libraries(test_protocal PRIVATE DataProtocolizedController Qt6::Test)

add_executable(test_sink tst_testsinks.cpp)
target_link_libraries(test_sink PRIVATE DataProtocolizedController Qt6::Test)

add_executable(test_sink_sendrecv TestDataProtocolizedController.cpp)
target_link_libraries(test_sink_sendrecv PRIVATE DataProtocolizedController Qt6::Test)

add_executable(example_seen_image example.cpp)
target_link_libraries(example_seen_image PRIVATE DataProtocolizedController Qt6::Test)

add_executable(example_seen_image2 example2.cpp)
target_link_libraries(example_seen_image2 PRIVATE
    DataProtocolizedController Qt6::Test PeerConnectionCore)

add_executable(example_seen_image3 example3.cpp)
target_link_libraries(example_seen_image3 PRIVATE
    DataProtocolizedController Qt6::Test PeerConnectionCore)
