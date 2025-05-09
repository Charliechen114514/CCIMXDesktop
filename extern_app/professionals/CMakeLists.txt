message(STATUS "Entering configuring the professional apps")
message(STATUS "Configuring the must libraries for the professional apps")

option(INCLUDE_OPENCV_QT_ADAPTER    "OpenCV Qt Convient Adapter"    ON)

add_subdirectory(library)




