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
	bool E_Check = false;				// �����Ǿ� �ִ��� üũ, flase�� ������� �ʰ��ִ�
};
class ItemEncyclopedia
{
	SINGLE(ItemEncyclopedia);
	
public:
	// ItemId �޾Ƽ� Ű�� �Լ�, ���� �Լ�
	
	// ������ Id ������ Itme �̸� ����
	string ItemName(ItemId id)const
	{
		return itemData.at(id).Name;
	}
	// ������ Id ������ ItemData ����
	const NewItemInfo getNewItemInfo(ItemId id) const {
		return itemData.at(id);
	}
	// ItemId�� �� Ȯ���� �ش� ��� ��������� Ȯ���Ͽ�
	// bool ������ ��ȯ, ������̸� true, ��� x�� false
	const bool EffectCheck(ItemId id)const
	{
		return itemData.at(id).E_Check;
	}
	// ���� ItemId�� ������������ Ȯ��
	// ������� true, �ƴҰ�� false
	const bool ItemCheck(ItemId id)const
	{
		return(ItemId::Weapon1 > id) ? true : false;
	}
	// ���� ItemId�� �������� Ȯ��
	// ������� true, �ƴҰ�� false
	const bool WeaponCheck(ItemId id)const
	{
		if (ItemCheck(id)) return false;
		return(ItemId::Equipment1 > id) ? true : false;
	}
	// ���� ItemId�� Equipment���� Ȯ��
	// ������� true, �ƴҰ�� false
	const bool EquipmentCheck(ItemId id)const
	{
		return(ItemId::Weapon10 < id) ? true : false;
	}
	// �� �� ������� �ش� Id effect�Լ� ȣ��, false�� ������ ȿ�� ���������� Ȯ�� ��
	// ȿ�� ����
	const void E_Apply(ItemId Id)
	{
		if (!ItemCheck(Id)) // �Һ� �������� ��� �Ʒ� Effect�����Լ� ����
		{
			if (EffectCheck(Id)) // ��� �������� ����� �ϰ�� ������ ����
			{
				std::cout << "�ش� ���� ������Դϴ�." << std::endl;
				return;
			}
		}
		itemData.at(Id).effects();
	}
	// �� �� ������� �ش� Id effect�Լ� ȣ��, false�� ������ ȿ�� ���������� Ȯ�� ��
	// ȿ�� ����
	const void ER_Apply(ItemId Id)
	{
		if (ItemCheck(Id)) return;// �Һ� �������� ��� ��ȯ
		if (!EffectCheck(Id)) // ��� �������� ������� �ƴҰ�� ��� Ż�� ����
		{
			std::cout << "�ش� ���� ������� �ƴմϴ�." << std::endl;
			return;
		}
		itemData.at(Id).removeEffects();
	}
	void E_Off(ItemId id) { E_ON_OFF(id, false); }
	void E_ON(ItemId id) { E_ON_OFF(id, true); }
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
	
	// ItemId ������ Effect������ Ű�� �Լ�, Private �ؾߵ�
	void E_ON_OFF(ItemId id, bool on_off)
	{
		itemData.at(id).E_Check = on_off;
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
	// ������ĭ �����ϴ� �Լ�
	void DeleteItemManuOpen();
private:
	
	// �������� ���� �������
	vector<ItemId>  ItemBag;
	//�տ� �ִ� ������, �̰ɷθ� ������ ���� �ϵ��� ����
	vector<ItemId>::iterator handleItem;
private:
	// HandleItem ��ġ ���� Auto, int�� �޾Ƽ� ������
	void handleAuto(int choice)
	{
		auto it = ItemBag.begin();
		handleItem = it + choice;
	}
	//HandleItem �����, �ϴ� privite �� ���� ����ؾ� �ɵ�
	void HandleItemErase(vector<ItemId>::iterator& ItemId);
	// ������ ã���ִ� �Լ� �׸��� ������ ���� �ϴ� �Լ�(public���� �ٲ��� ���)
	void OpenItemBag();
	// iterator �ּҰ��� id int�� �̾ƿ��� �Լ�
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// ItmeID�� id string�� �̾ƿ��� �Լ�
	const string ViewItemName(ItemId id) const
	{
		return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name;
	}
	// TODO: ������ �� ItemBag�� ���� �ҋ� ������ ������ AddItem �Լ����� ItemBag�� ������ ������ ������ ����
	// �� �������� �����ϴ� ���
	// 1. �Ҹ� �������� ����ҋ�
	// 2. ��� ���� ������
	// 3. ��� �������� ������(�Ƹ��� �� ������)
	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�
	void AddItem(ItemId item);
	// ���� handleItem ��ġ ������ �����ϴ� �Լ�
	void DeleteItem();
	// �Ҹ𼺾����� ����ϰ� ����ߴٸ� ������ĭ���� �����ϴ� �Լ� 1��
	void UsingItem();
	
	// int�� �Է��ϸ� ItemId������ ��ȯ�ϴ� �Լ�
	ItemId convert(int Num) const
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
	bool ViewEquippedItems();
	// ���������� Ȯ��(Check)
	// ������� false
	bool EquipmentCheck();
	// ItemId���� �޾� �´��� Ȯ��
	bool EquipentCheckAuto(ItemId id)
	{
		return ItemEncyclopedia::GetInst()->EffectCheck(id);
	}
	
	// ���������� ��ü
	bool MoveEquipped();
	// ������ â ��ȸ �ϸ鼭 ��� ����
	void UnItemTypeEffect(ItemId itemId);  
	// ��� �ڵ� ����
	// ������â ��ȸ �ϸ鼭 ��� �տ��ִ� ������� ����
	void BagEffect();
	// ������â ������ ����ϴ� �Լ�
	// ItemId �޾Ƽ� �Ҹ𼺾������ϰ�� ȿ�� ����
	// �Ҹ𼺾������� �ƴѰ�� false ��ȯ, ������ ȿ������ ������ true ��ȯ
	bool ItemEffect(ItemId Id);
	// ItemId�� �μ��� ���ȿ�� ����(���� �ȵ�), Private ó������
	// �ڵ� ���� �Լ����� ȣ����
	void applyEffect(ItemId test);
	// ItemId�� �μ��� �������ȿ�� ����(���� �ȵ�), Private ó������
	// �ڵ���ü �Լ����� ȣ����
	void RemoveEffect(ItemId test);
	
 

};

