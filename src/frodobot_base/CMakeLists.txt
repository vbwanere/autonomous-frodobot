cmake_minimum_required(VERSION 3.8)
project(frodobot_lidar)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find ROS2 dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

# SDK and project headers
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../../rplidar_sdk/sdk/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../../rplidar_sdk/sdk/src
)

# Build the ROS2 lidar node
add_executable(lidar_node
  src/lidar_node.cpp
  lidar/LidarScanner.cpp
)

ament_target_dependencies(lidar_node
  rclcpp
  sensor_msgs
)

target_link_libraries(lidar_node
  ${CMAKE_CURRENT_SOURCE_DIR}/../../rplidar_sdk/output/Linux/Release/libsl_lidar_sdk.a
  pthread
)

# Install the executable so ros2 run can find it
install(TARGETS lidar_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()