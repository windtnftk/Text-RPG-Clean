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
	End =32,
};
// �׷��ϱ� �������� ����Ҷ� �̸����� �������� ��������� ���Ǵ��� 
// Ȯ�εǰ� ����ϴ� �Լ�? �� ����� �������ڳ�
// enum class �� �׷��� ����ϰ� ���⿡�� �ᱹ ���� ����� �����ų� 
// �ϴ� �Ŵ����� ����ϴ°Ŵ� ���߿� �и��ϰ� ������� 
// �� Ŭ������ ��������
// ���ȭ�� õõ�� ��������
struct ItemMMOR
{
	ItemId		CurItemId;
	string		ItemName; //������ �̸� ����
	
};


class MainItem
{
	SINGLE(MainItem);
public:
	// �������� ���� �������
	vector<ItemMMOR>  ItemBag;
	//�տ� �ִ� ������
	vector<ItemMMOR>::iterator handleItem; //�ϴ� privite �� ���� ����ؾ� �ɵ�
	
public:
	
	// ������ init
	void ItemInit();
	//HandleItem �����, �ϴ� privite �� ���� ����ؾ� �ɵ�
	void HandleItemErase(vector<ItemMMOR>::iterator& ItemId);
	// ������ ã���ִ� �Լ� �׸��� ������ ���� �ϴ� �Լ�
	void OpenItemBag();
	// iterator �ּҰ��� id int�� �̾ƿ��� �Լ�
	ItemId SelectId(const vector<ItemMMOR>::iterator& ItemId);
	// iterator �ּҰ��� id string�� �̾ƿ��� �Լ�
	string SelectName(const vector<ItemMMOR>::iterator& ItemId);
	// ������ ����ϴ� �Լ�
	void UseItemManuOpen();
	// ������ ������ ����ϴ� �Լ� -> �׳� ȿ�� �ߵ�
	void UseItem(ItemId Item);
	// handleItem�� ������ ������ ����ϴ� �Լ� -> ����ǰ ��� -> ������ ����
	void UseItem();
	// handleItem�� ���ϴ� ��ġ�� �����ϴ� �Լ�
	void ChangeHandleItem(int item);
	// ItemId �Է��ϸ� ��� �߰��ϴ� �Լ�
	void AddItem(ItemId item);


};

