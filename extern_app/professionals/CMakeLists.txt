message(STATUS "Entering configuring the professional apps")
message(STATUS "Configuring the must libraries for the professional apps")
add_subdirectory(library)

message(STATUS "About to configure the board level application")
add_subdirectory(boardlevel_application)




