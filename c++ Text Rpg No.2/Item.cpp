#include "pch.h"
#include "Item.h"

string ItemArr[(int)ItemId::End] =
{	// 지금은 index 9ea만 사용 가능 나중에 구조 수정 예정(24.10.23)
	"HealthPortion",
	"BigHealthPortion",
	"PowerPortion",
	"BigPowerPortion",
	"weapon1",
	"weapon2",
	"weapon3",
	"FirePortion",
	"BigFirePortion",
	"VeryBigThis"
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
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister 알고리즘을 사용하는 엔진 생성

	// 균일 분포에서 랜덤한 정수 생성 (0 이상 99 이하)
	std::uniform_int_distribution<int> distribution(0, 99);
	
	for (int i = 0; i < 9; ++i)
	{
		int rendom = distribution(gen) % 10;
		ItemMMOR NewItem = { static_cast<ItemId>(rendom),ItemArr[rendom] };
		ItemBag.push_back(NewItem);
	}
	handleItem = ItemBag.begin();
	OpenItemBag();
}

void MainItem::HandleItemErase(vector<ItemMMOR>::iterator& ItemId)
{
	
	vector<ItemMMOR>::iterator it = ItemId;
	if (it != ItemBag.end())
	{
		
		ItemBag.erase(it);
	}
}
int MainItem::SelectId(const vector<ItemMMOR>::iterator& ItemId)
{
	if (ItemId == ItemBag.end())
	{
		std::cout << "Get Id fale" << std::endl;
		return 0;
	}
	else
	{
		ItemMMOR Hi = *ItemId;
		return (int)Hi.CurItemId;
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
	if (0 == choice || choice > ItemBag.size())
	{
		ErrorCode();
	}
	else
	{
		handleItem = ItemBag.begin();
		for (int i = 0, item = -1; i < item; ++i)
		{
			++handleItem;
		}
	}
	UseItem(handleItem);
	
}

void MainItem::UseItem(vector<ItemMMOR>::iterator Item)
{
	
}
void MainItem::ChangeHandleItem(int item)
{
	
}

void MainItem::OpenItemBag()
{
	vector<ItemMMOR>::iterator BeginhandleItem = ItemBag.begin();

	for (int i = 0; i < ItemBag.size(); ++BeginhandleItem,++i)
	{
		//int GetId = GetInst()->SelectId(BeginhandleItem);
		string GetName =GetInst()->SelectName(BeginhandleItem);
		std::cout << i+1 << ". " << GetName << std::endl;
	}


}



MainItem::MainItem()
	:ItemBag()
	, handleItem{}
{
}

MainItem::~MainItem()
{
	
}
