#include "pch.h"
#include <unordered_set>
//#include "Item.h"
//#include "Ccore.h"

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
			NewItemInfo NewItem = { static_cast<ItemId>(i),ItemArr[i]};
			ItemBag.push_back(NewItem);
		}

		std::random_device rd;
		std::mt19937 gen(rd()); // Mersenne Twister 알고리즘을 사용하는 엔진 생성
		// 균일 분포에서 랜덤한 정수 생성 (0 이상 99 이하)
		std::uniform_int_distribution<int> distribution(0, 99);
		for (int i = 0; i < 9; ++i)
		{
			int rendom = distribution(gen) % 10;
			NewItemInfo NewItem = { static_cast<ItemId>(rendom),ItemArr[rendom] };
			ItemBag.push_back(NewItem);
		}
		*/

	AddItem(ItemId::Weapon1);
	AddItem(ItemId::Equipment1);
<<<<<<< HEAD
	AddItem(ItemId::HealthPortion);
	handleItem = ItemBag.end();
	OpenItemBag();
}
void MainItem::HandleItemErase(vector<ItemId>::iterator& ItemId)
{
	if (ItemId != ItemBag.end())
	{
		ItemBag.erase(ItemId);
		//handleItem = ItemBag.begin();
	}
}
=======
	AddItem(ItemId::HealthPortion, 3);
	//handleItem = ItemBag.begin();
	OpenItemBag();
}

//void MainItem::HandleItemErase(vector<NewItemInfo>::iterator& ItemId)
//{
//	if (ItemId != ItemBag.end())
//	{
//		ItemBag.erase(ItemId);
//		handleItem = ItemBag.begin();
//	}
//}
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
void MainItem::OpenItemBag()
{
	int count = 0;
	for (auto q : ItemBag)
	{
<<<<<<< HEAD
		string GetName = ItemEncyclopedia::GetInst()->ItemName(*it);
		std::cout << i << ". " << GetName << std::endl;
=======
		std::cout << count++ << ". " << ItemName(q.first) << ", 개수: " << q.second << std::endl;
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
	}
}

//ItemId MainItem::SelectId(const vector<NewItemInfo>::iterator& ItemId)
//{
//	if (ItemId == ItemBag.end())
//	{
//		std::cout << "Get Id fale" << std::endl;
//		return ItemId::End;
//	}
//	else
//	{
//		return ItemId->Name;
//	}}
<<<<<<< HEAD
=======


