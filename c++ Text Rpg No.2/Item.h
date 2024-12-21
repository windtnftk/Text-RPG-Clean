#pragma once
#include <unordered_set>
enum class ItemId
{
	HealthPortion,
	BigHealthPortion,
	PowerPortion,
	BigPowerPortion,
	Potion4,
	Potion5,
	Potion6,
	Potion7,
	FirePortion,
	BigFirePortion,
	Weapon1 = 10,
	Weapon2,
	Weapon3,
	Weapon4,
	Weapon5,
	Weapon6,
	Weapon7,
	Weapon8,
	Weapon9,
	Weapon10,
	Equipment1 = 20,
	Equipment2,
	Equipment3,
	Equipment4,
	Equipment5,
	Equipment6,
	Equipment7,
	Equipment8,
	Equipment9,
	Equipment10,
	End = 30,
};
enum class ItemType {
	CONSUMABLE,  // ¼Ò¸ğ¼º ¾ÆÀÌÅÛ
	WEAPON,      // ¹«±â
	EQUIPMENT    // Àåºñ
};
enum ItemRarity {
	COMMON,      // ÀÏ¹İ ¾ÆÀÌÅÛ 1~2 ¹ø
	UNCOMMON,    // °í±Ş ¾ÆÀÌÅÛ 3~4 ¹ø
	RARE,        // Èñ±Í ¾ÆÀÌÅÛ 5~6 ¹ø
	EPIC,        // ¼­»ç ¾ÆÀÌÅÛ 7~8 ¹ø
	LEGENDARY    // Àü¼³ ¾ÆÀÌÅÛ 9~10 ¹ø
};
struct NewItemInfo
{
	string	Name; // ÀÌ¸§
	ItemRarity Rarity; // ·¹¾îµµ
	int			Money; // ¾ÆÀÌÅÛ °¡Ä¡
	ItemType	Type;	// ¾ÆÀÌÅÛ Å¸ÀÔ
	std::function<void()> effects;		// Âø¿ë½Ã È¿°ú
	std::function<void()> removeEffects;// Å»Âø½Ã È¿°ú
	bool E_Check = false;				// ÀåÂøµÇ¾î ÀÖ´ÂÁö Ã¼Å©, flase¸é »ç¿ëÇÏÁö ¾Ê°íÀÖ´Ù
};
class ItemEncyclopedia
{
	SINGLE(ItemEncyclopedia);
	
public:
	// ItemId ¹Ş¾Æ¼­ Å°´Â ÇÔ¼ö, ²ô´Â ÇÔ¼ö
	
