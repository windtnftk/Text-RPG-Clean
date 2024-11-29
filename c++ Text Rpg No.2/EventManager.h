#pragma once
#include "MysteriousEvent.h"
enum class EventType {
    Enemy,
    Treasure,
    Shop,
    Event
};
class EventManager {
public:
    EventManager(unsigned int seed);
    void triggerEvent(EventType eventType, int depth);

private:
    unsigned int seed; // ���� ���� �� ����� �õ尪
    std::mt19937 gen;  // ���� ������

    // TODO: �پ��� �̺�Ʈ�� �����ϴ� ���͵�, Event ���� �Լ� ��ӿ���
    std::vector<MysteriousEvent> mysteriousEvents;
    std::vector<std::function<void()>> enemyEncountersEasy; // �� ���� �̺�Ʈ ����
    std::vector<std::function<void()>> enemyEncountersHard;// �� ���� �̺�Ʈ ����
    std::vector<std::function<void()>> itemPickupsBasic;// ������ ���� ���� ����
    std::vector<std::function<void()>> itemPickupsRare;// ������ ���� ���� ����
    
    // TODO: ���Ŀ� Main�Լ���� �õ尪 ����°� �����ؾ���
    // �ʱ�ȭ �Լ���
    void initMysteriousEvents(); // TODO: ���� Enum Class ���� �߰� ����
    void initEnemyEncounters(); // TODO: �� ���� �̺�Ʈ ���濹��
    void initItemPickups();     // TODO: ������ ��޺� ������ ���� ���� ������

    // �� �̺�Ʈ �ڵ鷯��
    void handleMysteriousEvent(int eventIndex, int depth);
    void handleEnemyEncounter(int depth);
    void handleItemPickup(int depth);
};
