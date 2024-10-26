#pragma once
#include "Item.h"

struct EqBase
{
	//기본 정보
	string	name; //장비 이름입니다.
	int		AttackUp; //추가 공격력 수치
	int		DefenseUp; // 추가 방어력 수치
	int		MaxDurability; // 한계 내구도 수치, 현재 내구도 구현 해야됨
	int		Buythis; // 구매비용
	uint8_t data; // 1바이트 데이터를 사용해 비트별로 관리

	// 비트 마스크 정의
	static constexpr uint8_t Sell_MASK =	0x01;  // 00000001 - Sell? (1비트) 판매 가능 여부
	static constexpr uint8_t Type_MASK =	0x07;  // 00001110 - type (3비트)
	// 한손무기, 양손무기, 장화, 바지, 상의, 보호구, 악세(한칸씩 3개)
	static constexpr uint8_t RARITY_MASK =	0x30;  // 00110000 - rarity (2비트) 희귀도
	// 노말, 희귀, 영웅, 전설

	//// 생성자
	//EqBase(uint8_t type, uint8_t rarity, uint8_t upgradeLevel) : data(0) {
	//	SetType(type);
	//	SetRarity(rarity);
	//	SetUpgradeLevel(upgradeLevel);
	//}
	//// Type 설정 (0~15 가능)
	//void SetType(uint8_t type) {
	//	data = (data & ~TYPE_MASK) | (type & 0x0F);
	//}

	//// Rarity 설정 (0~7 가능)
	//void SetRarity(uint8_t rarity) {
	//	data = (data & ~RARITY_MASK) | ((rarity & 0x07) << 4);
	//}

	//// Upgrade Level 설정 (0 또는 1 가능)
	//void SetUpgradeLevel(uint8_t upgradeLevel) {
	//	data = (data & ~UPGRADE_MASK) | ((upgradeLevel & 0x01) << 7);
	//}
};
struct MyStruct
{
	//upgradeLevel, maxUpgradeLevel : 장비의 강화 단계를 나타내며, 최대 강화 단계까지 도달할 수 있습니다.
	// 4bit 이거는 기본정보가 아닌 실시간 적용되어야 하는 정보 => 장비 도감(?) 에는 들어가지 않음	
	//enhancementSuccessRate : 강화 시도 시 성공할 확률로, 강화 시스템이 있는 경우 사용될 수 있습니다. 함수로 구현
	//추가 효과
	//additionalEffects : 장비가 가지는 특별한 효과 목록으로 따로 관리

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

