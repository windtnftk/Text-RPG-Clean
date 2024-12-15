#pragma once
#include "IEvent.h"


class EventManager {
public:
    explicit EventManager(unsigned int seed) : gen(seed) {}

    std::unique_ptr<IEvent> getRandomEvent() {
        if (events.empty()) {
            return nullptr;
        }

        std::uniform_int_distribution<> dist(0, events.size() - 1);
        int randomIndex = dist(gen);
        return std::move(events[randomIndex]->clone());
    }

private:
    std::vector<std::unique_ptr<IEvent>> events;
    std::mt19937 gen;
};
