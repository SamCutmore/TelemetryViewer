#pragma once
#include "event.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>

class EventQueue {
    std::queue<Event> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;

public:
    void push(Event ev) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(ev));
        cv_.notify_one();
    }

    Event wait_and_pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this]{ return !queue_.empty(); });
        Event ev = std::move(queue_.front());
        queue_.pop();
        return ev;
    }
};