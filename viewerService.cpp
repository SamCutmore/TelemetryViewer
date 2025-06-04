#include "viewerService.hpp"
#include <iostream>

ViewerService::ViewerService() {
    std::cout << "[ViewerService] Constructed\n";
}

void ViewerService::onTelemetry(const EventPayload& payload) {
    if (auto data = std::get_if<TelemetryData>(&payload)) {
        std::cout << "\n[ViewerService] Telemetry: " 
                  << data->lat << ", " << data->lon << ", " << data->alt << std::endl;
    }
}