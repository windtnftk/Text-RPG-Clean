#pragma once
#include "Item.h"

struct EqBase
{
	//�⺻ ����
	string	name; //��� �̸��Դϴ�.
	int		AttackUp; //�߰� ���ݷ� ��ġ
	int		DefenseUp; // �߰� ���� ��ġ
	int		MaxDurability; // �Ѱ� ������ ��ġ, ���� ������ ���� �ؾߵ�
	int		Buythis; // ���ź��
	uint8_t data; // 1����Ʈ �����͸� ����� ��Ʈ���� ����

	// ��Ʈ ����ũ ����
	static constexpr uint8_t Sell_MASK =	0x01;  // 00000001 - Sell? (1��Ʈ) �Ǹ� ���� ����
	static constexpr uint8_t Type_MASK =	0x07;  // 00001110 - type (3��Ʈ)
	// �Ѽչ���, ��չ���, ��ȭ, ����, ����, ��ȣ��, �Ǽ�(��ĭ�� 3��)
	static constexpr uint8_t RARITY_MASK =	0x30;  // 00110000 - rarity (2��Ʈ) ��͵�
	// �븻, ���, ����, ����

	//// ������
	//EqBase(uint8_t type, uint8_t rarity, uint8_t upgradeLevel) : data(0) {
	//	SetType(type);
	//	SetRarity(rarity);
	//	SetUpgradeLevel(upgradeLevel);
	//}
	//// Type ���� (0~15 ����)
	//void SetType(uint8_t type) {
	//	data = (data & ~TYPE_MASK) | (type & 0x0F);
	//}

	//// Rarity ���� (0~7 ����)
	//void SetRarity(uint8_t rarity) {
	//	data = (data & ~RARITY_MASK) | ((rarity & 0x07) << 4);
	//}

	//// Upgrade Level ���� (0 �Ǵ� 1 ����)
	//void SetUpgradeLevel(uint8_t upgradeLevel) {
	//	data = (data & ~UPGRADE_MASK) | ((upgradeLevel & 0x01) << 7);
	//}
};
struct MyStruct
{
	//upgradeLevel, maxUpgradeLevel : ����� ��ȭ �ܰ踦 ��Ÿ����, �ִ� ��ȭ �ܰ���� ������ �� �ֽ��ϴ�.
	// 4bit �̰Ŵ� �⺻������ �ƴ� �ǽð� ����Ǿ�� �ϴ� ���� => ��� ����(?) ���� ���� ����	
	//enhancementSuccessRate : ��ȭ �õ� �� ������ Ȯ����, ��ȭ �ý����� �ִ� ��� ���� �� �ֽ��ϴ�. �Լ��� ����
	//�߰� ȿ��
	//additionalEffects : ��� ������ Ư���� ȿ�� ������� ���� ����

};

class Equipment : public MainItem
{
public:
	//SINGLE(Equipment);
	

	static Equipment* GetInst() {
		static Equipment instance;
		return &instance;
	}
	void ItemInit() override { std::cout << "hi" << std::endl; }

public:
	Equipment();
	~Equipment();
};

