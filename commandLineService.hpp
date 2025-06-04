#pragma once
#include "eventQueue.hpp"

class CLIService {
    EventQueue& queue_;
public:
    CLIService(EventQueue& queue);
    void run();
};
