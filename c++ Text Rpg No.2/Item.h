#pragma once

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
// �׷��ϱ� �������� ����Ҷ� �̸����� �������� ��������� ���Ǵ��� 
// Ȯ�εǰ� ����ϴ� �Լ�? �� ����� �������ڳ�
// enum class �� �׷��� ����ϰ� ���⿡�� �ᱹ ���� ����� �����ų� 
// �ϴ� �Ŵ����� ����ϴ°Ŵ� ���߿� �и��ϰ� ������� 
// �� Ŭ������ ��������
// ���ȭ�� õõ�� ��������
// ���� �������� �߰��ϴ� �Լ��� �츮�� �����ϴ� 
// �Լ����� ����Ʈ(������ �ƴ� ItemArr���� ������)
// �׷��� ������ ���� �״�� ���� ������ ������ ������ �����
// �ű⿡ �ִ� ������ �������°� 

class MainItem
{
	SINGLE(MainItem);
public:
	// TODO: ���� ������ ��� �Ǵ� ���ȿ�� ������ �����ϰ� ���� ������, ���Ŀ� �ؾߵ�
	// ������ init
	void ItemInit();
	// ������ ����ϴ� �Լ�
	void UseItemManuOpen();
	// ��� ��ü �� ���� �Ѱ��� �Լ�
	// ��������� �����ְ�(������ �����ٰ� �ٷι�ȯ)
	// �����ü �Ұ��� ���(���⼭�� ��� ��ü�� ����)
	void TotalequippedItems();
private:
	// �������� ���� �������
	vector<NewItemInfo>  ItemBag;
	//�տ� �ִ� ������
	vector<NewItemInfo>::iterator handleItem; //�ϴ� privite �� ���� ����ؾ� �ɵ�
private:
	//HandleItem �����, �ϴ� privite �� ���� ����ؾ� �ɵ�
	void HandleItemErase(vector<NewItemInfo>::iterator& ItemId);
	// ������ ã���ִ� �Լ� �׸��� ������ ���� �ϴ� �Լ�(public���� �ٲ��� ���)
	void OpenItemBag();
	// iterator �ּҰ��� id int�� �̾ƿ��� �Լ�
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// iterator �������� id string�� �̾ƿ��� �Լ�
	string SelectName(const vector<NewItemInfo>::iterator& ItemId);
	
	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�
	void AddItem(ItemId item);
	// int�� �Է��ϸ� ItemId������ ��ȯ�ϴ� �Լ�
	ItemId convert(int Num)
	{
		return static_cast<ItemId>(Num);
	}
public:	//������ ����Լ�
	
	//ItemEncyclopedia Itemsub; // ������ ����
	// �� ItemId�� �����ϴ� ȿ�� �Լ��� ������ ���� ���̺�
	/*std::unordered_map<ItemId, std::function<void()>> effects;
	std::unordered_map<ItemId, std::function<void()>> removeEffects;*/
	vector<ItemId> equippedItems; // ����� ��� ���
	// TODO: ȿ�� �ߺ����� ���� ���ذ�
	// ���������� Ȯ��(view)
	bool ViewEquippedItems();
	// ���������� ��ü
	void MoveEquipped(int choice);
	// ������ ȿ�� �ʱ�ȭ ��
	void initEffects();
	void ItemTypeEffect(ItemId itemId);    // �Һ������ ���, ��� ����
	void UnItemTypeEffect(ItemId itemId);  // ��� ����
	void applyEquippedItems();        // ��� ȿ�� ����
	// ItemId�� �μ��� ������,��� ȿ�� �Լ�����, Private ó������
	void applyEffect(ItemId test);
	// ItemId�� �μ��� ��� ȿ������ �Լ�����, Private ó������
	void RemoveEffect(ItemId test);
	
 

};

