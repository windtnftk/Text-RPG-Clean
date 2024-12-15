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
		//item�� �������� 3���� �߰� �ϰ� ������
		// �ϴ� 5,2,6 �̷������� ������ �õ尪 �־��

		for (int i = 0; i < (int)ItemId::End; ++i)
		{
			NewItemInfo NewItem = { static_cast<ItemId>(i),ItemArr[i]};
			ItemBag.push_back(NewItem);
		}

		std::random_device rd;
		std::mt19937 gen(rd()); // Mersenne Twister �˰����� ����ϴ� ���� ����
		// ���� �������� ������ ���� ���� (0 �̻� 99 ����)
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
void MainItem::OpenItemBag()
{
	int count = 0;
	for (auto q : ItemBag)
	{
		std::cout << count++ << ". " << ItemName(q.first) << ", ����: " << q.second << std::endl;
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
	// ������ �� ���� ����� ���� ������
	std::cout << "������ ����Ͻðڽ��ϱ�?" << std::endl;
	if (!Yes_No()) return;
	std::cout << std::endl << "����Ͻ� �������� ������" << std::endl;
	ItemId_Use(ItemBagId_to_cinAuto());
}
void MainItem::ItemId_Use(ItemId id)
{
	// �Ҹ� �������ϰ��
	if (ItemTypeCheck(id)) UseItem(id); 
	// ��� �������ϰ��
	else equippedUse(id);
}
void MainItem::equippedUse(ItemId id)
{
	// ��� ����ϴ� �Լ���
	if (!ItemTypeCheck(id)) { std::cout << "��� �ƴմϴ�." << std::endl; return; }
	// ��� ã��
	auto it = ItemBag.find(id);
	// �ش� ���� ������ ���� ����
	if (it == ItemBag.end()) { std::cout << "������â�� ���� ��� �Դϴ�." << std::endl;  return; }
	// ������ 0�� ���� ��
	if (it->second <= 0) { std::cout << "��� ������ 0�� �����Դϴ�." << std::endl; return; }
	// ��� �߰� �����ÿ��� �����۹鿡�� ������ ���� �� ȿ������
	if (!AddequippedItems(id)) { std::cout << "���â�� ���� ��� �ֽ��ϴ�." << std::endl; return; }
	// ������ ���� ���̰� ������ ���ȿ�� ����, ������ ���� ������ �ƿ� ����
	--it->second; ItemEffect(id); if (it->second <= 0)
	{
		ItemBag.erase(it); std::cout << "�ش� ��� �� ����߽��ϴ�." << std::endl;
	}
	std::cout << "��� ���� �Ϸ�." << std::endl;
}
void MainItem::UseItem(ItemId id)
{
	// �Ҹ� �����۸� ����ϴ� �Լ���
	if (ItemTypeCheck(id)) { std::cout << "�Ҹ� �������� �ƴմϴ�." << std::endl; return; }
	// ������ ã��
	auto it = ItemBag.find(id);
	// �ش�������� ������ ���� ����
	if (it == ItemBag.end()) { std::cout << "������â�� ���� �Ҹ𼺾����� �Դϴ�." << std::endl;  return; }
	// ������ 0�� ���� ��
	if (it->second <= 0) { std::cout << "������ ������ 0�� �����Դϴ�." << std::endl; return; }
	// ������ ���� ���̰� ������ ���ȿ�� ����, ������ ���� ������ �ƿ� ����
	--it->second; ItemEffect(id); if (it->second <= 0)
	{ ItemBag.erase(it); std::cout << "�ش� �������� �� ����߽��ϴ�." << std::endl; }
}
ItemId MainItem::ItemBagId_to_cinAuto()
{
	auto it = ItemBag.begin();
	int choice = CinAuto();
	// std::advance�� �ݺ��ڸ� �̵�
	return std::next(it, choice)->first;
}
ItemId MainItem::EquippedId_to_cinAuto()
{
	auto it = equippedItems.begin();
	auto id = std::next(it, CinAuto()); // ���� ����� ���� �̵�
	if (id == equippedItems.end()) return ItemId::End; // �߸��� �� �Է½� ��ȯ�� End
	return *id;
}
bool MainItem::ItemTypeCheck(ItemId id)
{
	if (ItemId::End == id) { std::cout << "�߸��� Id�� �Դϴ�." << std::endl; return false; }
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
			std::cout << "���� type�� ��� �ֽ��ϴ�." << std::endl;
			return false;
		}
	}
	return true;
}
void MainItem::TotalequippedItems()
{
	if (!ViewEquippedItems())return;
	std::cout << "��� ��ü�Ͻðڽ��ϱ�?" << std::endl;
	if (!Yes_No()) return;
	std::cout << "���� ��ü�Ͻðڽ��ϱ�?" << std::endl;
	MoveEquipped(EquippedId_to_cinAuto());
}
bool MainItem::AddequippedItems(ItemId id)
{
	if (!LikeItemtypeCheck(id)) return false; // ���� Ÿ���� ��� �����Ϸ��Ұ�� false
	return equippedItems.insert(id).second;
}
bool MainItem::ViewEquippedItems()
{
	std::cout << "�������� ���";
	if (equippedItems.empty())
	{
		std::cout << "�� �����ϴ�." << std::endl;
		return false;
	}
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
	// ��� �����۸� ����ϴ� �Լ���
	if (!ItemTypeCheck(id)) { std::cout << "�Ҹ� �������Դϴ�." << std::endl; return; }
	// ������ ã��
	auto it = equippedItems.find(id);
	// �ش�������� ������ ���� ����
	if (it == equippedItems.end()) { std::cout << "���â�� ���� �������Դϴ�." << std::endl;  return; }
	// ������ ����ȿ�� ����, ������ ���� ������ �ƿ� ����
	RemoveItemEffect(id);
	AddItem(id);  std::cout << "��� Ż���Ϸ�Ǿ����ϴ�." << std::endl;
}
// ������ ȿ�� ���� ���� ���߿� �뷱�� ���鼭 �ֱ�
// ������ ���
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
// ���� ����
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
// ��� ����
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
// ���� ��ü
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
// ��� ��ü
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
	case ItemId::PowerPortion:		return [this]() { this->PowerPortionEffect();		};
	case ItemId::BigPowerPortion:	return [this]() { this->BigPowerPortionEffect();	};
	case ItemId::Potion4:			return [this]() { this->Potion4Effect();			};
	case ItemId::Potion5:			return [this]() { this->Potion4Effect();			};
	case ItemId::Potion6:			return [this]() { this->Potion4Effect();			};
	case ItemId::Potion7:			return [this]() { this->Potion5Effect();			};
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
	default: return []() { std::cout << "item ��ȣ�� �߸��Ǿ����ϴ�." << std::endl; };
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
	default: return []() { std::cout << "item ��ȣ�� �߸��Ǿ����ϴ�." << std::endl; };
	}
}

ItemEncyclopedia::ItemEncyclopedia()
	:itemData{}
{
	for (int i = 0, k = 0; i < static_cast<int>(ItemId::End); ++i)
	{
		ItemType it;
		k = (i % 10) / 2; // ������ ��� ���߱�
		ItemId id = Id_Convert(i);
		if (id < ItemId::Weapon1)
		{
			it = ItemType::CONSUMABLE;
		}
		else if (id < ItemId::Equipment1)
		{
			it = ItemType::WEAPON;
		}
		else
		{
			it = ItemType::EQUIPMENT;
		}
		itemData[id] = {
			ItemArr[i],
			Rarity_Convert(k),
			it,
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
	, equippedItems{}
{

}
MainItem::~MainItem()
{
	ItemBag.clear();
}