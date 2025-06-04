#include "eventQueue.hpp"
#include "eventBus.hpp"
#include "eventLoop.hpp"
#include "viewerService.hpp"
#include "commandLineService.hpp"
#include <thread>
#include <iostream>

int main() {
    EventQueue queue;
    EventBus bus;
    ViewerService viewer;

    std::thread input_thread([&]() {
        queue.push({EventType::TelemetryReceived, TelemetryData{51.5, -0.1, 100}});
        queue.push({EventType::UserCommand, UserCommand{"ARM"}});
        queue.push({EventType::Quit, {}});
    });

    CLIService cli(queue);
    std::thread cli_thread([&]() {
        cli.run();
    });

    std::thread event_loop_thread([&]() {
        run_event_loop(queue, bus);
    });

    input_thread.join();
    cli_thread.join();
    event_loop_thread.join();

    return 0;
}
