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
	CONSUMABLE,  // �Ҹ� ������
	WEAPON,      // ����
	EQUIPMENT    // ���
};
enum ItemRarity {
	COMMON,      // �Ϲ� ������ 1~2 ��
	UNCOMMON,    // ��� ������ 3~4 ��
	RARE,        // ��� ������ 5~6 ��
	EPIC,        // ���� ������ 7~8 ��
	LEGENDARY    // ���� ������ 9~10 ��
};
struct NewItemInfo
{
	string	Name; // �̸�
	ItemRarity Rarity; // ���
	ItemType	Type;	// ������ Ÿ��
	std::function<void()> effects;		// ����� ȿ��
	std::function<void()> removeEffects;// Ż���� ȿ��
	bool E_Check = false;				// �����Ǿ� �ִ��� üũ
};
class ItemEncyclopedia
{
	SINGLE(ItemEncyclopedia);
	
public:
	
	//vector<ItemId> ReturnItemId();
	// ������ Id ������ ItemData ����
	const NewItemInfo getNewItemInfo(ItemId id) const {
		return itemData.at(id);
	}

private:
	std::unordered_map<ItemId, NewItemInfo> itemData;
	//int ���� ItemId�� �ٲٴ� ��ũ��
	ItemId Id_Convert(int number)
	{
		return static_cast<ItemId>(number);
	}
	//int ���� ItemRarity�� �ٲٴ� ��ũ��
	ItemRarity Rarity_Convert(int number)
	{
		return static_cast<ItemRarity>(number);
	}
	// 
	std::function<void()> getEffectFunction(ItemId id);
	std::function<void()> getRemoveEffectFunction(ItemId id);
	// ȿ�� ���� �����
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

public: // ���� �Լ�
	// TODO: ���� ������ ��� �Ǵ� ���ȿ�� ������ �����ϰ� ���� ������, ���Ŀ� �ؾߵ�

	// ������ init
	void ItemInit(); 
	// ������ ����ϴ� �Լ�
	// ItemBagView -> Yes_or_No -> Yes �� ItemId_Use ����
	void UseItemManuOpen(); 
	// ������ ã���ִ� �Լ� �׸��� ������ ���� �ϴ� �Լ�(public���� �ٲ��� ���)
	// 4. ItemBag Ȯ�� �ϴ� �Լ� : ������ Id �� ���������� �����ֱ⸸ ��
	void OpenItemBag(); 
	// TODO: ȿ�� �ߺ����� ���� ���ذ�
	// ���������� Ȯ��(view)
	bool ViewEquippedItems();
	// ��� ��ü �� �� ���� �Լ�
	// ��������� view -> Yes_or_No -> Yes�� MoveEquipped ����
	void TotalequippedItems();

private: // MainItem ���� �Լ� �� ���� �Լ�

	// ������, ��� �� ���ȿ���� �����ؼ� ����ϴ� �Լ�
	// ������ Type �ڵ�����_��ùߵ�, ������ �鿡���� ��쿡 ���
	void ItemId_Use(ItemId id);

	// 2.�Ҹ� ������ ����Լ� : ���⼭�� ������ Id�� �ް� �̰� �Ҹ� ���������� Ȯ���Ͽ� ������� ����
	// �Ҹ� �����۰� ���� ������, ���������� ������ �������� �� ���� �޾ƿ��� �Լ�����
	// ���⼭ ������ ����, ��� ���� �Լ��� �۵��ϰ� �����߰ڴ�
	void UseItem(ItemId id);

	// 3. ��� ���� �Լ� : ���� �������� ���� �� ������ ItemId �ְ� ������ ȿ�� �Լ� ���
	// ������ ������ ������ ���� , ������ �鿡�� ���� 1���� ������ �� �Ŀ� 0���� �ɰ�� Id���� ����
	void equippedUse(ItemId id);

	// ���������� ��ü
	void MoveEquipped(ItemId id);

private: // itemBag ��� �Լ�

	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�
	void AddItem(ItemId item);
	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�, int�� ������ �� ����ŭ ����
	void AddItem(ItemId item, int NUMBER);
	// OpenItemBag�� ���߾� ItemId�� �μ��� �� �Լ�
	ItemId ItemBagId_to_cinAuto();

private:	//equippedItems ��� �Լ�

	// ItemId �� �μ��� ������ ���â�� �߰��ϴ� �Լ�
	// ��� �߰� ����(���� ��� ���� ��)�� false���
	bool AddequippedItems(ItemId id); 

	// ItemId �μ��� ������ ���� id�� ���â�� �ִ� ������ type�ϰ� ��ġ���� Ȯ��
	// ���â Ž���� ���� �������� �������� �������� Ȯ�εǸ� true, ��ġ�� false
	bool LikeItemtypeCheck(ItemId id); 
	
	// equippedItems�� ���߾� ItemId�� �μ��� �� �Լ�
	ItemId EquippedId_to_cinAuto();

private: // MainItem Class ���� ��ȯ �Լ�

	std::unordered_map<ItemId, int> ItemBag; // ������ ����
	std::unordered_set<ItemId> equippedItems; // ������� ���

	// ItemId Ȯ���ؼ� �Ҹ� ���������� Ȯ���ϴ� �Լ�
	// �Ҹ� �������ϰ�� true ���
	bool ItemTypeCheck(ItemId id);

	// ItemId �μ��� ������ �׿� �´� ������ ȿ�� ��� 
	void ItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).effects; }

	// ItemId �μ��� ������ �׿� �´� ������ ����ȿ�� ���
	// ��� ������ ������ ���
	void RemoveItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).removeEffects; }

	// ItemId �μ��� ������ �̸� ��� 
	string ItemName(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name; }

	// ItemId �μ��� ������ ������� ���������� �˷���
	ItemType Itemtype(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Type; }
	// int�� �Է��ϸ� ItemId������ ��ȯ�ϴ� �Լ�
	ItemId convert(int Num)
	{
		return static_cast<ItemId>(Num);
	}
};

