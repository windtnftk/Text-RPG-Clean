#pragma once
#include "IEvent.h"

// TODO: ���� �̺�Ʈ ����� �ȸ������ 
class EnemyEvent : public IEvent {
public:
    explicit EnemyEvent(std::mt19937& gen) : gen(gen) {}

    void trigger(int depth) const override {
        // Dungeon seed�� ������ ������ ���� ������ �ʱ�ȭ
        std::uniform_int_distribution<int> dist(1, 5);
        int randomEvent = dist(gen);
    }
    std::unique_ptr<IEvent> clone() const override {
        return std::make_unique<EnemyEvent>(gen); // ������ gen ����
    }

private:
    std::mt19937& gen;
};

