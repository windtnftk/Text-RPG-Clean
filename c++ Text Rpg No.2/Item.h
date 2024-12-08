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
	CONSUMABLE,  // 소모성 아이템
	WEAPON,      // 무기
	EQUIPMENT    // 장비
};
enum ItemRarity {
	COMMON,      // 일반 아이템 1~2 번
	UNCOMMON,    // 고급 아이템 3~4 번
	RARE,        // 희귀 아이템 5~6 번
	EPIC,        // 서사 아이템 7~8 번
	LEGENDARY    // 전설 아이템 9~10 번
};
struct NewItemInfo
{
	string	Name; // 이름
	ItemRarity Rarity; // 레어도
	ItemType	Type;	// 아이템 타입
	std::function<void()> effects;		// 착용시 효과
	std::function<void()> removeEffects;// 탈착시 효과
	bool E_Check = false;				// 장착되어 있는지 체크
};
class ItemEncyclopedia
{
	SINGLE(ItemEncyclopedia);
	
public:
	
	//vector<ItemId> ReturnItemId();
	// 아이템 Id 받으면 ItemData 전달
	const NewItemInfo getNewItemInfo(ItemId id) const {
		return itemData.at(id);
	}

private:
	std::unordered_map<ItemId, NewItemInfo> itemData;
	//int 값을 ItemId로 바꾸는 메크로
	ItemId Id_Convert(int number)
	{
		return static_cast<ItemId>(number);
	}
	//int 값을 ItemRarity로 바꾸는 메크로
	ItemRarity Rarity_Convert(int number)
	{
		return static_cast<ItemRarity>(number);
	}
	// 
	std::function<void()> getEffectFunction(ItemId id);
	std::function<void()> getRemoveEffectFunction(ItemId id);
	// 효과 정의 선언부
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
// NowCoding : public 과 private 분리작업 진행예정 그 후 문제 없으면 상점 함수 제작 예정
class MainItem
{
	SINGLE(MainItem);
public:
	// TODO: 아직 아이템 장비 또는 사용효과 적용은 세세하게 구현 안했음, 추후에 해야됨
	// ItemBag 에서 남길것들
	// 1.아이템 초기화 : 초기 아이템 3개 정도 있고, handle Item은 nullrt로 만들어서 지정후 지울수 있도록
	// 
	// 5. 아이템 추가 함수 : 아이템 Id를 받아서 추가하는 함수
	// 두가지 형태의 함수로 만들어서 int 인수 받을경우 그 수 만큼 추가, Id값만 받을 경우 1개만 추가
	// 내부 구조는 ID 탐색 후 원래 있으면 개수만 추가 없을경우 새로 만들고
	// 
	// 다시 만들자 새로 ㅇㅇ
	std::unordered_map<ItemId, int> ItemBag; // 아이템 가방
	std::unordered_set<ItemId> equippedItems; // 장비중인 장비
	// 아이템 init
	void ItemInit(); // 완료
	// 아이템 사용하는 함수
	void UseItemManuOpen(); //완료
private:
	// 고른 아이템이 장착아이템일 경우와 아닐경우 나눠서 다른 함수 호출
	void UseItemChange(ItemId id);//완료
	//3. 장비 장착 함수 : 장비된 아이템을 관리 할 변수에 ItemId 넣고 아이템 효과 함수 출력
	// 진행중 아이템 삭제도 진행
	// 아이템 삭제를 진행할때 아이템 백에서 개수 1개를 내리고 그 후에 0개가 될경우 Id값도 없애
	// 그 경우 handle Item을 재지정 하고 Erase 함수 출력(따로 만듬, 분활)
	void equippedUse(ItemId id);//완료
	// 2.소모성 아이템 사용함수 : 여기서는 아이템 Id를 받고 이게 소모성 아이템인지 확인하여 맞을경우 진행
	// 소모성 아이템과 무기 아이템, 장비아이템을 아이템 도감에서 이 값을 받아오는 함수생성
	// 여기서 아이템 무기, 장비 장착 함수도 작동하게 만들어야겠다
	void UseItem(ItemId id); // 완료
	// OpenItemBag에 맞추어 ItemId를 인수를 줄 함수
	ItemId ItemBagId_to_cinAuto(); //완료
	// equippedItems에 맞추어 ItemId를 인수를 줄 함수
	ItemId EquippedId_to_cinAuto();//완료
	// ItemId 확인해서 소모성 아이템인지 확인하는 함수
	// 소모성 아이템일경우 true 출력
	bool ItemTypeCheck(ItemId id);//완료
	// ItemId 인수로 받으면 그에 맞는 아이템 효과 출력 //완료
	void ItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).effects; }
	// ItemId 인수로 받으면 그에 맞는 아이템 삭제효과 출력 //완료
	void RemoveItemEffect(ItemId id) { ItemEncyclopedia::GetInst()->getNewItemInfo(id).removeEffects; }
	// ItemId 인수로 받으면 이름 출력 //완료
	string ItemName(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name; }
	// ItemId 인수로 받으면 어떤종류의 아이템인지 알려줌
	ItemType Itemtype(ItemId id) { return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Type; }
	// ItemId 인수로 받으면 지금 id가 장비창에 있는 아이템 type하고 곂치는지 확인
	// 장비창 탐색중 같은 아이템이 장착되지 않은것이 확인되면 true, 곂치면 false
	bool LikeItemtypeCheck(ItemId id); //완료
	// 장비 해체 및 관리 총관리 함수
	// 장착한장비 보여주고(없으면 장비없다고 바로반환)
	// 장비해체 할건지 물어봄(여기서는 장비 해체만 가능)
	void TotalequippedItems(); // 완료
	// ItemId 가 인수로 들어오면 장비창에 추가하는 함수
	// 장비 추가 실패(같은 장비가 있음 등)시 false출력
	bool AddequippedItems(ItemId id); // 완료
	// 장비장착 함수
