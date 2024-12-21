#pragma once
#include "IEvent.h"
#include "MysteriousEvent.h"
#include "EnemyEvent.h"

// �̺�Ʈ ���� Ŭ����
// ������ IEvent �Ƶ� Ŭ������ ��ü�� �־� Ʈ���Ž�
// �ش� Ŭ������ Ʈ���� �Լ��� �����
class EventManager {
private:
    // ���� Ŭ���� ������ ���������ϵ��� ������ ����
    friend class Dungeon;
    // explicit �� ������ ȣ��� seed���� ��Ȯ�� �ֵ��� �����ϴ� ��Ȱ
    // Seed���� �׻� �ް� �ؼ� Ŭ���� ��ü ����
    explicit EventManager(unsigned int seed) : gen(seed){}
    // IEvent �Ƶ� Ŭ������ �ּҰ��� ���� ����
    // events ���Ϳ� ����
    void addEvent(std::unique_ptr<IEvent> event) {
        events.push_back(std::move(event));
    }
    // �̺�Ʈ ���� ��ü events�� �ּҰ� ��ȯ
    // Dungeon Ŭ���� �ʱ�ȭ�� ���
    IEvent* getRandomEvent() {
        if (events.empty()) {
            return nullptr;
        }

        std::uniform_int_distribution<> dist(0, events.size() - 1);
        int randomIndex = dist(gen);
        return events[randomIndex].get(); // ���� ��ü�� ������ ��ȯ
    }

    // ��ü ������ Ŭ���� ���� ����
    std::vector<std::unique_ptr<IEvent>> events;
    // ���� Seed �� �̿��� �Լ� �迭��, ������ Ŭ���������� �������� ����
    std::mt19937 gen;
};
