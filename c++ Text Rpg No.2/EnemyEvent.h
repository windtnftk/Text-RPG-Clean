#pragma once
#include "IEvent.h"

class EnemyEvent : public IEvent {
public:
    explicit EnemyEvent(std::string enemyType) : enemyType(enemyType) {}

    void trigger(int depth) const override {
        std::cout << "Enemy Encounter: " << enemyType << " at depth " << depth << std::endl;
    }

    std::unique_ptr<IEvent> clone() const override {
        return std::make_unique<EnemyEvent>(*this);
    }

private:
    std::string enemyType;
};

