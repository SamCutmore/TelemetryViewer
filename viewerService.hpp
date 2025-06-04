#pragma once
#include "event.hpp"

class ViewerService {
public:
    ViewerService();
    void onTelemetry(const EventPayload& payload);
    void update();
    bool shouldClose() const;

private:
    // SDL/GL state, telemetry buffer, etc.
};
