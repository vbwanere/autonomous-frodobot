# Autonomous Frodobot

C++ autonomy stack for a Frodobot differential-drive robot.

![ROS2](https://img.shields.io/badge/ROS2-Humble-blue)
![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-Jetson_Orin-green)
![License](https://img.shields.io/badge/License-MIT-yellow)
![Hardware](https://img.shields.io/badge/LIDAR-RPLIDAR_A1M8-red)

## Hardware

- RPLIDAR A1M8 (360° 2D LIDAR, 12m range)
- MPU9250 9-axis IMU (onboard YB-ERF01)
- BLDC encoder motors
- YB-ERF01 V3 control board (STM32F103RCT6)
- Jetson Orin Nano/NX (JetPack 6.x, ROS2 Humble)

## What's working

- Custom C++ LIDAR driver wrapping Slamtec's `rplidar_sdk` — no `rplidar_ros`
- ROS2 node publishing `sensor_msgs/LaserScan` on `/scan`
- RAII resource management, `Result<T>` error handling throughout

## Repo structure

```
autonomous-frodobot/
├── rplidar_sdk/                     # Slamtec SDK (submodule)
└── src/
    └── frodobot_lidar/              # ROS2 package
        ├── core/
        │   └── Result.hpp           # Generic error handling
        ├── lidar/
        │   ├── ScanPoint.hpp        # angle, distance, quality
        │   ├── LidarScanner.hpp     # SDK wrapper interface
        │   └── LidarScanner.cpp     # Connect, scan, disconnect
        ├── src/
        │   └── lidar_node.cpp       # ROS2 publisher node
        ├── examples/
        │   └── lidar_console_demo.cpp
        ├── package.xml
        └── CMakeLists.txt
```

## Build & run

```bash
# Clone with SDK submodule
git clone --recurse-submodules https://github.com/vbwanere/autonomous-frodobot.git
cd autonomous-frodobot

# If already cloned without submodules
git submodule update --init

# Build SDK
cd rplidar_sdk && make && cd ..

# Build ROS2 package
colcon build
source install/setup.bash

# Run (LIDAR on /dev/ttyUSB0)
ros2 run frodobot_lidar lidar_node

# Visualize (on another machine, same ROS_DOMAIN_ID)
rviz2
# Fixed Frame → laser, Add → By topic → /scan → LaserScan
```

## Roadmap

- [ ] IMU driver (MPU9250)
- [ ] Encoder driver
- [ ] STM32 firmware (PID velocity control)
- [ ] Scan matching
- [ ] EKF sensor fusion
- [ ] SLAM / occupancy grid
- [ ] Navigation / obstacle avoidance
