#pragma once
#include "IEvent.h"
class MysteriousEvent : public IEvent {
public:
    explicit MysteriousEvent(std::mt19937& gen) : gen(gen) {}

    void trigger(int depth) const override {
        // Dungeon seed와 동일한 값으로 난수 생성기 초기화
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
    std::unique_ptr<IEvent> clone() const override {
        return std::make_unique<MysteriousEvent>(gen); // 동일한 gen 전달
    }

private:
    // 이벤트메니저 클래스의 gen 값 참조
    std::mt19937& gen;
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

    // shop 클래스 생성은 이벤트 호출시에만 생성하는 방향으로 가자
    class Shop{
    public:
        explicit Shop(std::mt19937& gen) : gen(gen) {}
        // 메인 샵 입장 함수
        void MainShopEvents(int depth) const;
        // Step 1.1 구매 할수있는 아이템 목록 초기화
        ItemId BuyList(int depth)const;
        // Step 1. 상점 입장 후 스크립트(벡터 참조 값 받아서 스크립트 전개도 진행)
        // => 선택지 (번호 선택), 마지막 번호를 나가기 번호 
        // => 나가기 번호 선택시 Yes_Or_No 후 Yes시 그냥 나감
        // => 아닐경우 Step 1 복귀(while문 사용)
        void Shopscript(ItemId Id) const;
        // Step 2. 번호 입력시 아이템 상세 설명 표시
        // 미 구매시 step. 1 으로 복귀
        void shopCloseUp()const;
        // step 3. 아이템 얻는 스크립트 및 실제 아이템 추가
        // 구매 가능한지 체크, x시 Step 1번 복귀 아니면 실제 구매해서 ItemBag에 Add
        // 그 후 (  )를 구매했습니다. /n 남은 잔돈 ( ) 표시
        void BuyItem()const;
        // 아이템 구매 함수 반환값 확인 후 구매 완료 문제 없으면
        // BuyList에서 만든 vector 변환(ItemId에서 End값으로 하면 될듯)
    private:
        std::mt19937& gen; // 난수 생성기 참조
        // BuyList에서 초기화 진행
        vector<ItemId> ShopList;
    };
};
// NowCoding : 상점 클래스 제작 작업 진행 중
// 아이템에서 가치 제작 완료
// 상점 이벤트에 필요한것...
    // 1. 스크립트
    // 2. 아이템 생성 메커니즘
    // 3. 아이템 금액
    // 4. 내가 가진돈, 5. 구매 스크립트 및 실제 아이템 얻기
    // 
    // Step 1. 아이템 보여주기 1. 아이템 이름, 가격/ 2. 아이템 이름 가격 /... 등 
    // => 선택지 (번호 선택), 마지막 번호를 나가기 번호 
    // => 나가기 번호 선택시 Yes_Or_No 후 Yes시 그냥 나감
    // => 아닐경우 Step 1 복귀(while문 사용)
    // Step 2. 아이템 번호 선택 -> 아이템 이름, 가격, 효과 => view 
    // 선택지 1. 아이템 구매, 2. 뒤로가기 => 뒤로가기 시 Step 2로 복귀
    // step 3. 아이템 얻는 스크립트 및 실제 아이템 추가
    // step 4. 구매한 아이템 팔린 상품이라고 그 위치 에 보여주면서 Step 1 으로 복귀
    