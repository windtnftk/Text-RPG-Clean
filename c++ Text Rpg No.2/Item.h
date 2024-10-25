#pragma once

enum class ItemId
{
	HealthPortion,
	BigHealthPortion,
	PowerPortion,
	BigPowerPortion,
	weapon1,
	weapon2,
	weapon3,
	FirePortion,
	BigFirePortion,

	End =32,

};
// 그러니까 아이템을 사용할때 이름값만 가져오면 어떤아이템을 사용되는지 
// 확인되고 사용하는 함수? 를 만들고 싶은거자나
// enum class 는 그렇게 사용하고 여기에는 결국 뭐를 만들고 싶은거냐 
// 일단 매니저로 사용하는거는 나중에 분리하고 모든기능을 
// 이 클래스에 때려놓고
// 모듈화를 천천히 진행하자
struct ItemMMOR
{
	ItemId		CurItemId;
	string		ItemName; //아이템 이름 저장
};


class MainItem
{
	SINGLE(MainItem);
public:
	// 아이템의 실제 저장공간
	vector<ItemMMOR>  ItemBag;
	//손에 있는 아이템
	vector<ItemMMOR>::iterator handleItem; //일단 privite 로 만들어서 사용해야 될듯
	
public:
	
	// 아이템 init
	virtual void ItemInit();
	//HandleItem 지우기, 일단 privite 로 만들어서 사용해야 될듯
	void HandleItemErase(vector<ItemMMOR>::iterator& ItemId);
	// 아이템 찾아주는 함수 그리고 아이템 나열 하는 함수
	void OpenItemBag();
	// iterator 주소값을 id int값 뽑아오는 함수
	int SelectId(const vector<ItemMMOR>::iterator& ItemId);
	// iterator 주소값을 id string값 뽑아오는 함수
	string SelectName(const vector<ItemMMOR>::iterator& ItemId);
	// 아이템 사용하는 함수
	void UseItemManuOpen();
	// handleItem로 지정한 아이템 사용하는 함수
	void UseItem(vector<ItemMMOR>::iterator Item);
	// handleItem을 원하는 위치로 변경하는 함수
	void ChangeHandleItem(int item);


};