	// ¾ÆÀÌÅÛ Id ¹ŞÀ¸¸é Itme ÀÌ¸§ Àü´Ş
	string ItemName(ItemId id)const
	{
		return itemData.at(id).Name;
	}
	// ¾ÆÀÌÅÛ Id ¹ŞÀ¸¸é ItemData Àü´Ş
	const NewItemInfo getNewItemInfo(ItemId id) const {
		return itemData.at(id);
	}
	// ItemId°ª À» È®ÀÎÈÄ ÇØ´ç Àåºñ¸¦ »ç¿ëÁßÀÎÁö È®ÀÎÇÏ¿©
	// bool °ªÀ¸·Î ¹İÈ¯, »ç¿ëÁßÀÌ¸é true, »ç¿ë x¸é false
	const bool EffectCheck(ItemId id)const
	{
		return itemData.at(id).E_Check;
	}
	// µé¾î¿Â ItemId°¡ »ç¿ë¾ÆÀÌÅÛÀÎÁö È®ÀÎ
	// ¸ÂÀ»°æ¿ì true, ¾Æ´Ò°æ¿ì false
	const bool ItemCheck(ItemId id)const
	{
		return(ItemId::Weapon1 > id) ? true : false;
	}
	// µé¾î¿Â ItemId°¡ ¹«±âÀÎÁö È®ÀÎ
	// ¸ÂÀ»°æ¿ì true, ¾Æ´Ò°æ¿ì false
	const bool WeaponCheck(ItemId id)const
	{
		if (ItemCheck(id)) return false;
		return(ItemId::Equipment1 > id) ? true : false;
	}
	// µé¾î¿Â ItemId°¡ EquipmentÀÎÁö È®ÀÎ
	// ¸ÂÀ»°æ¿ì true, ¾Æ´Ò°æ¿ì false
	const bool EquipmentCheck(ItemId id)const
	{
		return(ItemId::Weapon10 < id) ? true : false;
	}
	// ±× ÈÄ ¸ÂÀ»°æ¿ì ÇØ´ç Id effectÇÔ¼ö È£Ãâ, false¸é ¾ÆÀÌÅÛ È¿°ú Àû¿ëÁßÀÎÁö È®ÀÎ ÈÄ
	// È¿°ú Àû¿ë
	const void E_Apply(ItemId Id)
	{
		if (!ItemCheck(Id)) // ¼Òºñ ¾ÆÀÌÅÛÀÏ °æ¿ì ¾Æ·¡ EffectÀû¿ëÇÔ¼ö ÁøÇà
		{
			if (EffectCheck(Id)) // Àåºñ ¾ÆÀÌÅÛÀÌ »ç¿ëÁß ÀÏ°æ¿ì ¸ø¾²°Ô ¸·À½
			{
				std::cout << "ÇØ´ç Àåºñ´Â »ç¿ëÁßÀÔ´Ï´Ù." << std::endl;
				return;
			}
		}
		itemData.at(Id).effects();
	}
	// ±× ÈÄ ¸ÂÀ»°æ¿ì ÇØ´ç Id effectÇÔ¼ö È£Ãâ, false¸é ¾ÆÀÌÅÛ È¿°ú Àû¿ëÁßÀÎÁö È®ÀÎ ÈÄ
	// È¿°ú Àû¿ë
	const void ER_Apply(ItemId Id)
	{
		if (ItemCheck(Id)) return;// ¼Òºñ ¾ÆÀÌÅÛÀÏ °æ¿ì ¹İÈ¯
		if (!EffectCheck(Id)) // Àåºñ ¾ÆÀÌÅÛÀÌ »ç¿ëÁßÀÌ ¾Æ´Ò°æ¿ì Àåºñ Å»°Å ¸·À½
		{
			std::cout << "ÇØ´ç Àåºñ´Â »ç¿ëÁßÀÌ ¾Æ´Õ´Ï´Ù." << std::endl;
			return;
		}
		itemData.at(Id).removeEffects();
	}
	void E_Off(ItemId id) { E_ON_OFF(id, false); }
	void E_ON(ItemId id) { E_ON_OFF(id, true); }
private:
	std::unordered_map<ItemId, NewItemInfo> itemData;
	//int °ªÀ» ItemId·Î ¹Ù²Ù´Â ¸ŞÅ©·Î
	ItemId Id_Convert(int number)
	{
		return static_cast<ItemId>(number);
	}
	//int °ªÀ» ItemRarity·Î ¹Ù²Ù´Â ¸ŞÅ©·Î
	ItemRarity Rarity_Convert(int number)
	{
		return static_cast<ItemRarity>(number);
	}
	
	// ItemId ¹ŞÀ¸¸é Effect»ç¿ë²ô°í Å°´Â ÇÔ¼ö, Private ÇØ¾ßµÊ
	void E_ON_OFF(ItemId id, bool on_off)
	{
		itemData.at(id).E_Check = on_off;
	}
	// 
	std::function<void()> getEffectFunction(ItemId id);
	std::function<void()> getRemoveEffectFunction(ItemId id);
	// È¿°ú Á¤ÀÇ ¼±¾ğºÎ
#pragma region Effect
	void HealthPortionEffect();
	void BigHealthPortionEffect();
	void PowerPortionEffect();
	void BigPowerPortionEffect();
	void Potion4Effect();
	void Potion5Effect();
	void Potion6Effect();
	void Potion7Effect();
	void FirePortionEffect();
	void BigFirePortionEffect();
	void Weapon1Effect();
	void Weapon2Effect();
	void Weapon3Effect();
	void Weapon4Effect();
	void Weapon5Effect();
	void Weapon6Effect();
	void Weapon7Effect();
	void Weapon8Effect();
	void Weapon9Effect();
	void Weapon10Effect();
	void Equipment1Effect();
	void Equipment2Effect();
	void Equipment3Effect();
	void Equipment4Effect();
	void Equipment5Effect();
	void Equipment6Effect();
	void Equipment7Effect();
	void Equipment8Effect();
	void Equipment9Effect();
	void Equipment10Effect();
	void RemoveWeapon1Effect();
	void RemoveWeapon2Effect();
	void RemoveWeapon3Effect();
	void RemoveWeapon4Effect();
	void RemoveWeapon5Effect();
	void RemoveWeapon6Effect();
	void RemoveWeapon7Effect();
	void RemoveWeapon8Effect();
	void RemoveWeapon9Effect();
	void RemoveWeapon10Effect();
	void RemoveEquipment1Effect();
	void RemoveEquipment2Effect();
	void RemoveEquipment3Effect();
	void RemoveEquipment4Effect();
	void RemoveEquipment5Effect();
	void RemoveEquipment6Effect();
	void RemoveEquipment7Effect();
	void RemoveEquipment8Effect();
	void RemoveEquipment9Effect();
	void RemoveEquipment10Effect();
#pragma endregion
};

