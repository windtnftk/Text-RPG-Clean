#include "pch.h"
#include "Item.h"

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
{
	//item�� �������� 3���� �߰� �ϰ� ������
	// �ϴ� 5,2,6 �̷������� ������ �õ尪 �־��
	/*
	for (int i = 0; i < (int)ItemId::End; ++i)
	{
		ItemMMOR NewItem = { static_cast<ItemId>(i),ItemArr[i]};
		ItemBag.push_back(NewItem);
	}
	*/
	//std::random_device rd;
	//std::mt19937 gen(rd()); // Mersenne Twister �˰����� ����ϴ� ���� ����

	//// ���� �������� ������ ���� ���� (0 �̻� 99 ����)
	//std::uniform_int_distribution<int> distribution(0, 99);

	//for (int i = 0; i < 9; ++i)
	//{
	//	int rendom = distribution(gen) % 10;
	//	ItemMMOR NewItem = { static_cast<ItemId>(rendom),ItemArr[rendom] };
	//	ItemBag.push_back(NewItem);
	//}

	AddItem(ItemId::Weapon1);
	AddItem(ItemId::Equipment1);
	AddItem(ItemId::HealthPortion);
	handleItem = ItemBag.begin();
	OpenItemBag();
}

void MainItem::HandleItemErase(vector<ItemMMOR>::iterator& ItemId)
{
	if (ItemId != ItemBag.end())
	{
		ItemBag.erase(ItemId);
		handleItem = ItemBag.begin();
	}
}
ItemId MainItem::SelectId(const vector<ItemMMOR>::iterator& ItemId)
{
	if (ItemId == ItemBag.end())
	{
		std::cout << "Get Id fale" << std::endl;
		return ItemId::End;
	}
	else
	{
		return ItemId->CurItemId;
	}

}
string MainItem::SelectName(const vector<ItemMMOR>::iterator& ItemId)
{
	ItemMMOR Hi = *ItemId;
	return (string)Hi.ItemName;
}

void MainItem::UseItemManuOpen()
{
	OpenItemBag();
	// ������ �� ���� ����� ���� ������
	int choice = 0;
	std::cout << std::endl << "����Ͻ� �������� ������" << std::endl;
	std::cin >> choice;
	if (0 == choice || choice > ItemBag.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ErrorCode();
		return;
	}
	//erase �Լ� ȣ���ؼ� �����ؾ��ϴϱ� iterator ��ȯ�� ������
	handleItem = ItemBag.begin();
	for (int i = 1; i < choice; ++i)
	{
		++handleItem;
	}
	UseItem();
}
void MainItem::UseItem()
{

	if (handleItem->CurItemId <= ItemId::BigFirePortion)
	{
	}
	else if (handleItem->CurItemId <= ItemId::Weapon10)
	{
	}
	else if (handleItem->CurItemId <= ItemId::Equipment10)
	{
	}
	else
	{
		ErrorCode();
		return;
	}
	HandleItemErase(handleItem);
}

void MainItem::UseItem(ItemId Item)
{
	if (Item <= ItemId::BigFirePortion)
	{
	}
	else if (Item <= ItemId::Weapon10)
	{
	}
	else if (Item <= ItemId::Equipment10)
	{
	}
	else
	{
		ErrorCode();
		return;
	}
}


void MainItem::ChangeHandleItem(int item)
{

}

void MainItem::AddItem(ItemId item)
{

	if (item <= ItemId::Equipment10)
	{
		ItemMMOR test = { item, ItemArr[static_cast<int>(item)] };
		ItemBag.emplace_back(test);
	}
	else
	{
		std::cout << "�߸��� ������ ���̵��Դϴ�." << std::endl;
	}
}

void MainItem::OpenItemBag()
{
	vector<ItemMMOR>::iterator BeginhandleItem = ItemBag.begin();

	for (int i = 0; i < ItemBag.size(); ++BeginhandleItem, ++i)
	{
		//int GetId = GetInst()->SelectId(BeginhandleItem);
		string GetName = SelectName(BeginhandleItem);
		std::cout << i + 1 << ". " << GetName << std::endl;
	}


}



MainItem::MainItem()
	:ItemBag()
	, handleItem{}
{
}

MainItem::~MainItem()
{
	delete& ItemBag;
	delete& handleItem;
}
