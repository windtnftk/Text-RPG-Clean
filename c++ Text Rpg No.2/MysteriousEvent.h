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

// ���� �̺�Ʈ�� �ʿ��Ѱ�...
    // 1. ��ũ��Ʈ
    // 2. ������ ���� ��Ŀ����
    // 3. ������ �ݾ�
    // 4. ���� ������, 5. ���� ��ũ��Ʈ �� ���� ������ ���
    // 
    // Step 1. ������ �����ֱ� 1. ������ �̸�, ����/ 2. ������ �̸� ���� /... �� 
    // => ������ (��ȣ ����), ������ ��ȣ�� ������ ��ȣ => ������ ��ȣ ���ý� Yes_Or_No �� Yes�� �׳� ����
    // Step 2. ������ ��ȣ ���� -> ������ �̸�, ����, ȿ�� => view 
    // ������ 1. ������ ����, 2. �ڷΰ��� => �ڷΰ��� �� Step 2�� ����
    // step 3. ������ ��� ��ũ��Ʈ �� ���� ������ �߰