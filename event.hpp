#pragma once
#include <variant>
#include <string>

enum class EventType {
    TelemetryReceived,
    UserCommand,
    Quit
};

struct TelemetryData {
    double lat, lon, alt;
};

struct UserCommand {
    std::string command;
};

// Expand this union as the system grows.
using EventPayload = std::variant<std::monostate, TelemetryData, UserCommand>;

struct Event {
    EventType type;
    EventPayload payload;
};