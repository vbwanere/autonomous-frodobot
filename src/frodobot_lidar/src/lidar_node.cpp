#include <cmath>  // for M_PI
#include <limits> 
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "../lidar/LidarScanner.hpp"

class LidarNode : public rclcpp::Node {
public:
    LidarNode() : Node("lidar_node"), m_scanner("/dev/ttyUSB0") {
        m_pub = this->create_publisher<sensor_msgs::msg::LaserScan>("/scan", 10);
        m_timer = this->create_wall_timer(
            std::chrono::milliseconds(100),
            std::bind(&LidarNode::timer_cb, this));
    }

    void timer_cb() {
        auto result = m_scanner.grabScan();
        if (result.isOk()) {
            auto points = result.value();
            sensor_msgs::msg::LaserScan msg;

            msg.header.stamp = this->now();
            msg.header.frame_id = "laser";
            msg.angle_min = 0.0;
            msg.angle_max = 2.0 * M_PI;
            msg.angle_increment = (2.0 * M_PI) / points.size();
            msg.range_min = 0.15;
            msg.range_max = 12.0;

            for (auto& p : points) {
                if (p.quality == 0) {
                    msg.ranges.push_back(std::numeric_limits<float>::infinity());
                    msg.intensities.push_back(0.0f);
                } else {
                    msg.ranges.push_back(p.distance / 1000.0f);
                    msg.intensities.push_back(p.distance / 1000.0f);  // distance as intensity
                }
            }

            // for (auto& p : points) {
            //     if (p.quality == 0)
            //         msg.ranges.push_back(std::numeric_limits<float>::infinity());
            //     else
            //         msg.ranges.push_back(p.distance / 1000.0f);
            // }
            
            m_pub->publish(msg);
        }
        else {
            RCLCPP_WARN(this->get_logger(), "Scan failed: %s", result.error().message.c_str());
        }
    }

private:
    frodobot::LidarScanner m_scanner;
    rclcpp::Publisher<sensor_msgs::msg::LaserScan>::SharedPtr m_pub;
    rclcpp::TimerBase::SharedPtr m_timer;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LidarNode>());
    rclcpp::shutdown();
    return 0;
}