>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
void MainItem::UseItemManuOpen()
{
	OpenItemBag();
	// 아이템 을 고르고 사용을 할지 정하자
<<<<<<< HEAD
	std::cout << std::endl << "사용,장착 하실 아이템을 고르세요" << std::endl;
	int choice = CinAuto();
	if (0 == choice || choice > ItemBag.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ErrorCode();
		return;
	}
	handleAuto(choice);
	UsingItem();
=======
	std::cout << "아이템 사용하시겠습니까?" << std::endl;
	if (!Yes_No()) return;
	std::cout << std::endl << "사용하실 아이템을 고르세요" << std::endl;
	ItemId_Use(ItemBagId_to_cinAuto());
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
}
void MainItem::ItemId_Use(ItemId id)
{
<<<<<<< HEAD
	ItemBag.push_back(item);
}
void MainItem::DeleteItem()
{
	HandleItemErase(handleItem);
}
void MainItem::UsingItem()
{
	if (ItemEffect(*handleItem))
	{
		DeleteItem();
	}
=======
	// 소모성 아이템일경우
	if (ItemTypeCheck(id)) UseItem(id); 
	// 장비 아이템일경우
	else equippedUse(id);
}
void MainItem::equippedUse(ItemId id)
{
	// 장비만 사용하는 함수임
	if (!ItemTypeCheck(id)) { std::cout << "장비가 아닙니다." << std::endl; return; }
	// 장비 찾기
	auto it = ItemBag.find(id);
	// 해당 장비는 가지고 있지 않음
	if (it == ItemBag.end()) { std::cout << "아이템창에 없는 장비 입니다." << std::endl;  return; }
	// 개수가 0개 이하 임
	if (it->second <= 0) { std::cout << "장비 개수가 0개 이하입니다." << std::endl; return; }
	// 장비 추가 성공시에만 아이템백에서 아이템 제거 및 효과적용
	if (!AddequippedItems(id)) { std::cout << "장비창에 같은 장비가 있습니다." << std::endl; return; }
	// 아이템 숫자 줄이고 아이템 사용효과 빌동, 아이템 개수 적으면 아예 삭제
	--it->second; ItemEffect(id); if (it->second <= 0)
	{
		ItemBag.erase(it); std::cout << "해당 장비를 다 사용했습니다." << std::endl;
	}
	std::cout << "장비 장착 완료." << std::endl;
}
void MainItem::UseItem(ItemId id)
{
	// 소모성 아이템만 사용하는 함수임
	if (ItemTypeCheck(id)) { std::cout << "소모성 아이템이 아닙니다." << std::endl; return; }
	// 아이템 찾기
	auto it = ItemBag.find(id);
	// 해당아이템은 가지고 있지 않음
	if (it == ItemBag.end()) { std::cout << "아이템창에 없는 소모성아이템 입니다." << std::endl;  return; }
	// 개수가 0개 이하 임
	if (it->second <= 0) { std::cout << "아이템 개수가 0개 이하입니다." << std::endl; return; }
	// 아이템 숫자 줄이고 아이템 사용효과 빌동, 아이템 개수 적으면 아예 삭제
	--it->second; ItemEffect(id); if (it->second <= 0)
	{ ItemBag.erase(it); std::cout << "해당 아이템을 다 사용했습니다." << std::endl; }
}
ItemId MainItem::ItemBagId_to_cinAuto()
{
	auto it = ItemBag.begin();
	int choice = CinAuto();
	// std::advance로 반복자를 이동
	return std::next(it, choice)->first;
}
ItemId MainItem::EquippedId_to_cinAuto()
{
	auto it = equippedItems.begin();
	auto id = std::next(it, CinAuto()); // 범위 계산을 위한 이동
	if (id == equippedItems.end()) return ItemId::End; // 잘못된 값 입력시 반환값 End
	return *id;
}
bool MainItem::ItemTypeCheck(ItemId id)
{
	if (ItemId::End == id) { std::cout << "잘못된 Id값 입니다." << std::endl; return false; }
	return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Type == ItemType::CONSUMABLE;
}
void MainItem::AddItem(ItemId item) {
	ItemBag[item]++;
}
void MainItem::AddItem(ItemId item, int NUMBER) {
	ItemBag[item] += NUMBER;
}
bool MainItem::LikeItemtypeCheck(ItemId id)
{
	for (auto q : equippedItems)
	{
		if (Itemtype(q) == Itemtype(id))
		{
			std::cout << "같은 type의 장비가 있습니다." << std::endl;
			return false;
		}
	}
	return true;
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
}
void MainItem::TotalequippedItems()
{
	if (!ViewEquippedItems())return;
<<<<<<< HEAD
	auto check = true;
	while (!check)
	{
		std::cout << "장비를 해체하시겠습니까?" << std::endl;
		if (!Yes_No()) return;
		std::cout << "어떤장비를 해체하시겠습니까?" << std::endl;
		check = MoveEquipped();
	}
	
=======
	std::cout << "장비를 해체하시겠습니까?" << std::endl;
	if (!Yes_No()) return;
	std::cout << "어떤장비를 해체하시겠습니까?" << std::endl;
	MoveEquipped(EquippedId_to_cinAuto());
}
bool MainItem::AddequippedItems(ItemId id)
{
	if (!LikeItemtypeCheck(id)) return false; // 같은 타입의 장비를 장착하려할경우 false
	return equippedItems.insert(id).second;
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
}
void MainItem::DeleteItemManuOpen()
{
	OpenItemBag();
	// 아이템 을 고르고 사용을 할지 정하자
	std::cout << std::endl << "버릴 아이템을 고르세요" << std::endl;
	int choice = CinAuto();
	if (0 == choice || choice > ItemBag.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ErrorCode();
		return;
	}
	handleAuto(choice);
	DeleteItem();
}
bool MainItem::ViewEquippedItems()
{
<<<<<<< HEAD
	
	std::cout << "장착중인 장비" << std::endl; ;
	if (!EquipmentCheck())
=======
	std::cout << "장착중인 장비";
	if (equippedItems.empty())
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
	{
		std::cout << "가 없습니다." << std::endl;
		return false;
	}
<<<<<<< HEAD
	return true;
}
bool MainItem::EquipmentCheck()
{
	bool check = false;
	for (const auto q : ItemBag)
	{
		if (EquipentCheckAuto(q))
		{
			check = true;
			std::cout << ItemEncyclopedia::GetInst()->ItemName(q) << ", " << std::endl;
		}
	}
	return check;
}
bool MainItem::MoveEquipped()
{	// TODO: Choice부분 1을 강제로 더하고 뺴는 부분을 수정해야됨, ViewEquippedItems포함 그냥 0번아이템이라 부르자
	auto it = ItemBag.begin() + CinAuto();
	if (it == ItemBag.end()) // 아이템가방의 위치 선택값이 지정값을 벗어났을 경우
	{
		ErrorCode();
		return false;
	}
	RemoveEffect(*it);
	//AddItem(convert(choice)); // 아이템으로 복귀
	return true;
}
// 장비 해제 함수
void MainItem::UnItemTypeEffect(ItemId id) {
	for (const auto q : ItemBag)
	{
		RemoveEffect(q);
	}
}
// 장착된 모든 장비의 효과를 일괄 적용
void MainItem::BagEffect()
{
	for (const auto q : ItemBag)
	{
		//사용 아이템인지 확인 하고 아닐경우 아이템 사용
		if(!ItemEncyclopedia::GetInst()->ItemCheck(q)) applyEffect(q); 
	}
}
bool MainItem::ItemEffect(ItemId Id)
{
	if (!ItemEncyclopedia::GetInst()->ItemCheck(Id)) return false; // 소모성 아이템이 아닐경우 바로 리턴
	ItemEncyclopedia::GetInst()->E_Apply(Id);
}
void MainItem::applyEffect(ItemId test)
{
	ItemEncyclopedia::GetInst()->E_Apply(test);
	ItemEncyclopedia::GetInst()->E_ON(test);
}
void MainItem::RemoveEffect(ItemId test)
{
	ItemEncyclopedia::GetInst()->ER_Apply(test);
	ItemEncyclopedia::GetInst()->E_Off(test);
=======
	std::cout << std::endl;
	int count = 0;
	for (auto q : equippedItems)
	{
		std::cout << count++ << ". " << ItemName(q) << std::endl;
	}
	return true;
}
void MainItem::MoveEquipped(ItemId id)
{
	// 장비 아이템만 사용하는 함수임
	if (!ItemTypeCheck(id)) { std::cout << "소모성 아이템입니다." << std::endl; return; }
	// 아이템 찾기
	auto it = equippedItems.find(id);
	// 해당아이템은 가지고 있지 않음
	if (it == equippedItems.end()) { std::cout << "장비창에 없는 아이템입니다." << std::endl;  return; }
	// 아이템 삭제효과 빌동, 아이템 개수 적으면 아예 삭제
	RemoveItemEffect(id);
	AddItem(id);  std::cout << "장비 탈착완료되었습니다." << std::endl;
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
}
// 아이템 효과 대충 만듬 나중에 밸런스 보면서 넣기
// 아이템 사용
#pragma region Potion Effects
void ItemEncyclopedia::HealthPortionEffect()
{
	Ccore::GetInst()->LimitHealthUp(5);
}
void ItemEncyclopedia::BigHealthPortionEffect()
{
	Ccore::GetInst()->LimitHealthUp(5);
}
void ItemEncyclopedia::PowerPortionEffect()
{
	Ccore::GetInst()->LimitHealthUp(5);
}
void ItemEncyclopedia::BigPowerPortionEffect()
{
	Ccore::GetInst()->LimitHealthUp(5);
}
void ItemEncyclopedia::Potion4Effect()
{
	Ccore::GetInst()->LimitHealthUp(5);
}
void ItemEncyclopedia::Potion5Effect()
{
	Ccore::GetInst()->Newbarrier(5);
}
void ItemEncyclopedia::Potion6Effect()
{
	Ccore::GetInst()->Newbarrier(5);
}
void ItemEncyclopedia::Potion7Effect()
{
	Ccore::GetInst()->Newbarrier(5);
}
void ItemEncyclopedia::FirePortionEffect()
{
	Ccore::GetInst()->Newbarrier(5);
}
void ItemEncyclopedia::BigFirePortionEffect()
{
	Ccore::GetInst()->Newbarrier(5);
}
#pragma endregion
// 무기 장착
#pragma region Weapon Effects										
void ItemEncyclopedia::Weapon1Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon2Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon3Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon4Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon5Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon6Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon7Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon8Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon9Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
void ItemEncyclopedia::Weapon10Effect()
{
	Ccore::GetInst()->AddPowerUp(5);
}
#pragma endregion
// 장비 장착
#pragma region Equipment Effects		
void ItemEncyclopedia::Equipment1Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment2Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment3Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment4Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment5Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment6Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment7Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment8Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment9Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
void ItemEncyclopedia::Equipment10Effect()
{
	Ccore::GetInst()->AddDefenseUp(5);
}
#pragma endregion
// 무기 해체
#pragma region Remove Weapon Effects		
void ItemEncyclopedia::RemoveWeapon1Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon2Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon3Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon4Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon5Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon6Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon7Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon8Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon9Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
void ItemEncyclopedia::RemoveWeapon10Effect()
{
	Ccore::GetInst()->RemovePowerUp(5);
}
#pragma endregion
// 장비 해체
#pragma region Remove Equipment Effects	
void ItemEncyclopedia::RemoveEquipment1Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment2Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment3Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment4Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment5Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment6Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment7Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment8Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment9Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
void ItemEncyclopedia::RemoveEquipment10Effect()
{
	Ccore::GetInst()->RemoveDefenseUp(5);
}
#pragma endregion