class MainItem
{
	SINGLE(MainItem);

public: // °ø°³ ÇÔ¼ö
	// TODO: ¾ÆÁ÷ ¾ÆÀÌÅÛ Àåºñ ¶Ç´Â »ç¿ëÈ¿°ú Àû¿ëÀº ¼¼¼¼ÇÏ°Ô ±¸Çö ¾ÈÇßÀ½, ÃßÈÄ¿¡ ÇØ¾ßµÊ

	// ¾ÆÀÌÅÛ init
	void ItemInit(); 
	// ¾ÆÀÌÅÛ »ç¿ëÇÏ´Â ÇÔ¼ö
<<<<<<< HEAD
	void UseItemManuOpen();
	// Àåºñ ÇØÃ¼ ¹× °ü¸® ÃÑ°ü¸® ÇÔ¼ö
	// ÀåÂøÇÑÀåºñ º¸¿©ÁÖ°í(¾øÀ¸¸é Àåºñ¾ø´Ù°í ¹Ù·Î¹İÈ¯)
	// ÀåºñÇØÃ¼ ÇÒ°ÇÁö ¹°¾îº½(¿©±â¼­´Â Àåºñ ÇØÃ¼¸¸ °¡´É)
	void TotalequippedItems();
	// ¾ÆÀÌÅÛÄ­ »èÁ¦ÇÏ´Â ÇÔ¼ö
	void DeleteItemManuOpen();
private:
	
