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
// NowCoding : public �� private �и��۾� ���࿹�� �� �� ���� ������ ���� �Լ� ���� ����
class MainItem
{
	SINGLE(MainItem);
public:
	// TODO: ���� ������ ��� �Ǵ� ���ȿ�� ������ �����ϰ� ���� ������, ���Ŀ� �ؾߵ�
	// ItemBag ���� ����͵�
	// 1.������ �ʱ�ȭ : �ʱ� ������ 3�� ���� �ְ�, handle Item�� nullrt�� ���� ������ ����� �ֵ���
	// 
	// 5. ������ �߰� �Լ� : ������ Id�� �޾Ƽ� �߰��ϴ� �Լ�
	// �ΰ��� ������ �Լ��� ���� int �μ� ������� �� �� ��ŭ �߰�, Id���� ���� ��� 1���� �߰�
	// ���� ������ ID Ž�� �� ���� ������ ������ �߰� ������� ���� �����
	// 
	// �ٽ� ������ ���� ����
	std::unordered_map<ItemId, int> ItemBag; // ������ ����
	std::unordered_set<ItemId> equippedItems; // ������� ���
	// ������ init
	void ItemInit(); // �Ϸ�
	// ������ ����ϴ� �Լ�
	void UseItemManuOpen(); //�Ϸ�
private:
	// �� �������� ������������ ���� �ƴҰ�� ������ �ٸ� �Լ� ȣ��
	void UseItemChange(ItemId id);//�Ϸ�
	//3. ��� ���� �Լ� : ���� �������� ���� �� ������ ItemId �ְ� ������ ȿ�� �Լ� ���
	// ������ ������ ������ ����
	// ������ ������ �����Ҷ� ������ �鿡�� ���� 1���� ������ �� �Ŀ� 0���� �ɰ�� Id���� ����
	// �� ��� handle Item�� ������ �ϰ� Erase �Լ� ���(���� ����, ��Ȱ)
	void equippedUse(ItemId id);//�Ϸ�
	// 2.�Ҹ� ������ ����Լ� : ���⼭�� ������ Id�� �ް� �̰� �Ҹ� ���������� Ȯ���Ͽ� ������� ����
	// �Ҹ� �����۰� ���� ������, ���������� ������ �������� �� ���� �޾ƿ��� �Լ�����
	// ���⼭ ������ ����, ��� ���� �Լ��� �۵��ϰ� �����߰ڴ�
	void UseItem(ItemId id); // �Ϸ�
	// OpenItemBag�� ���߾� ItemId�� �μ��� �� �Լ�
	ItemId ItemBagId_to_cinAuto(); //�Ϸ�
	// equippedItems�� ���߾� ItemId�� �μ��� �� �Լ�
	ItemId EquippedId_to_cinAuto();//�Ϸ�
	// ItemId Ȯ���ؼ� �Ҹ� ���������� Ȯ���ϴ� �Լ�
	// �Ҹ� �������ϰ�� true ���
	bool ItemTypeCheck(ItemId id);//�Ϸ�
	// ItemId �μ��� ������ �׿� �´� ������ ȿ�� ��� //�Ϸ�
	void ItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).effects; }
	// ItemId �μ��� ������ �׿� �´� ������ ����ȿ�� ��� //�Ϸ�
	void RemoveItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).removeEffects; }
	// ItemId �μ��� ������ �̸� ��� //�Ϸ�
	string ItemName(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name; }
	// ItemId �μ��� ������ ������� ���������� �˷���
	ItemType Itemtype(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Type; }
	// ItemId �μ��� ������ ���� id�� ���â�� �ִ� ������ type�ϰ� ��ġ���� Ȯ��
	// ���â Ž���� ���� �������� �������� �������� Ȯ�εǸ� true, ��ġ�� false
	bool LikeItemtypeCheck(ItemId id); //�Ϸ�
	// ��� ��ü �� ���� �Ѱ��� �Լ�
	// ��������� �����ְ�(������ �����ٰ� �ٷι�ȯ)
	// �����ü �Ұ��� ���(���⼭�� ��� ��ü�� ����)
	void TotalequippedItems(); // �Ϸ�
	// ItemId �� �μ��� ������ ���â�� �߰��ϴ� �Լ�
	// ��� �߰� ����(���� ��� ���� ��)�� false���
	bool AddequippedItems(ItemId id); // �Ϸ�
	// ������� �Լ�
private:
	// �������� ���� �������
	//vector<NewItemInfo>  ItemBag;
	//�տ� �ִ� ������
	//vector<NewItemInfo>::iterator handleItem; //�ϴ� privite �� ���� ����ؾ� �ɵ�
private:
	//HandleItem �����, �ϴ� privite �� ���� ����ؾ� �ɵ�
	void HandleItemErase(vector<NewItemInfo>::iterator& ItemId);
	// ������ ã���ִ� �Լ� �׸��� ������ ���� �ϴ� �Լ�(public���� �ٲ��� ���)
	// 4. ItemBag Ȯ�� �ϴ� �Լ� : ������ Id �� ���������� �����ֱ⸸ ��
	
	void OpenItemBag(); // �Ϸ�
	// iterator �ּҰ��� id int�� �̾ƿ��� �Լ�
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// iterator �������� id string�� �̾ƿ��� �Լ�
	
	
	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�
	void AddItem(ItemId item); //�Ϸ�
	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�, int�� ������ �� ����ŭ ����
	void AddItem(ItemId item, int NUMBER); //�Ϸ�
	// int�� �Է��ϸ� ItemId������ ��ȯ�ϴ� �Լ�
	ItemId convert(int Num) // �Ϸ�
	{
		return static_cast<ItemId>(Num);
	}
public:	//������ ����Լ�
	
	//ItemEncyclopedia Itemsub; // ������ ����
	// �� ItemId�� �����ϴ� ȿ�� �Լ��� ������ ���� ���̺�
	/*std::unordered_map<ItemId, std::function<void()>> effects;
	std::unordered_map<ItemId, std::function<void()>> removeEffects;*/
	//vector<ItemId> equippedItems; // ����� ��� ���
	// TODO: ȿ�� �ߺ����� ���� ���ذ�
	// ���������� Ȯ��(view)
	bool ViewEquippedItems(); // �Ϸ�
	// ���������� ��ü
	void MoveEquipped(ItemId id); // �Ϸ�
	
	
 

};

