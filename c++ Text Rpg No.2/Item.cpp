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
	//item을 랜덤으로 3개만 추가 하고 싶은데
	// 일단 5,2,6 이런식으로 고정된 시드값 넣어보자
	/*
	for (int i = 0; i < (int)ItemId::End; ++i)
	{
		ItemMMOR NewItem = { static_cast<ItemId>(i),ItemArr[i]};
		ItemBag.push_back(NewItem);
	}
	*/
	//std::random_device rd;
	//std::mt19937 gen(rd()); // Mersenne Twister 알고리즘을 사용하는 엔진 생성

	//// 균일 분포에서 랜덤한 정수 생성 (0 이상 99 이하)
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
	// 아이템 을 고르고 사용을 할지 정하자
	int choice = 0;
	std::cout << std::endl << "사용하실 아이템을 고르세요" << std::endl;
	std::cin >> choice;
	if (0 == choice || choice > ItemBag.size() || std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ErrorCode();
		return;
	}
	//erase 함수 호출해서 적용해야하니까 iterator 반환값 남기자
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
		std::cout << "잘못된 아이템 아이디입니다." << std::endl;
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
