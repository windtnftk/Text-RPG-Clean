#pragma once
#include "IEvent.h"
class MysteriousEvent : public IEvent {
public:
    explicit MysteriousEvent(unsigned int seed) : gen(seed) {}

    void trigger(int depth) const override {
        std::uniform_int_distribution<int> dist(1, 5);
        int randomEvent = dist(gen);

        switch (randomEvent) {
        case 1: Ez_Event1(); break;
        case 2: Ez_Event2(); break;
        case 3: Ez_Event3(); break;
        case 4: Ez_Event4(); break;
        case 5: Ez_Event5(); break;
        }
    }

private:
    mutable std::mt19937 gen;
    void Ez_Event1() const;
    void Ez_Event2() const;
    void Ez_Event3() const;
    void Ez_Event4() const;
    void Ez_Event5() const;
    void Hard_Event1() const;
    void Hard_Event2() const;
    void Hard_Event3() const;
    void Hard_Event4() const;
    void Hard_Event5() const;
};

// 상점 이벤트에 필요한것...
    // 1. 스크립트
    // 2. 아이템 생성 메커니즘
    // 3. 아이템 금액
    // 4. 내가 가진돈, 5. 구매 스크립트 및 실제 아이템 얻기
    // 
    // Step 1. 아이템 보여주기 1. 아이템 이름, 가격/ 2. 아이템 이름 가격 /... 등 
    // => 선택지 (번호 선택), 마지막 번호를 나가기 번호 => 나가기 번호 선택시 Yes_Or_No 후 Yes시 그냥 나감
    // Step 2. 아이템 번호 선택 -> 아이템 이름, 가격, 효과 => view 
    // 선택지 1. 아이템 구매, 2. 뒤로가기 => 뒤로가기 시 Step 2로 복귀
    // step 3. 아이템 얻는 스크립트 및 실제 아이템 추가