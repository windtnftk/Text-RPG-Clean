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
	void ItemInit();
	//HandleItem 지우기, 일단 privite 로 만들어서 사용해야 될듯
	void HandleItemErase(vector<ItemMMOR>::iterator& ItemId);
	// 아이템 찾아주는 함수 그리고 아이템 나열 하는 함수
	void OpenItemBag();
	// iterator 주소값을 id int값 뽑아오는 함수
	ItemId SelectId(const vector<ItemMMOR>::iterator& ItemId);
	// iterator 주소값을 id string값 뽑아오는 함수
	string SelectName(const vector<ItemMMOR>::iterator& ItemId);
	// 아이템 사용하는 함수
	void UseItemManuOpen();
	// 지정한 아이템 사용하는 함수 -> 그냥 효과 발동
	void UseItem(ItemId Item);
	// handleItem로 지정한 아이템 사용하는 함수 -> 소지품 사용 -> 아이템 삭제
	void UseItem();
	// handleItem을 원하는 위치로 변경하는 함수
	void ChangeHandleItem(int item);
	// ItemId 입력하면 장비에 추가하는 함수
	void AddItem(ItemId item);
public:	//아이템 사용함수, ItemId받은거에 따라 따로 적용
	// 모두 하나로 처리
	void PortionUse(ItemId test);
public:
	// 각 ItemId에 대응하는 효과 함수를 저장할 맵핑 테이블
	std::unordered_map<ItemId, std::function<void()>> effects;

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


};

