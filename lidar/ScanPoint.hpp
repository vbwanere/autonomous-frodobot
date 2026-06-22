#pragma once

namespace frodobot{

    struct ScanPoint
    {
        /* data */
        double angle = 0.0 ; // degrees 0-360
        double distance = 0.0; // mm
        int quality = 0; // signal confidence 0-100 %, 0 - no return
    };
    
} // namespace frodobot

