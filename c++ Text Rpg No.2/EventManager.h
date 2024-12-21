#pragma once
#include "IEvent.h"
#include "MysteriousEvent.h"
#include "EnemyEvent.h"

// 이벤트 관리 클래스
// 생성시 IEvent 아들 클래스를 객체로 넣어 트리거시
// 해당 클래스의 트리거 함수로 진행됨
class EventManager {
private:
    // 던전 클래스 에서만 생성가능하도록 생성자 숨김
    friend class Dungeon;
    // explicit 는 생성자 호출시 seed값을 명확히 주도록 제한하는 역활
    // Seed값을 항상 받게 해서 클래스 객체 생성
    explicit EventManager(unsigned int seed) : gen(seed){}
    // IEvent 아들 클래스의 주소값을 새로 생성
    // events 벡터에 저장
    void addEvent(std::unique_ptr<IEvent> event) {
        events.push_back(std::move(event));
    }
    // 이벤트 관련 객체 events의 주소값 반환
    // Dungeon 클래스 초기화시 사용
    IEvent* getRandomEvent() {
        if (events.empty()) {
            return nullptr;
        }

        std::uniform_int_distribution<> dist(0, events.size() - 1);
        int randomIndex = dist(gen);
        return events[randomIndex].get(); // 원본 객체의 포인터 반환
    }

    // 객체 생성한 클래스 보관 변수
    std::vector<std::unique_ptr<IEvent>> events;
    // 메인 Seed 를 이용한 함수 배열값, 나머지 클래스에서는 참조값만 받음
    std::mt19937 gen;
};
