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

using EventPayload = std::variant<std::monostate, TelemetryData, UserCommand>;

struct Event {
    const EventType type;
    const EventPayload payload;

    explicit Event(EventType t, EventPayload p) : type(t), payload(std::move(p)) {}

};