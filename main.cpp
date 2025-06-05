#include "eventQueue.hpp"
#include "eventBus.hpp"
#include "eventLoop.hpp"
#include "viewerService.hpp"
#include "commandLineService.hpp"
#include "transportServiceUARTLinux.cpp"
#include <thread>
#include <iostream>

int main() {
    EventQueue queue;
    EventBus bus;
    ViewerService viewer;
    TransportServiceUART transport("/dev/pts/4", 9600);

    bus.subscribe(EventType::TelemetryReceived, [&](const EventPayload& p) {
        viewer.onTelemetry(p);
    });

    bus.subscribe(EventType::UserCommand, [&](const EventPayload& p) {
        transport.start(queue);
    });

    bus.subscribe(EventType::Quit, [&](const EventPayload&) {
        std::cout << "[System] Quit signal received\n";
    });

    CLIService cli(queue);
    std::thread cli_thread([&]() {
        cli.run();
    });

    std::thread event_loop_thread([&]() {
        run_event_loop(queue, bus);
    });

    cli_thread.join();
    event_loop_thread.join();

    return 0;
}