private:
	// 아이템의 실제 저장공간
	//vector<NewItemInfo>  ItemBag;
	//손에 있는 아이템
	//vector<NewItemInfo>::iterator handleItem; //일단 privite 로 만들어서 사용해야 될듯
private:
	//HandleItem 지우기, 일단 privite 로 만들어서 사용해야 될듯
	void HandleItemErase(vector<NewItemInfo>::iterator& ItemId);
	// 아이템 찾아주는 함수 그리고 아이템 나열 하는 함수(public으로 바꿀지 고민)
	// 4. ItemBag 확인 하는 함수 : 아이템 Id 및 개수까지만 보여주기만 함
	
	void OpenItemBag(); // 완료
	// iterator 주소값을 id int값 뽑아오는 함수
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// iterator 참조값을 id string값 뽑아오는 함수
	
	
	// ItemId 입력하면 장비에 추가하는 함수
	void AddItem(ItemId item); //완료
	// ItemId 입력하면 장비에 추가하는 함수, int값 넣으면 그 수만큼 넣음
	void AddItem(ItemId item, int NUMBER); //완료
	// int값 입력하면 ItemId값으로 변환하는 함수
	ItemId convert(int Num) // 완료
	{
		return static_cast<ItemId>(Num);
	}
public:	//아이템 사용함수
	
	//ItemEncyclopedia Itemsub; // 아이템 도감
	// 각 ItemId에 대응하는 효과 함수를 저장할 맵핑 테이블
	/*std::unordered_map<ItemId, std::function<void()>> effects;
	std::unordered_map<ItemId, std::function<void()>> removeEffects;*/
	//vector<ItemId> equippedItems; // 장비한 장비 목록
	// TODO: 효과 중복가능 문제 미해결
	// 장착아이템 확인(view)
	bool ViewEquippedItems(); // 완료
	// 장착아이템 해체
	void MoveEquipped(ItemId id); // 완료
	
	
 

};

