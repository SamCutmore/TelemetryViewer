#include "viewerService.hpp"
#include <iostream>

ViewerService::ViewerService() {
    std::cout << "[ViewerService] Constructed\n";
}

void ViewerService::onTelemetry(const EventPayload& payload) {
    if (auto p = std::get_if<TelemetryData>(&payload)) {
        std::cout << "[ViewerService] Got telemetry: "
                  << p->lat << ", " << p->lon << ", " << p->alt << "\n";
    }
}
