#include "pch.h"
#include "Item.h"
#include "Ccore.h"

string ItemArr[(int)ItemId::End] =
{
	"HealthPortion",
	"BigHealthPortion",
	"PowerPortion",
	"BigPowerPortion",
	"Potion4",
	"Potion5",
	"Potion6",
	"Potion7",
	"FirePortion",
	"BigFirePortion",
	"Weapon1",
	"Weapon2",
	"Weapon3",
	"Weapon4",
	"Weapon5",
	"Weapon6",
	"Weapon7",
	"Weapon8",
	"Weapon9",
	"Weapon10",
	"Equipment1",
	"Equipment2",
	"Equipment3",
	"Equipment4",
	"Equipment5",
	"Equipment6",
	"Equipment7",
	"Equipment8",
	"Equipment9",
	"Equipment10",
};
void MainItem::ItemInit()
{		/*
		//item을 랜덤으로 3개만 추가 하고 싶은데
		// 일단 5,2,6 이런식으로 고정된 시드값 넣어보자
		
		for (int i = 0; i < (int)ItemId::End; ++i)
		{
			ItemMMOR NewItem = { static_cast<ItemId>(i),ItemArr[i]};
			ItemBag.push_back(NewItem);
		}
		
		std::random_device rd;
		std::mt19937 gen(rd()); // Mersenne Twister 알고리즘을 사용하는 엔진 생성
		// 균일 분포에서 랜덤한 정수 생성 (0 이상 99 이하)
		std::uniform_int_distribution<int> distribution(0, 99);
		for (int i = 0; i < 9; ++i)
		{
			int rendom = distribution(gen) % 10;
			ItemMMOR NewItem = { static_cast<ItemId>(rendom),ItemArr[rendom] };
			ItemBag.push_back(NewItem);
		}
		*/
	
	AddItem(ItemId::Weapon1);
	AddItem(ItemId::Equipment1);
	AddItem(ItemId::HealthPortion);
	handleItem = ItemBag.begin();
	OpenItemBag();
}
void MainItem::HandleItemErase(vector<ItemMMOR>::iterator& ItemId)
{
	if (ItemId != ItemBag.end())
	{
		ItemBag.erase(ItemId);
		handleItem = ItemBag.begin();
	}
}
void MainItem::OpenItemBag()
{
	vector<ItemMMOR>::iterator BeginhandleItem = ItemBag.begin();

	for (int i = 0; i < ItemBag.size(); ++BeginhandleItem, ++i)
	{
		//int GetId = GetInst()->SelectId(BeginhandleItem);
		string GetName = SelectName(BeginhandleItem);
		std::cout << i + 1 << ". " << GetName << std::endl;
	}
}
ItemId MainItem::SelectId(const vector<ItemMMOR>::iterator& ItemId)
{
	if (ItemId == ItemBag.end())
	{
		std::cout << "Get Id fale" << std::endl;
		return ItemId::End;
	}
	else
	{
		return ItemId->CurItemId;
	}

}
string MainItem::SelectName(const vector<ItemMMOR>::iterator& ItemId)
{
	ItemMMOR Hi = *ItemId;
	return (string)Hi.ItemName;
}
void MainItem::UseItemManuOpen()
{
	OpenItemBag();
	// 아이템 을 고르고 사용을 할지 정하자
	std::cout << std::endl << "사용하실 아이템을 고르세요" << std::endl;
	int choice = CinAuto();
	if (0 == choice || choice > ItemBag.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ErrorCode();
		return;
	}
	ItemTypeEffect(convert(choice));
}
void MainItem::AddItem(ItemId item)
{
	if (item <= ItemId::Equipment10)
	{
		ItemMMOR test = { item, ItemArr[static_cast<int>(item)] };
		ItemBag.emplace_back(test);
	}
	else
	{
		std::cout << "잘못된 아이템 아이디입니다." << std::endl;
	}
}
void MainItem::TotalequippedItems()
{
	if (!ViewEquippedItems())return;
	std::cout << "장비를 해체하시겠습니까?" << std::endl;
	if (!Yes_No()) return;
	std::cout << "어떤장비를 해체하시겠습니까?" << std::endl;
	MoveEquipped(CinAuto());
	
}
bool MainItem::ViewEquippedItems()
{
	std::cout << "장착중인 장비" ;
	if (equippedItems.empty())
	{
		std::cout <<"가 없습니다."<< std::endl;
		return false;
	}
	std::cout << std::endl;
	for (auto q : equippedItems)
	{
		auto it = static_cast<int>(q);
		std::cout <<"1. " << std::endl << ItemArr[it] << ", " << std::endl;
	}
	return true;
}
void MainItem::MoveEquipped(int choice)
{
	auto it = equippedItems.begin();
	for (int i = 1; i < choice; ++i)
	{
		++it;
	}
	if (equippedItems.end() == it)
	{
		ErrorCode();
		return;
	}
	equippedItems.erase(it); // 장비 해체
	AddItem(convert(choice)); // 아이템으로 복귀
}
// 아이템 효과 초기화
void MainItem::initEffects()
{
	effects = {
	{ ItemId::HealthPortion, std::bind(&MainItem::HealthPortionEffect, this) },
	{ ItemId::BigHealthPortion, std::bind(&MainItem::BigHealthPortionEffect , this) },
	{ ItemId::PowerPortion, std::bind(&MainItem::PowerPortionEffect , this) },
	{ ItemId::BigPowerPortion, std::bind(&MainItem::BigPowerPortionEffect , this) },
	{ ItemId::Potion4, std::bind(&MainItem::Potion4Effect , this) },
	{ ItemId::Potion5, std::bind(&MainItem::Potion5Effect , this) },
	{ ItemId::Potion6, std::bind(&MainItem::Potion6Effect , this) },
	{ ItemId::Potion7, std::bind(&MainItem::Potion7Effect , this) },
	{ ItemId::FirePortion, std::bind(&MainItem::FirePortionEffect , this) },
	{ ItemId::BigFirePortion, std::bind(&MainItem::BigFirePortionEffect, this) },
	{ ItemId::Weapon1, std::bind(&MainItem::Weapon1Effect , this) },
	{ ItemId::Weapon2, std::bind(&MainItem::Weapon2Effect , this) },
	{ ItemId::Weapon3, std::bind(&MainItem::Weapon3Effect , this) },
	{ ItemId::Weapon4, std::bind(&MainItem::Weapon4Effect , this) },
	{ ItemId::Weapon5, std::bind(&MainItem::Weapon5Effect , this) },
	{ ItemId::Weapon6, std::bind(&MainItem::Weapon6Effect , this) },
	{ ItemId::Weapon7, std::bind(&MainItem::Weapon7Effect , this) },
	{ ItemId::Weapon8, std::bind(&MainItem::Weapon8Effect , this) },
	{ ItemId::Weapon9, std::bind(&MainItem::Weapon9Effect , this) },
	{ ItemId::Weapon10, std::bind(&MainItem::Weapon10Effect , this) },
	{ ItemId::Equipment1 , std::bind(&MainItem::Equipment1Effect, this) },
	{ ItemId::Equipment2, std::bind(&MainItem::Equipment2Effect, this) },
	{ ItemId::Equipment3, std::bind(&MainItem::Equipment3Effect, this) },
	{ ItemId::Equipment4, std::bind(&MainItem::Equipment4Effect, this) },
	{ ItemId::Equipment5, std::bind(&MainItem::Equipment5Effect, this) },
	{ ItemId::Equipment6, std::bind(&MainItem::Equipment6Effect, this) },
	{ ItemId::Equipment7, std::bind(&MainItem::Equipment7Effect, this) },
	{ ItemId::Equipment8, std::bind(&MainItem::Equipment8Effect, this) },
	{ ItemId::Equipment9, std::bind(&MainItem::Equipment9Effect, this) },
	{ ItemId::Equipment10, std::bind(&MainItem::Equipment10Effect , this) } };
	removeEffects =
	{
		{ ItemId::Weapon1, std::bind(&MainItem::RemoveWeapon1Effect , this) },
		{ ItemId::Weapon2, std::bind(&MainItem::RemoveWeapon2Effect , this) },
		{ ItemId::Weapon3, std::bind(&MainItem::RemoveWeapon3Effect , this) },
		{ ItemId::Weapon4, std::bind(&MainItem::RemoveWeapon4Effect , this) },
		{ ItemId::Weapon5, std::bind(&MainItem::RemoveWeapon5Effect , this) },
		{ ItemId::Weapon6, std::bind(&MainItem::RemoveWeapon6Effect , this) },
		{ ItemId::Weapon7, std::bind(&MainItem::RemoveWeapon7Effect , this) },
		{ ItemId::Weapon8, std::bind(&MainItem::RemoveWeapon8Effect , this) },
		{ ItemId::Weapon9, std::bind(&MainItem::RemoveWeapon9Effect , this) },
		{ ItemId::Weapon10, std::bind(&MainItem::RemoveWeapon10Effect , this) },
		{ ItemId::Equipment1, std::bind(&MainItem::RemoveEquipment1Effect, this) },
		{ ItemId::Equipment2, std::bind(&MainItem::RemoveEquipment2Effect, this) },
		{ ItemId::Equipment3, std::bind(&MainItem::RemoveEquipment3Effect, this) },
		{ ItemId::Equipment4, std::bind(&MainItem::RemoveEquipment4Effect, this) },
		{ ItemId::Equipment5, std::bind(&MainItem::RemoveEquipment5Effect, this) },
		{ ItemId::Equipment6, std::bind(&MainItem::RemoveEquipment6Effect, this) },
		{ ItemId::Equipment7, std::bind(&MainItem::RemoveEquipment7Effect, this) },
		{ ItemId::Equipment8, std::bind(&MainItem::RemoveEquipment8Effect, this) },
		{ ItemId::Equipment9, std::bind(&MainItem::RemoveEquipment9Effect, this) },
		{ ItemId::Equipment10, std::bind(&MainItem::RemoveEquipment10Effect , this) }
	};
}
// 장비 장착 함수
void MainItem::ItemTypeEffect(ItemId id) {
	if (ItemId::BigFirePortion < id)
	{
		applyEffect(id);
	}
	else if (std::find(equippedItems.begin(), equippedItems.end(), id) == equippedItems.end()) {
		equippedItems.push_back(id); // 중복 장착 방지
		applyEffect(id);             // 장비 효과 적용
	}
	else {
		std::cout << "Item is already equipped.\n";
	}
}
// 장비 해제 함수
void MainItem::UnItemTypeEffect(ItemId id) {
	auto it = std::find(equippedItems.begin(), equippedItems.end(), id);
	if (it != equippedItems.end()) {
		RemoveEffect(id);            // 장비 효과 제거
		equippedItems.erase(it);         // 목록에서 제거
	}
	else {
		std::cout << "Item is not equipped.\n";
	}
}
// 장착된 모든 장비의 효과를 일괄 적용
void MainItem::applyEquippedItems() {
	for (const auto& item : equippedItems) {
		applyEffect(item);
	}
}
void MainItem::applyEffect(ItemId test)
{
	auto effect = effects.find(test);  // ItemId에 해당하는 효과 함수 검색
	if (effect != effects.end()) {
		effect->second();  // 해당 함수 호출하여 아이템 효과 적용
	}
	else {
		std::cout << "No effect for this item.\n";
	}
}
void MainItem::RemoveEffect(ItemId test)
{
	auto effect = removeEffects.find(test);  // ItemId에 해당하는 효과 함수 검색
	if (effect != removeEffects.end()) {
		effect->second();  // 해당 함수 호출하여 아이템 효과 적용
	}
	else {
		std::cout << "No effect for this item.\n";
	}
}
// 아이템 효과 대충 만듬 나중에 밸런스 보면서 넣기
// 아이템 사용
#pragma region Potion Effects
void MainItem::HealthPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void MainItem::BigHealthPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void MainItem::PowerPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void MainItem::BigPowerPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void MainItem::Potion4Effect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void MainItem::Potion5Effect()
{ Ccore::GetInst()->Newbarrier(5); }
void MainItem::Potion6Effect()
{ Ccore::GetInst()->Newbarrier(5); }
void MainItem::Potion7Effect()
{ Ccore::GetInst()->Newbarrier(5); }
void MainItem::FirePortionEffect()
{ Ccore::GetInst()->Newbarrier(5); }
void MainItem::BigFirePortionEffect()
{ Ccore::GetInst()->Newbarrier(5); }
#pragma endregion
// 무기 장착
#pragma region Weapon Effects										
void MainItem::Weapon1Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon2Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon3Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon4Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon5Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon6Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon7Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon8Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon9Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void MainItem::Weapon10Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
#pragma endregion
// 장비 장착
#pragma region Equipment Effects		
void MainItem::Equipment1Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment2Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment3Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment4Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment5Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment6Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment7Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment8Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment9Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void MainItem::Equipment10Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
#pragma endregion
// 무기 해체
#pragma region Remove Weapon Effects		
void MainItem::RemoveWeapon1Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon2Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon3Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon4Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon5Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon6Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon7Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon8Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon9Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void MainItem::RemoveWeapon10Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
#pragma endregion
// 장비 해체
#pragma region Remove Equipment Effects	
void MainItem::RemoveEquipment1Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment2Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment3Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment4Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment5Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment6Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment7Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment8Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment9Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void MainItem::RemoveEquipment10Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
#pragma endregion

MainItem::MainItem()
	:ItemBag()
	, handleItem{}
	, effects{
	}
{}
MainItem::~MainItem()
{
	ItemBag.clear();
}
