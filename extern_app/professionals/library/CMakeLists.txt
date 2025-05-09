message(STATUS "About to build selected library")



if(INCLUDE_OPENCV_QT_ADAPTER)
    message(STATUS "Build Qt_OpenCV_Adapter Due to the INCLUDE_OPENCV_QT_ADAPTER")
    add_subdirectory(OpencvQtAdapter)
endif()
