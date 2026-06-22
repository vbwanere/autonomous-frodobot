cmake_minimum_required(VERSION 3.10)
project(autonomous-frodobot)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/rplidar_sdk/sdk/include
    ${CMAKE_SOURCE_DIR}/rplidar_sdk/sdk/src
)

add_executable(lidar_demo
    examples/lidar_console_demo.cpp
    lidar/LidarScanner.cpp
)

target_link_libraries(lidar_demo
    ${CMAKE_SOURCE_DIR}/rplidar_sdk/output/Linux/Release/libsl_lidar_sdk.a
    pthread
)
