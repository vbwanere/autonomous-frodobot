#include "../lidar/LidarScanner.hpp"
#include <iostream>

using namespace frodobot;

int main() {
    int count = 10;

    LidarScanner scanner("/dev/ttyUSB0");

    for (int i = 0; i < count; i++) {
        auto result = scanner.grabScan();

        if (result.isOk()){
            auto points = result.value();
            for (auto& p : points) {
                std::cout << "angle: " << p.angle
                          << " dist: " << p.distance
                          << "    Q: " << p.quality << "\n";
            }

        }
        else {
            std::cout << "Error: " << result.error().message << "\n";
        }

    }

}