	// ¾ÆÀÌÅÛÀÇ ½ÇÁ¦ ÀúÀå°ø°£
	vector<ItemId>  ItemBag;
	//¼Õ¿¡ ÀÖ´Â ¾ÆÀÌÅÛ, ÀÌ°É·Î¸¸ ¾ÆÀÌÅÛ »èÁ¦ ÇÏµµ·Ï ÇÏÀÚ
	vector<ItemId>::iterator handleItem;
private:
	// HandleItem À§Ä¡ º¯°æ Auto, int°ª ¹Ş¾Æ¼­ ÁøÇàÇÔ
	void handleAuto(int choice)
	{
		auto it = ItemBag.begin();
		handleItem = it + choice;
	}
	//HandleItem Áö¿ì±â, ÀÏ´Ü privite ·Î ¸¸µé¾î¼­ »ç¿ëÇØ¾ß µÉµí
	void HandleItemErase(vector<ItemId>::iterator& ItemId);
	// ¾ÆÀÌÅÛ Ã£¾ÆÁÖ´Â ÇÔ¼ö ±×¸®°í ¾ÆÀÌÅÛ ³ª¿­ ÇÏ´Â ÇÔ¼ö(publicÀ¸·Î ¹Ù²ÜÁö °í¹Î)
	void OpenItemBag();
	// iterator ÁÖ¼Ò°ªÀ» id int°ª »Ì¾Æ¿À´Â ÇÔ¼ö
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// ItmeIDÀ» id string°ª »Ì¾Æ¿À´Â ÇÔ¼ö
	const string ViewItemName(ItemId id) const
	{
		return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name;
	}
	// TODO: ¾ÆÀÌÅÛ ¾ò¾î¼­ ItemBag¿¡ ÀúÀå ÇÒ‹š °°Àº°Ô µé¾î¿À¸é AddItem ÇÔ¼ö¿¡¼­ ItemBag¿¡ ¼ö·®À» °ü¸®ÇÒ º¯¼ö¸¦ ³ÖÀÚ
	// ÀÚ ¾ÆÀÌÅÛÀ» »èÁ¦ÇÏ´Â °æ¿ì
	// 1. ¼Ò¸ğ¼º ¾ÆÀÌÅÛÀ» »ç¿ëÇÒ‹š
	// 2. Àåºñ¸¦ ÁıÀû ¹ö¸±‹š
	// 3. Àåºñ°¡ ³»±¸µµ°¡ ³¡³¯‹š(¾Æ¸¶µµ ¾È ³ÖÀ»µí)
	// ItemId ÀÔ·ÂÇÏ¸é Àåºñ¿¡ Ãß°¡ÇÏ´Â ÇÔ¼ö
	void AddItem(ItemId item);
	// ÇöÀç handleItem À§Ä¡ ¾ÆÀÌÅÛ »èÁ¦ÇÏ´Â ÇÔ¼ö
	void DeleteItem();
	// ¼Ò¸ğ¼º¾ÆÀÌÅÛ »ç¿ëÇÏ°í »ç¿ëÇß´Ù¸é ¾ÆÀÌÅÛÄ­¿¡¼­ »èÁ¦ÇÏ´Â ÇÔ¼ö 1¹ø
	void UsingItem();
	
=======
	// ItemBagView -> Yes_or_No -> Yes ½Ã ItemId_Use ÁøÇà
	void UseItemManuOpen(); 
	// ¾ÆÀÌÅÛ Ã£¾ÆÁÖ´Â ÇÔ¼ö ±×¸®°í ¾ÆÀÌÅÛ ³ª¿­ ÇÏ´Â ÇÔ¼ö(publicÀ¸·Î ¹Ù²ÜÁö °í¹Î)
	// 4. ItemBag È®ÀÎ ÇÏ´Â ÇÔ¼ö : ¾ÆÀÌÅÛ Id ¹× °³¼ö±îÁö¸¸ º¸¿©ÁÖ±â¸¸ ÇÔ
	void OpenItemBag(); 
	// TODO: È¿°ú Áßº¹°¡´É ¹®Á¦ ¹ÌÇØ°á
	// ÀåÂø¾ÆÀÌÅÛ È®ÀÎ(view)
	bool ViewEquippedItems();
	// Àåºñ ÇØÃ¼ ¹× ÃÑ °ü¸® ÇÔ¼ö
	// ÀåÂøÇÑÀåºñ view -> Yes_or_No -> Yes½Ã MoveEquipped ÁøÇà
	void TotalequippedItems();

private: // MainItem ³»ºÎ ÇÔ¼ö ÃÑ °ü¸® ÇÔ¼ö

	// ¾ÆÀÌÅÛ, Àåºñ ÀÇ »ç¿ëÈ¿°ú¸¦ ±¸ºĞÇØ¼­ »ç¿ëÇÏ´Â ÇÔ¼ö
	// ¾ÆÀÌÅÛ Type ÀÚµ¿±¸ºĞ_Áï½Ã¹ßµ¿, ¾ÆÀÌÅÛ ¹é¿¡ÀÖÀ» °æ¿ì¿¡ »ç¿ë
	void ItemId_Use(ItemId id);

	// 2.¼Ò¸ğ¼º ¾ÆÀÌÅÛ »ç¿ëÇÔ¼ö : ¿©±â¼­´Â ¾ÆÀÌÅÛ Id¸¦ ¹Ş°í ÀÌ°Ô ¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÎÁö È®ÀÎÇÏ¿© ¸ÂÀ»°æ¿ì ÁøÇà
	// ¼Ò¸ğ¼º ¾ÆÀÌÅÛ°ú ¹«±â ¾ÆÀÌÅÛ, Àåºñ¾ÆÀÌÅÛÀ» ¾ÆÀÌÅÛ µµ°¨¿¡¼­ ÀÌ °ªÀ» ¹Ş¾Æ¿À´Â ÇÔ¼ö»ı¼º
	// ¿©±â¼­ ¾ÆÀÌÅÛ ¹«±â, Àåºñ ÀåÂø ÇÔ¼öµµ ÀÛµ¿ÇÏ°Ô ¸¸µé¾î¾ß°Ú´Ù
	void UseItem(ItemId id);

