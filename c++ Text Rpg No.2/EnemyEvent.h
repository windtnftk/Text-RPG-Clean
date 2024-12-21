#pragma once
#include "IEvent.h"

// TODO: 여기 이벤트 제대로 안만들었음 
class EnemyEvent : public IEvent {
public:
    explicit EnemyEvent(std::mt19937& gen) : gen(gen) {}

    void trigger(int depth) const override {
        // Dungeon seed와 동일한 값으로 난수 생성기 초기화
        std::uniform_int_distribution<int> dist(1, 5);
        int randomEvent = dist(gen);
    }
    std::unique_ptr<IEvent> clone() const override {
        return std::make_unique<EnemyEvent>(gen); // 동일한 gen 전달
    }

private:
    std::mt19937& gen;
};

