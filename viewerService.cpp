#include "viewerService.hpp"
#include <iostream>

ViewerService::ViewerService() {
    std::cout << "[ViewerService] Constructed\n";
}

void ViewerService::onTelemetry(const EventPayload& p) {
    if (auto data = std::get_if<TelemetryData>(&p)) {
        std::cout << "\n[ViewerService] Telemetry: " 
                  << data->lat << ", " << data->lon << ", " << data->alt << std::endl;
    }
}