	// 3. Àåºñ ÀåÂø ÇÔ¼ö : ÀåºñµÈ ¾ÆÀÌÅÛÀ» °ü¸® ÇÒ º¯¼ö¿¡ ItemId ³Ö°í ¾ÆÀÌÅÛ È¿°ú ÇÔ¼ö Ãâ·Â
	// ÁøÇàÁß ¾ÆÀÌÅÛ »èÁ¦µµ ÁøÇà , ¾ÆÀÌÅÛ ¹é¿¡¼­ °³¼ö 1°³¸¦ ³»¸®°í ±× ÈÄ¿¡ 0°³°¡ µÉ°æ¿ì Id°ªµµ ¾ø¾Ö
	void equippedUse(ItemId id);

	// ÀåÂø¾ÆÀÌÅÛ ÇØÃ¼
	void MoveEquipped(ItemId id);

private: // itemBag »ç¿ë ÇÔ¼ö

	// ItemId ÀÔ·ÂÇÏ¸é Àåºñ¿¡ Ãß°¡ÇÏ´Â ÇÔ¼ö
	void AddItem(ItemId item);
	// ItemId ÀÔ·ÂÇÏ¸é Àåºñ¿¡ Ãß°¡ÇÏ´Â ÇÔ¼ö, int°ª ³ÖÀ¸¸é ±× ¼ö¸¸Å­ ³ÖÀ½
	void AddItem(ItemId item, int NUMBER);
	// OpenItemBag¿¡ ¸ÂÃß¾î ItemId¸¦ ÀÎ¼ö¸¦ ÁÙ ÇÔ¼ö
	ItemId ItemBagId_to_cinAuto();

private:	//equippedItems »ç¿ë ÇÔ¼ö

	// ItemId °¡ ÀÎ¼ö·Î µé¾î¿À¸é ÀåºñÃ¢¿¡ Ãß°¡ÇÏ´Â ÇÔ¼ö
	// Àåºñ Ãß°¡ ½ÇÆĞ(°°Àº Àåºñ°¡ ÀÖÀ½ µî)½Ã falseÃâ·Â
	bool AddequippedItems(ItemId id); 

	// ItemId ÀÎ¼ö·Î ¹ŞÀ¸¸é Áö±İ id°¡ ÀåºñÃ¢¿¡ ÀÖ´Â ¾ÆÀÌÅÛ typeÇÏ°í ÈÄ¡´ÂÁö È®ÀÎ
	// ÀåºñÃ¢ Å½»öÁß °°Àº ¾ÆÀÌÅÛÀÌ ÀåÂøµÇÁö ¾ÊÀº°ÍÀÌ È®ÀÎµÇ¸é true, ÈÄ¡¸é false
	bool LikeItemtypeCheck(ItemId id); 
	
	// equippedItems¿¡ ¸ÂÃß¾î ItemId¸¦ ÀÎ¼ö¸¦ ÁÙ ÇÔ¼ö
	ItemId EquippedId_to_cinAuto();

private: // MainItem Class ³»ºÎ º¯È¯ ÇÔ¼ö

	std::unordered_map<ItemId, int> ItemBag; // ¾ÆÀÌÅÛ °¡¹æ
	std::unordered_set<ItemId> equippedItems; // ÀåºñÁßÀÎ Àåºñ

	// ItemId È®ÀÎÇØ¼­ ¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÎÁö È®ÀÎÇÏ´Â ÇÔ¼ö
	// ¼Ò¸ğ¼º ¾ÆÀÌÅÛÀÏ°æ¿ì true Ãâ·Â
	bool ItemTypeCheck(ItemId id);

	// ItemId ÀÎ¼ö·Î ¹ŞÀ¸¸é ±×¿¡ ¸Â´Â ¾ÆÀÌÅÛ È¿°ú Ãâ·Â 
	void ItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).effects; }

	// ItemId ÀÎ¼ö·Î ¹ŞÀ¸¸é ±×¿¡ ¸Â´Â ¾ÆÀÌÅÛ »èÁ¦È¿°ú Ãâ·Â
	// Àåºñ ¾ÆÀÌÅÛ »èÁ¦½Ã »ç¿ë
	void RemoveItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).removeEffects; }

	// ItemId ÀÎ¼ö·Î ¹ŞÀ¸¸é ÀÌ¸§ Ãâ·Â 
	string ItemName(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name; }

	// ItemId ÀÎ¼ö·Î ¹ŞÀ¸¸é ¾î¶²Á¾·ùÀÇ ¾ÆÀÌÅÛÀÎÁö ¾Ë·ÁÁÜ
	ItemType Itemtype(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Type; }
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
	// int°ª ÀÔ·ÂÇÏ¸é ItemId°ªÀ¸·Î º¯È¯ÇÏ´Â ÇÔ¼ö
	ItemId convert(int Num) const
	{
		return static_cast<ItemId>(Num);
	}