std::function<void()> ItemEncyclopedia::getEffectFunction(ItemId id) {
	switch (id) {
	case ItemId::HealthPortion:		return [this]() { this->HealthPortionEffect();		};
	case ItemId::BigHealthPortion:	return [this]() { this->BigHealthPortionEffect();	};
<<<<<<< HEAD
	case ItemId::PowerPortion:		return [this]() { this->PowerPortionEffect() ;		};
	case ItemId::BigPowerPortion:	return [this]() { this->BigPowerPortionEffect() ;	};
	case ItemId::Potion4:			return [this]() { this->Potion4Effect() ;			};
	case ItemId::Potion5:			return [this]() { this->Potion5Effect() ;			};
	case ItemId::Potion6:			return [this]() { this->Potion6Effect();			};
	case ItemId::Potion7:			return [this]() { this->Potion7Effect();			};
=======
	case ItemId::PowerPortion:		return [this]() { this->PowerPortionEffect();		};
	case ItemId::BigPowerPortion:	return [this]() { this->BigPowerPortionEffect();	};
	case ItemId::Potion4:			return [this]() { this->Potion4Effect();			};
	case ItemId::Potion5:			return [this]() { this->Potion4Effect();			};
	case ItemId::Potion6:			return [this]() { this->Potion4Effect();			};
	case ItemId::Potion7:			return [this]() { this->Potion5Effect();			};
>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
	case ItemId::FirePortion:		return [this]() { this->FirePortionEffect();		};
	case ItemId::BigFirePortion:	return [this]() { this->BigFirePortionEffect();		};
	case ItemId::Weapon1:			return [this]() { this->Weapon1Effect();			};
	case ItemId::Weapon2:			return [this]() { this->Weapon2Effect();			};
	case ItemId::Weapon3:			return [this]() { this->Weapon3Effect();			};
	case ItemId::Weapon4:			return [this]() { this->Weapon4Effect();			};
	case ItemId::Weapon5:			return [this]() { this->Weapon5Effect();			};
	case ItemId::Weapon6:			return [this]() { this->Weapon6Effect();			};
	case ItemId::Weapon7:			return [this]() { this->Weapon7Effect();			};
	case ItemId::Weapon8:			return [this]() { this->Weapon8Effect();			};
	case ItemId::Weapon9:			return [this]() { this->Weapon9Effect();			};
	case ItemId::Weapon10:			return [this]() { this->Weapon10Effect();			};
	case ItemId::Equipment1:		return [this]() { this->Equipment1Effect();			};
	case ItemId::Equipment2:		return [this]() { this->Equipment2Effect();			};
	case ItemId::Equipment3:		return [this]() { this->Equipment3Effect();			};
	case ItemId::Equipment4:		return [this]() { this->Equipment4Effect();			};
	case ItemId::Equipment5:		return [this]() { this->Equipment5Effect();			};
	case ItemId::Equipment6:		return [this]() { this->Equipment6Effect();			};
	case ItemId::Equipment7:		return [this]() { this->Equipment7Effect();			};
	case ItemId::Equipment8:		return [this]() { this->Equipment8Effect();			};
	case ItemId::Equipment9:		return [this]() { this->Equipment9Effect();			};
	case ItemId::Equipment10:		return [this]() { this->Equipment10Effect();		};
	default: return []() { std::cout << "item 번호가 잘못되었습니다." << std::endl; };
	}
}
std::function<void()> ItemEncyclopedia::getRemoveEffectFunction(ItemId id) {
	switch (id) {
	case ItemId::Weapon1:			return [this]() { this->RemoveWeapon1Effect();			};
	case ItemId::Weapon2:			return [this]() { this->RemoveWeapon2Effect();			};
	case ItemId::Weapon3:			return [this]() { this->RemoveWeapon3Effect();			};
	case ItemId::Weapon4:			return [this]() { this->RemoveWeapon4Effect();			};
	case ItemId::Weapon5:			return [this]() { this->RemoveWeapon5Effect();			};
	case ItemId::Weapon6:			return [this]() { this->RemoveWeapon6Effect();			};
	case ItemId::Weapon7:			return [this]() { this->RemoveWeapon7Effect();			};
	case ItemId::Weapon8:			return [this]() { this->RemoveWeapon8Effect();			};
	case ItemId::Weapon9:			return [this]() { this->RemoveWeapon9Effect();			};
	case ItemId::Weapon10:			return [this]() { this->RemoveWeapon10Effect();			};
	case ItemId::Equipment1:		return [this]() { this->RemoveEquipment1Effect();			};
	case ItemId::Equipment2:		return [this]() { this->RemoveEquipment2Effect();			};
	case ItemId::Equipment3:		return [this]() { this->RemoveEquipment3Effect();			};
	case ItemId::Equipment4:		return [this]() { this->RemoveEquipment4Effect();			};
	case ItemId::Equipment5:		return [this]() { this->RemoveEquipment5Effect();			};
	case ItemId::Equipment6:		return [this]() { this->RemoveEquipment6Effect();			};
	case ItemId::Equipment7:		return [this]() { this->RemoveEquipment7Effect();			};
	case ItemId::Equipment8:		return [this]() { this->RemoveEquipment8Effect();			};
	case ItemId::Equipment9:		return [this]() { this->RemoveEquipment9Effect();			};
	case ItemId::Equipment10:		return [this]() { this->RemoveEquipment10Effect();		};
	default: return []() { std::cout << "item 번호가 잘못되었습니다." << std::endl; };
	}
}
// 생성자
ItemEncyclopedia::ItemEncyclopedia()
	: itemData{} {
	for (int id = 0; id < static_cast<int>(ItemId::End); ++id) {
		// 0. 현재 반복문을 ItemId로 맞춤
		ItemId index = Id_Convert(id);

		// 1. 아이템 이름을 ItemArr에서 참조로 받아옴
		const string& Name = ItemArr[id]; // 복사 대신 참조 사용

		// 2. 아이템 레어도를 ItemId에 맞춰 조정
		int Raritynumber = (id % 10) / 2;
		ItemRarity Rarity = Rarity_Convert(Raritynumber);

		// 3. 아이템 레어도에 따라 아이템의 가치 변화
		int Rarity_to_Money = Raritynumber * 5;

		// 4. 아이템 타입별로 분류
		ItemType type;
		if (index < ItemId::Weapon1) {
			type = ItemType::CONSUMABLE;
		}
		else if (index < ItemId::Equipment1) {
			type = ItemType::WEAPON;
		}
		else {
			type = ItemType::EQUIPMENT;
		}

		// 5. 이동 연산자(std::move)로 복사 비용 제거
		itemData[index] = std::move(NewItemInfo{
			Name,                              // 참조된 아이템 이름
			Rarity,                            // 아이템 레어도 저장
			Rarity_to_Money,                   // 레어도에 따른 가치
			type,                              // 아이템 타입
			getEffectFunction(index),          // 효과 함수
			getRemoveEffectFunction(index),    // 제거 효과 함수
			false                              // 기타 정보
			});
	}
}


ItemEncyclopedia::~ItemEncyclopedia()
{
}
MainItem::MainItem()
	:ItemBag{}
	, equippedItems{}
{
<<<<<<< HEAD
=======

>>>>>>> ItemClass-�옣李⑹븘�씠�뀥-蹂��닔-�젣嫄곗옉�뾽-�쟾�솚
}
MainItem::~MainItem()
{
	ItemBag.clear();
}