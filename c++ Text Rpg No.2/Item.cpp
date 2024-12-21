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
		//itemÀ» ·£´ıÀ¸·Î 3°³¸¸ Ãß°¡ ÇÏ°í ½ÍÀºµ¥
		// ÀÏ´Ü 5,2,6 ÀÌ·±½ÄÀ¸·Î °íÁ¤µÈ ½Ãµå°ª ³Ö¾îº¸ÀÚ

		for (int i = 0; i < (int)ItemId::End; ++i)
		{
			NewItemInfo NewItem = { static_cast<ItemId>(i),ItemArr[i]};
			ItemBag.push_back(NewItem);
		}

		std::random_device rd;
		std::mt19937 gen(rd()); // Mersenne Twister ¾Ë°í¸®ÁòÀ» »ç¿ëÇÏ´Â ¿£Áø »ı¼º
		// ±ÕÀÏ ºĞÆ÷¿¡¼­ ·£´ıÇÑ Á¤¼ö »ı¼º (0 ÀÌ»ó 99 ÀÌÇÏ)
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
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
void MainItem::OpenItemBag()
{
	int count = 0;
	for (auto q : ItemBag)
	{
<<<<<<< HEAD
		string GetName = ItemEncyclopedia::GetInst()->ItemName(*it);
		std::cout << i << ". " << GetName << std::endl;
=======
		std::cout << count++ << ". " << ItemName(q.first) << ", °³¼ö: " << q.second << std::endl;
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
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


>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
void MainItem::UseItemManuOpen()
{
	OpenItemBag();
	// ¾ÆÀÌÅÛ À» °í¸£°í »ç¿ëÀ» ÇÒÁö Á¤ÇÏÀÚ
<<<<<<< HEAD
	std::cout << std::endl << "»ç¿ë,ÀåÂø ÇÏ½Ç ¾ÆÀÌÅÛÀ» °í¸£¼¼¿ä" << std::endl;
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
	std::cout << "¾ÆÀÌÅÛ »ç¿ëÇÏ½Ã°Ú½À´Ï±î?" << std::endl;
	if (!Yes_No()) return;
	std::cout << std::endl << "»ç¿ëÇÏ½Ç ¾ÆÀÌÅÛÀ» °í¸£¼¼¿ä" << std::endl;
	ItemId_Use(ItemBagId_to_cinAuto());
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
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
	// ¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÏ°æ¿ì
	if (ItemTypeCheck(id)) UseItem(id); 
	// Àåºñ ¾ÆÀÌÅÛÀÏ°æ¿ì
	else equippedUse(id);
}
void MainItem::equippedUse(ItemId id)
{
	// Àåºñ¸¸ »ç¿ëÇÏ´Â ÇÔ¼öÀÓ
	if (!ItemTypeCheck(id)) { std::cout << "Àåºñ°¡ ¾Æ´Õ´Ï´Ù." << std::endl; return; }
	// Àåºñ Ã£±â
	auto it = ItemBag.find(id);
	// ÇØ´ç Àåºñ´Â °¡Áö°í ÀÖÁö ¾ÊÀ½
	if (it == ItemBag.end()) { std::cout << "¾ÆÀÌÅÛÃ¢¿¡ ¾ø´Â Àåºñ ÀÔ´Ï´Ù." << std::endl;  return; }
	// °³¼ö°¡ 0°³ ÀÌÇÏ ÀÓ
	if (it->second <= 0) { std::cout << "Àåºñ °³¼ö°¡ 0°³ ÀÌÇÏÀÔ´Ï´Ù." << std::endl; return; }
	// Àåºñ Ãß°¡ ¼º°ø½Ã¿¡¸¸ ¾ÆÀÌÅÛ¹é¿¡¼­ ¾ÆÀÌÅÛ Á¦°Å ¹× È¿°úÀû¿ë
	if (!AddequippedItems(id)) { std::cout << "ÀåºñÃ¢¿¡ °°Àº Àåºñ°¡ ÀÖ½À´Ï´Ù." << std::endl; return; }
	// ¾ÆÀÌÅÛ ¼ıÀÚ ÁÙÀÌ°í ¾ÆÀÌÅÛ »ç¿ëÈ¿°ú ºôµ¿, ¾ÆÀÌÅÛ °³¼ö ÀûÀ¸¸é ¾Æ¿¹ »èÁ¦
	--it->second; ItemEffect(id); if (it->second <= 0)
	{
		ItemBag.erase(it); std::cout << "ÇØ´ç Àåºñ¸¦ ´Ù »ç¿ëÇß½À´Ï´Ù." << std::endl;
	}
	std::cout << "Àåºñ ÀåÂø ¿Ï·á." << std::endl;
}
void MainItem::UseItem(ItemId id)
{
	// ¼Ò¸ğ¼º ¾ÆÀÌÅÛ¸¸ »ç¿ëÇÏ´Â ÇÔ¼öÀÓ
	if (ItemTypeCheck(id)) { std::cout << "¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÌ ¾Æ´Õ´Ï´Ù." << std::endl; return; }
	// ¾ÆÀÌÅÛ Ã£±â
	auto it = ItemBag.find(id);
	// ÇØ´ç¾ÆÀÌÅÛÀº °¡Áö°í ÀÖÁö ¾ÊÀ½
	if (it == ItemBag.end()) { std::cout << "¾ÆÀÌÅÛÃ¢¿¡ ¾ø´Â ¼Ò¸ğ¼º¾ÆÀÌÅÛ ÀÔ´Ï´Ù." << std::endl;  return; }
	// °³¼ö°¡ 0°³ ÀÌÇÏ ÀÓ
	if (it->second <= 0) { std::cout << "¾ÆÀÌÅÛ °³¼ö°¡ 0°³ ÀÌÇÏÀÔ´Ï´Ù." << std::endl; return; }
	// ¾ÆÀÌÅÛ ¼ıÀÚ ÁÙÀÌ°í ¾ÆÀÌÅÛ »ç¿ëÈ¿°ú ºôµ¿, ¾ÆÀÌÅÛ °³¼ö ÀûÀ¸¸é ¾Æ¿¹ »èÁ¦
	--it->second; ItemEffect(id); if (it->second <= 0)
	{ ItemBag.erase(it); std::cout << "ÇØ´ç ¾ÆÀÌÅÛÀ» ´Ù »ç¿ëÇß½À´Ï´Ù." << std::endl; }
}
ItemId MainItem::ItemBagId_to_cinAuto()
{
	auto it = ItemBag.begin();
	int choice = CinAuto();
	// std::advance·Î ¹İº¹ÀÚ¸¦ ÀÌµ¿
	return std::next(it, choice)->first;
}
ItemId MainItem::EquippedId_to_cinAuto()
{
	auto it = equippedItems.begin();
	auto id = std::next(it, CinAuto()); // ¹üÀ§ °è»êÀ» À§ÇÑ ÀÌµ¿
	if (id == equippedItems.end()) return ItemId::End; // Àß¸øµÈ °ª ÀÔ·Â½Ã ¹İÈ¯°ª End
	return *id;
}
bool MainItem::ItemTypeCheck(ItemId id)
{
	if (ItemId::End == id) { std::cout << "Àß¸øµÈ Id°ª ÀÔ´Ï´Ù." << std::endl; return false; }
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
			std::cout << "°°Àº typeÀÇ Àåºñ°¡ ÀÖ½À´Ï´Ù." << std::endl;
			return false;
		}
	}
	return true;
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
}
void MainItem::TotalequippedItems()
{
	if (!ViewEquippedItems())return;
<<<<<<< HEAD
	auto check = true;
	while (!check)
	{
		std::cout << "Àåºñ¸¦ ÇØÃ¼ÇÏ½Ã°Ú½À´Ï±î?" << std::endl;
		if (!Yes_No()) return;
		std::cout << "¾î¶²Àåºñ¸¦ ÇØÃ¼ÇÏ½Ã°Ú½À´Ï±î?" << std::endl;
		check = MoveEquipped();
	}
	
=======
	std::cout << "Àåºñ¸¦ ÇØÃ¼ÇÏ½Ã°Ú½À´Ï±î?" << std::endl;
	if (!Yes_No()) return;
	std::cout << "¾î¶²Àåºñ¸¦ ÇØÃ¼ÇÏ½Ã°Ú½À´Ï±î?" << std::endl;
	MoveEquipped(EquippedId_to_cinAuto());
}
bool MainItem::AddequippedItems(ItemId id)
{
	if (!LikeItemtypeCheck(id)) return false; // °°Àº Å¸ÀÔÀÇ Àåºñ¸¦ ÀåÂøÇÏ·ÁÇÒ°æ¿ì false
	return equippedItems.insert(id).second;
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
}
void MainItem::DeleteItemManuOpen()
{
	OpenItemBag();
	// ¾ÆÀÌÅÛ À» °í¸£°í »ç¿ëÀ» ÇÒÁö Á¤ÇÏÀÚ
	std::cout << std::endl << "¹ö¸± ¾ÆÀÌÅÛÀ» °í¸£¼¼¿ä" << std::endl;
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
	
	std::cout << "ÀåÂøÁßÀÎ Àåºñ" << std::endl; ;
	if (!EquipmentCheck())
=======
	std::cout << "ÀåÂøÁßÀÎ Àåºñ";
	if (equippedItems.empty())
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
	{
		std::cout << "°¡ ¾ø½À´Ï´Ù." << std::endl;
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
{	// TODO: ChoiceºÎºĞ 1À» °­Á¦·Î ´õÇÏ°í •û´Â ºÎºĞÀ» ¼öÁ¤ÇØ¾ßµÊ, ViewEquippedItemsÆ÷ÇÔ ±×³É 0¹ø¾ÆÀÌÅÛÀÌ¶ó ºÎ¸£ÀÚ
	auto it = ItemBag.begin() + CinAuto();
	if (it == ItemBag.end()) // ¾ÆÀÌÅÛ°¡¹æÀÇ À§Ä¡ ¼±ÅÃ°ªÀÌ ÁöÁ¤°ªÀ» ¹ş¾î³µÀ» °æ¿ì
	{
		ErrorCode();
		return false;
	}
	RemoveEffect(*it);
	//AddItem(convert(choice)); // ¾ÆÀÌÅÛÀ¸·Î º¹±Í
	return true;
}
// Àåºñ ÇØÁ¦ ÇÔ¼ö
void MainItem::UnItemTypeEffect(ItemId id) {
	for (const auto q : ItemBag)
	{
		RemoveEffect(q);
	}
}
// ÀåÂøµÈ ¸ğµç ÀåºñÀÇ È¿°ú¸¦ ÀÏ°ı Àû¿ë
void MainItem::BagEffect()
{
	for (const auto q : ItemBag)
	{
		//»ç¿ë ¾ÆÀÌÅÛÀÎÁö È®ÀÎ ÇÏ°í ¾Æ´Ò°æ¿ì ¾ÆÀÌÅÛ »ç¿ë
		if(!ItemEncyclopedia::GetInst()->ItemCheck(q)) applyEffect(q); 
	}
}
bool MainItem::ItemEffect(ItemId Id)
{
	if (!ItemEncyclopedia::GetInst()->ItemCheck(Id)) return false; // ¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÌ ¾Æ´Ò°æ¿ì ¹Ù·Î ¸®ÅÏ
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
	// Àåºñ ¾ÆÀÌÅÛ¸¸ »ç¿ëÇÏ´Â ÇÔ¼öÀÓ
	if (!ItemTypeCheck(id)) { std::cout << "¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÔ´Ï´Ù." << std::endl; return; }
	// ¾ÆÀÌÅÛ Ã£±â
	auto it = equippedItems.find(id);
	// ÇØ´ç¾ÆÀÌÅÛÀº °¡Áö°í ÀÖÁö ¾ÊÀ½
	if (it == equippedItems.end()) { std::cout << "ÀåºñÃ¢¿¡ ¾ø´Â ¾ÆÀÌÅÛÀÔ´Ï´Ù." << std::endl;  return; }
	// ¾ÆÀÌÅÛ »èÁ¦È¿°ú ºôµ¿, ¾ÆÀÌÅÛ °³¼ö ÀûÀ¸¸é ¾Æ¿¹ »èÁ¦
	RemoveItemEffect(id);
	AddItem(id);  std::cout << "Àåºñ Å»Âø¿Ï·áµÇ¾ú½À´Ï´Ù." << std::endl;
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
}
// ¾ÆÀÌÅÛ È¿°ú ´ëÃæ ¸¸µë ³ªÁß¿¡ ¹ë·±½º º¸¸é¼­ ³Ö±â
// ¾ÆÀÌÅÛ »ç¿ë
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
// ¹«±â ÀåÂø
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
// Àåºñ ÀåÂø
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
// ¹«±â ÇØÃ¼
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
// Àåºñ ÇØÃ¼
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
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
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
	default: return []() { std::cout << "item ¹øÈ£°¡ Àß¸øµÇ¾ú½À´Ï´Ù." << std::endl; };
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
	default: return []() { std::cout << "item ¹øÈ£°¡ Àß¸øµÇ¾ú½À´Ï´Ù." << std::endl; };
	}
}
// »ı¼ºÀÚ
ItemEncyclopedia::ItemEncyclopedia()
	: itemData{} {
	for (int id = 0; id < static_cast<int>(ItemId::End); ++id) {
		// 0. ÇöÀç ¹İº¹¹®À» ItemId·Î ¸ÂÃã
		ItemId index = Id_Convert(id);

		// 1. ¾ÆÀÌÅÛ ÀÌ¸§À» ItemArr¿¡¼­ ÂüÁ¶·Î ¹Ş¾Æ¿È
		const string& Name = ItemArr[id]; // º¹»ç ´ë½Å ÂüÁ¶ »ç¿ë

		// 2. ¾ÆÀÌÅÛ ·¹¾îµµ¸¦ ItemId¿¡ ¸ÂÃç Á¶Á¤
		int Raritynumber = (id % 10) / 2;
		ItemRarity Rarity = Rarity_Convert(Raritynumber);

		// 3. ¾ÆÀÌÅÛ ·¹¾îµµ¿¡ µû¶ó ¾ÆÀÌÅÛÀÇ °¡Ä¡ º¯È­
		int Rarity_to_Money = Raritynumber * 5;

		// 4. ¾ÆÀÌÅÛ Å¸ÀÔº°·Î ºĞ·ù
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

		// 5. ÀÌµ¿ ¿¬»êÀÚ(std::move)·Î º¹»ç ºñ¿ë Á¦°Å
		itemData[index] = std::move(NewItemInfo{
			Name,                              // ÂüÁ¶µÈ ¾ÆÀÌÅÛ ÀÌ¸§
			Rarity,                            // ¾ÆÀÌÅÛ ·¹¾îµµ ÀúÀå
			Rarity_to_Money,                   // ·¹¾îµµ¿¡ µû¸¥ °¡Ä¡
			type,                              // ¾ÆÀÌÅÛ Å¸ÀÔ
			getEffectFunction(index),          // È¿°ú ÇÔ¼ö
			getRemoveEffectFunction(index),    // Á¦°Å È¿°ú ÇÔ¼ö
			false                              // ±âÅ¸ Á¤º¸
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

>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
}
MainItem::~MainItem()
{
	ItemBag.clear();
}