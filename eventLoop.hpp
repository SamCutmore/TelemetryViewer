#pragma once
#include "eventQueue.hpp"
#include "eventBus.hpp"
#include <iostream>

void run_event_loop(EventQueue& queue, const EventBus& bus) {
    while (true) {
        Event ev = queue.wait_and_pop();
        if (ev.type == EventType::Quit) {
            break;
        }
        bus.publish(ev);
    }
}