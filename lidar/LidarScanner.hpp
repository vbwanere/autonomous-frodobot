#pragma once
#include "../core/Result.hpp"
#include "ScanPoint.hpp"
#include "../rplidar_sdk/sdk/include/sl_lidar.h"
#include <string>
#include <vector>

namespace frodobot {

class LidarScanner {
public:
    LidarScanner(std::string port); // constructor - connect and start motor.
    ~LidarScanner();                // destructor - stop motor, disconnect.

    Result<std::vector<ScanPoint>> grabScan();

private:
    sl::ILidarDriver* m_driver  = nullptr;
    sl::IChannel*     m_channel = nullptr;
    std::string       m_port;
};    

} // namespace frodobot

