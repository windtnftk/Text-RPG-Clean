#pragma once
#include "IEvent.h"
class MysteriousEvent : public IEvent {
public:
    explicit MysteriousEvent(std::mt19937& gen) : gen(gen) {}

    void trigger(int depth) const override {
        // Dungeon seed�� ������ ������ ���� ������ �ʱ�ȭ
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
        return std::make_unique<MysteriousEvent>(gen); // ������ gen ����
    }

private:
    // �̺�Ʈ�޴��� Ŭ������ gen �� ����
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

    // shop Ŭ���� ������ �̺�Ʈ ȣ��ÿ��� �����ϴ� �������� ����
    class Shop{
    public:
        explicit Shop(std::mt19937& gen) : gen(gen) {}
        // ���� �� ���� �Լ�
        void MainShopEvents(int depth) const;
        // Step 1.1 ���� �Ҽ��ִ� ������ ��� �ʱ�ȭ
        ItemId BuyList(int depth)const;
        // Step 1. ���� ���� �� ��ũ��Ʈ(���� ���� �� �޾Ƽ� ��ũ��Ʈ ������ ����)
        // => ������ (��ȣ ����), ������ ��ȣ�� ������ ��ȣ 
        // => ������ ��ȣ ���ý� Yes_Or_No �� Yes�� �׳� ����
        // => �ƴҰ�� Step 1 ����(while�� ���)
        void Shopscript(ItemId Id) const;
        // Step 2. ��ȣ �Է½� ������ �� ���� ǥ��
        // �� ���Ž� step. 1 ���� ����
        void shopCloseUp()const;
        // step 3. ������ ��� ��ũ��Ʈ �� ���� ������ �߰�
        // ���� �������� üũ, x�� Step 1�� ���� �ƴϸ� ���� �����ؼ� ItemBag�� Add
        // �� �� (  )�� �����߽��ϴ�. /n ���� �ܵ� ( ) ǥ��
        void BuyItem()const;
        // ������ ���� �Լ� ��ȯ�� Ȯ�� �� ���� �Ϸ� ���� ������
        // BuyList���� ���� vector ��ȯ(ItemId���� End������ �ϸ� �ɵ�)
    private:
        std::mt19937& gen; // ���� ������ ����
        // BuyList���� �ʱ�ȭ ����
        vector<ItemId> ShopList;
    };
};
// NowCoding : ���� Ŭ���� ���� �۾� ���� ��
// �����ۿ��� ��ġ ���� �Ϸ�
// ���� �̺�Ʈ�� �ʿ��Ѱ�...
    // 1. ��ũ��Ʈ
    // 2. ������ ���� ��Ŀ����
    // 3. ������ �ݾ�
    // 4. ���� ������, 5. ���� ��ũ��Ʈ �� ���� ������ ���
    // 
    // Step 1. ������ �����ֱ� 1. ������ �̸�, ����/ 2. ������ �̸� ���� /... �� 
    // => ������ (��ȣ ����), ������ ��ȣ�� ������ ��ȣ 
    // => ������ ��ȣ ���ý� Yes_Or_No �� Yes�� �׳� ����
    // => �ƴҰ�� Step 1 ����(while�� ���)
    // Step 2. ������ ��ȣ ���� -> ������ �̸�, ����, ȿ�� => view 
    // ������ 1. ������ ����, 2. �ڷΰ��� => �ڷΰ��� �� Step 2�� ����
    // step 3. ������ ��� ��ũ��Ʈ �� ���� ������ �߰�
    // step 4. ������ ������ �ȸ� ��ǰ�̶�� �� ��ġ �� �����ָ鼭 Step 1 ���� ����
    