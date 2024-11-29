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
    unsigned int seed; // 난수 생성 시 사용할 시드값
    std::mt19937 gen;  // 난수 생성기

    // TODO: 다양한 이벤트를 관리하는 벡터들, Event 관리 함수 상속예정
    std::vector<MysteriousEvent> mysteriousEvents;
    std::vector<std::function<void()>> enemyEncountersEasy; // 적 교전 이벤트 진행
    std::vector<std::function<void()>> enemyEncountersHard;// 적 교전 이벤트 진행
    std::vector<std::function<void()>> itemPickupsBasic;// 아이템 습득 진행 예정
    std::vector<std::function<void()>> itemPickupsRare;// 아이템 습득 진행 예정
    
    // TODO: 추후에 Main함수등에서 시드값 만드는거 구현해야함
    // 초기화 함수들
    void initMysteriousEvents(); // TODO: 아직 Enum Class 아직 추가 안함
    void initEnemyEncounters(); // TODO: 적 출현 이벤트 변경예정
    void initItemPickups();     // TODO: 아이템 등급별 아이템 출현 조정 진행중

    // 각 이벤트 핸들러들
    void handleMysteriousEvent(int eventIndex, int depth);
    void handleEnemyEncounter(int depth);
    void handleItemPickup(int depth);
};
