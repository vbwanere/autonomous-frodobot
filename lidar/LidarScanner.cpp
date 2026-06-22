#include "LidarScanner.hpp"

namespace frodobot {

// Constructor
LidarScanner::LidarScanner(std::string port) : m_port(port) {
    m_driver = *sl::createLidarDriver();
    if (!m_driver)
        throw std::runtime_error("Failed to create LIDAR driver");

    m_channel = *sl::createSerialPortChannel(port.c_str(), 115200);
    if (!m_channel)
        throw std::runtime_error("Failed to create serial channel");

    if (!SL_IS_OK(m_driver->connect(m_channel)))
        throw std::runtime_error("Failed to connect to LIDAR on " + port);

    m_driver->setMotorSpeed();
    m_driver->startScan(0, 1);
}

Result<std::vector<ScanPoint>> LidarScanner::grabScan() {
    sl_lidar_response_measurement_node_hq_t nodes[8192];
    size_t count = 8192;

    sl_result op_result = m_driver->grabScanDataHq(nodes, count);

    if (!SL_IS_OK(op_result))
        return Result<std::vector<ScanPoint>>::fail({"SCAN_FAILED", "grabScanDataHq failed"});

    m_driver->ascendScanData(nodes, count);

    std::vector<ScanPoint> points;
    for (int i = 0; i < (int)count; i++) {
        ScanPoint p;
        p.angle    = (nodes[i].angle_z_q14 * 90.f) / 16384.f;
        p.distance = nodes[i].dist_mm_q2 / 4.0f;
        p.quality  = nodes[i].quality >> SL_LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT;
        points.push_back(p);
    }

    return Result<std::vector<ScanPoint>>::ok(points);
}

// Destructor
LidarScanner::~LidarScanner() {
    if (m_driver) {
        m_driver->stop();
        m_driver->setMotorSpeed(0);
        delete m_driver;
        m_driver = nullptr;
    }
    if (m_channel) {
        delete m_channel;
        m_channel = nullptr;
    }
}

} // namespace frodobot




