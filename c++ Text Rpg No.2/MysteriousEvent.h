#pragma once
enum class EventList {
    test1,
    test2,
    test3,
    test4,
    test5
};
class MysteriousEvent {
public:
    MysteriousEvent(EventList eventType) : eventType(eventType) {}

    // NowCoding: 24.11.29 이벤트 생성 중
    void Ez_Event1() const;
    void Ez_Event2() const;
    void Ez_Event3() const;
    void Ez_Event4() const;
    void Ez_Event5() const;
    void Hard_Event1()const;
    void Hard_Event2()const;
    void Hard_Event3()const;
    void Hard_Event4()const;
    void Hard_Event5()const;
    string getEasyEventMessage()const;
    string getHardEventMessage()const;

    void trigger(int depth) const {
        if (depth < 3) {
            std::cout << getEasyEventMessage() << std::endl;
        }
        else {
            std::cout << getHardEventMessage() << std::endl;
        }
    }

private:
    EventList eventType;
};

