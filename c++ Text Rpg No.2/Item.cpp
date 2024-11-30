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
	AddItem(ItemId::HealthPortion);
	handleItem = ItemBag.begin();
	OpenItemBag();
}
void MainItem::HandleItemErase(vector<NewItemInfo>::iterator& ItemId)
{
	if (ItemId != ItemBag.end())
	{
		ItemBag.erase(ItemId);
		handleItem = ItemBag.begin();
	}
}
void MainItem::OpenItemBag()
{
	auto it = ItemBag.begin();
	for (int i = 0; it != ItemBag.end(); ++it,++i)
	{
		string GetName = SelectName(it);
		std::cout << i + 1 << ". " << GetName << std::endl;
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

string MainItem::SelectName(const vector<NewItemInfo>::iterator& ItemId)
{
	NewItemInfo Hi = *ItemId;
	return (string)Hi.Name;
}
void MainItem::UseItemManuOpen()
{
	OpenItemBag();
	// ������ �� ���� ����� ���� ������
	std::cout << std::endl << "����Ͻ� �������� ������" << std::endl;
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
	ItemBag.emplace_back(ItemEncyclopedia::GetInst()->getNewItemInfo(item));
}
void MainItem::TotalequippedItems()
{
	if (!ViewEquippedItems())return;
	std::cout << "��� ��ü�Ͻðڽ��ϱ�?" << std::endl;
	if (!Yes_No()) return;
	std::cout << "���� ��ü�Ͻðڽ��ϱ�?" << std::endl;
	MoveEquipped(CinAuto());
	
}
bool MainItem::ViewEquippedItems()
{
	std::cout << "�������� ���" ;
	if (equippedItems.empty())
	{
		std::cout <<"�� �����ϴ�."<< std::endl;
		return false;
	}
	std::cout << std::endl;
	for (auto q : equippedItems)
	{
		int it = static_cast<int>(q);
		std::cout << it + 1<<". " << std::endl << ItemArr[it] << ", " << std::endl;
	}
	return true;
}
void MainItem::MoveEquipped(int choice)
{	// TODO: Choice�κ� 1�� ������ ���ϰ� ���� �κ��� �����ؾߵ�, ViewEquippedItems����
	choice -= 1;
	if (choice < 0|| choice >= equippedItems.size())
	{
		ErrorCode();
		return;
	}
	auto it = equippedItems.begin() + choice;
	equippedItems.erase(it); // ��� ��ü
	AddItem(convert(choice)); // ���������� ����
}
// ������ ȿ�� �ʱ�ȭ
void MainItem::initEffects()
{
	
}
// ��� ���� �Լ�
void MainItem::ItemTypeEffect(ItemId id) {
	if (ItemId::Weapon1 > id)
	{
		applyEffect(id);
	}
	else if (std::find(equippedItems.begin(), equippedItems.end(), id) == equippedItems.end())
	{	
		// NowCoding: 24.11.30 ������ ���� �����, ItemBag�� ����鼭 ��»��� ItemBag�� ��ü ������ ���� �ʿ䰡 �ֳ�?
		// �׳� ItemId�� ������ �ְ� ȿ�� ����ÿ� ���� ���ؼ� ȿ�� �����ϰ� �����ϰ� ItemBag�� �� ������ �ִ�����
		// üũ�ϸ� �Ǵ°� ������ ������ ��� bool ������ �׳� ��뿩�� üũ�ϰ� ���� �ϴ� ���� �Լ� ��ġ�鼭 ���� ��
		// ��� �����Լ� �� ���� ���� ������ �׳� �������̿��� ������
		// Main Item���� �ϰ� �׳� ���� ȿ�� ������ �������� ����
		// �ߺ� ���� ����
		//if()
		equippedItems.push_back(id); 
		applyEffect(id);             // ��� ȿ�� ����
	}
	else {
		std::cout << "Item is already equipped.\n";
	}
}
// ��� ���� �Լ�
void MainItem::UnItemTypeEffect(ItemId id) {
	auto it = std::find(equippedItems.begin(), equippedItems.end(), id);
	if (it != equippedItems.end()) {
		RemoveEffect(id);            // ��� ȿ�� ����
		equippedItems.erase(it);         // ��Ͽ��� ����
	}
	else {
		std::cout << "Item is not equipped.\n";
	}
}
// ������ ��� ����� ȿ���� �ϰ� ����
void MainItem::applyEquippedItems() {
	for (const auto& item : equippedItems) {
		applyEffect(item);
	}
}
void MainItem::applyEffect(ItemId test)
{
	ItemEncyclopedia::GetInst()->getNewItemInfo(test).effects();
}
void MainItem::RemoveEffect(ItemId test)
{
	if (test < ItemId::Weapon1) 
	{
		std::cout << "��� item�� Ż���Ҽ� �����ϴ�." << std::endl;
		return;
	}
	 // ItemId�� �ش��ϴ� ȿ�� �Լ� �˻�
	ItemEncyclopedia::GetInst()->getNewItemInfo(test).removeEffects();
	//�ش� �Լ� ȣ���Ͽ� ������ ȿ�� ����
}
// ������ ȿ�� ���� ���� ���߿� �뷱�� ���鼭 �ֱ�
// ������ ���
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
// ���� ����
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
// ��� ����
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
// ���� ��ü
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
// ��� ��ü
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
	case ItemId::Potion5:			return [this]() { this->Potion4Effect() ;			};
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
		k = (i % 10) / 2; // ������ ��� ���߱�
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