<<<<<<< HEAD
public:	//¾ÆÀÌÅÛ »ç¿ëÇÔ¼ö
	
	//ItemEncyclopedia Itemsub; // ¾ÆÀÌÅÛ µµ°¨
	// °¢ ItemId¿¡ ´ëÀÀÇÏ´Â È¿°ú ÇÔ¼ö¸¦ ÀúÀåÇÒ ¸ÊÇÎ Å×ÀÌºí
	/*std::unordered_map<ItemId, std::function<void()>> effects;
	std::unordered_map<ItemId, std::function<void()>> removeEffects;*/
	//vector<ItemId> equippedItems; // ÀåºñÇÑ Àåºñ ¸ñ·Ï
	// TODO: È¿°ú Áßº¹°¡´É ¹®Á¦ ¹ÌÇØ°á
	// ÀåÂø¾ÆÀÌÅÛ È®ÀÎ(view)
	bool ViewEquippedItems();
	// ÀåÂø¾ÆÀÌÅÛ È®ÀÎ(Check)
	// ¾øÀ»°æ¿ì false
	bool EquipmentCheck();
	// ItemId°ªÀ» ¹Ş¾Æ ¸Â´ÂÁö È®ÀÎ
	bool EquipentCheckAuto(ItemId id)
	{
		return ItemEncyclopedia::GetInst()->EffectCheck(id);
	}
	
	// ÀåÂø¾ÆÀÌÅÛ ÇØÃ¼
	bool MoveEquipped();
	// ¾ÆÀÌÅÛ Ã¢ ¼øÈ¸ ÇÏ¸é¼­ Àåºñ¸¸ ÀåÂø
	void UnItemTypeEffect(ItemId itemId);  
	// Àåºñ ÀÚµ¿ ÀåÂø
	// ¾ÆÀÌÅÛÃ¢ ¼øÈ¸ ÇÏ¸é¼­ Àåºñ ¾Õ¿¡ÀÖ´Â ¼ø¼­´ë·Î ÀåÂø
	void BagEffect();
	// ¾ÆÀÌÅÛÃ¢ ¾ÆÀÌÅÛ »ç¿ëÇÏ´Â ÇÔ¼ö
	// ItemId ¹Ş¾Æ¼­ ¼Ò¸ğ¼º¾ÆÀÌÅÛÀÏ°æ¿ì È¿°ú Àû¿ë
	// ¼Ò¸ğ¼º¾ÆÀÌÅÛÀÌ ¾Æ´Ñ°æ¿ì false ¹İÈ¯, ¾ÆÀÌÅÛ È¿°úÀû¿ë ¼º°ø½Ã true ¹İÈ¯
	bool ItemEffect(ItemId Id);
	// ItemId¸¦ ÀÎ¼ö·Î ÀåºñÈ¿°ú Àû¿ë(»èÁ¦ ¾ÈµÊ), Private Ã³¸®¿¹Á¤
	// ÀÚµ¿ ÀåÂø ÇÔ¼ö¿¡¼­ È£ÃâÇÔ
	void applyEffect(ItemId test);
	// ItemId¸¦ ÀÎ¼ö·Î ÀåºñÁ¦°ÅÈ¿°ú Àû¿ë(»èÁ¦ ¾ÈµÊ), Private Ã³¸®¿¹Á¤
	// ÀÚµ¿ÇØÃ¼ ÇÔ¼ö¿¡¼­ È£ÃâÇÔ
	void RemoveEffect(ItemId test);
	
 

=======
>>>>>>> ItemClass-ì¥ì°©ì•„ì´í…œ-ë³€ìˆ˜-ì œê±°ì‘ì—…-ì „í™˜
};

