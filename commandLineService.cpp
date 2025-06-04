#include "commandLineService.hpp"
#include <iostream>

CLIService::CLIService(EventQueue& queue) : queue_(queue) {}

void CLIService::run() {
    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        if(line == "push telemetry") {
            TelemetryData data{51.5, -0.1, 100};
            queue_.push(Event{EventType::TelemetryReceived, EventPayload{data}});
        }
        
        if (line == "quit" || line == "exit") {
            queue_.push({EventType::Quit, {}});
            break;
        }

        queue_.push({EventType::UserCommand, UserCommand{line}});
    }
}
