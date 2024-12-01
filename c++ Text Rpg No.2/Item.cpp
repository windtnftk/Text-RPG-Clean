#include "pch.h"
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
void MainItem::OpenItemBag()
{
	auto it = ItemBag.begin();
	for (int i = 0; it != ItemBag.end(); ++it,++i)
	{
		string GetName = ItemEncyclopedia::GetInst()->ItemName(*it);
		std::cout << i << ". " << GetName << std::endl;
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
void MainItem::UseItemManuOpen()
{
	OpenItemBag();
	// 아이템 을 고르고 사용을 할지 정하자
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
}
void MainItem::AddItem(ItemId item)
{
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
}
void MainItem::TotalequippedItems()
{
	if (!ViewEquippedItems())return;
	auto check = true;
	while (!check)
	{
		std::cout << "장비를 해체하시겠습니까?" << std::endl;
		if (!Yes_No()) return;
		std::cout << "어떤장비를 해체하시겠습니까?" << std::endl;
		check = MoveEquipped();
	}
	
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
	
	std::cout << "장착중인 장비" << std::endl; ;
	if (!EquipmentCheck())
	{
		std::cout <<"가 없습니다."<< std::endl;
		return false;
	}
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
}
// 아이템 효과 대충 만듬 나중에 밸런스 보면서 넣기
// 아이템 사용
#pragma region Potion Effects
void ItemEncyclopedia::HealthPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void ItemEncyclopedia::BigHealthPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void ItemEncyclopedia::PowerPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void ItemEncyclopedia::BigPowerPortionEffect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void ItemEncyclopedia::Potion4Effect()
{ Ccore::GetInst()->LimitHealthUp(5); }
void ItemEncyclopedia::Potion5Effect()
{ Ccore::GetInst()->Newbarrier(5); }
void ItemEncyclopedia::Potion6Effect()
{ Ccore::GetInst()->Newbarrier(5); }
void ItemEncyclopedia::Potion7Effect()
{ Ccore::GetInst()->Newbarrier(5); }
void ItemEncyclopedia::FirePortionEffect()
{ Ccore::GetInst()->Newbarrier(5); }
void ItemEncyclopedia::BigFirePortionEffect()
{ Ccore::GetInst()->Newbarrier(5); }
#pragma endregion
// 무기 장착
#pragma region Weapon Effects										
void ItemEncyclopedia::Weapon1Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon2Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon3Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon4Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon5Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon6Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon7Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon8Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon9Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
void ItemEncyclopedia::Weapon10Effect()
{ Ccore::GetInst()->AddPowerUp(5); }
#pragma endregion
// 장비 장착
#pragma region Equipment Effects		
void ItemEncyclopedia::Equipment1Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment2Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment3Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment4Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment5Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment6Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment7Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment8Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment9Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
void ItemEncyclopedia::Equipment10Effect()
{ Ccore::GetInst()->AddDefenseUp(5); }
#pragma endregion
// 무기 해체
#pragma region Remove Weapon Effects		
void ItemEncyclopedia::RemoveWeapon1Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon2Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon3Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon4Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon5Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon6Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon7Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon8Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon9Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
void ItemEncyclopedia::RemoveWeapon10Effect()
{ Ccore::GetInst()->RemovePowerUp(5); }
#pragma endregion
// 장비 해체
#pragma region Remove Equipment Effects	
void ItemEncyclopedia::RemoveEquipment1Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment2Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment3Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment4Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment5Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment6Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment7Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment8Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment9Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
void ItemEncyclopedia::RemoveEquipment10Effect()
{ Ccore::GetInst()->RemoveDefenseUp(5); }
#pragma endregion

std::function<void()> ItemEncyclopedia::getEffectFunction(ItemId id) {
	switch (id) {
	case ItemId::HealthPortion:		return [this]() { this->HealthPortionEffect();		};
	case ItemId::BigHealthPortion:	return [this]() { this->BigHealthPortionEffect();	};
	case ItemId::PowerPortion:		return [this]() { this->PowerPortionEffect() ;		};
	case ItemId::BigPowerPortion:	return [this]() { this->BigPowerPortionEffect() ;	};
	case ItemId::Potion4:			return [this]() { this->Potion4Effect() ;			};
	case ItemId::Potion5:			return [this]() { this->Potion5Effect() ;			};
	case ItemId::Potion6:			return [this]() { this->Potion6Effect();			};
	case ItemId::Potion7:			return [this]() { this->Potion7Effect();			};
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

ItemEncyclopedia::ItemEncyclopedia()
	:itemData{}
{
	for (int i = 0, k = 0; i < static_cast<int>(ItemId::End); ++i)
	{
		k = (i % 10) / 2; // 아이템 레어도 맞추기
		ItemId id = Id_Convert(i);
		itemData[id] = {
			ItemArr[i],
			Rarity_Convert(k),
			getEffectFunction(id),
			getRemoveEffectFunction(id),false
		};
	}
}

ItemEncyclopedia::~ItemEncyclopedia()
{
}
MainItem::MainItem()
	:ItemBag{}
	, handleItem{}
	, equippedItems{}
{
}
MainItem::~MainItem()
{
	ItemBag.clear();
}