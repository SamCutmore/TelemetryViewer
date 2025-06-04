#pragma once
#include "event.hpp"
#include <functional>
#include <unordered_map>
#include <vector>

class EventBus {
    using Handler = std::function<void(const EventPayload&)>;
    std::unordered_map<EventType, std::vector<Handler>> subscribers_;

public:
    void subscribe(EventType type, Handler handler) {
        subscribers_[type].emplace_back(std::move(handler));
    }

    void publish(const Event& event) const {
        auto it = subscribers_.find(event.type);
        if (it != subscribers_.end()) {
            for (const auto& handler : it->second) {
                handler(event.payload);
            }
        }
    }
};
