cmake_minimum_required(VERSION 3.10)
project(autonomous-frodobot)
set(CMAKE_CXX_STANDARD 17)

# Tell compiler where to find header files
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/rplidar_sdk/sdk/include
    ${CMAKE_SOURCE_DIR}/rplidar_sdk/sdk/src
)

# Build the lidar console demo executable from these source files
add_executable(lidar_console_demo
    examples/lidar_console_demo.cpp
    lidar/LidarScanner.cpp
)

# Link against the RPLIDAR SDK and pthread for threading
target_link_libraries(lidar_console_demo
    ${CMAKE_SOURCE_DIR}/rplidar_sdk/output/Linux/Release/libsl_lidar_sdk.a
    pthread
)
