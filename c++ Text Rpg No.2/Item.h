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
// 그러니까 아이템을 사용할때 이름값만 가져오면 어떤아이템을 사용되는지 
// 확인되고 사용하는 함수? 를 만들고 싶은거자나
// enum class 는 그렇게 사용하고 여기에는 결국 뭐를 만들고 싶은거냐 
// 일단 매니저로 사용하는거는 나중에 분리하고 모든기능을 
// 이 클래스에 때려놓고
// 모듈화를 천천히 진행하자
// 지금 아이템을 추가하는 함수는 우리가 진행하는 
// 함수에서 리스트(변수가 아닌 ItemArr에서 가져옴)
// 그러면 아이템 백은 그대로 쓰고 아이템 도감을 실제로 만들고
// 거기에 있는 정보를 가져오는게 

class MainItem
{
	SINGLE(MainItem);
public:
	// TODO: 아직 아이템 장비 또는 사용효과 적용은 세세하게 구현 안했음, 추후에 해야됨
	// 아이템 init
	void ItemInit();
	// 아이템 사용하는 함수
	void UseItemManuOpen();
	// 장비 해체 및 관리 총관리 함수
	// 장착한장비 보여주고(없으면 장비없다고 바로반환)
	// 장비해체 할건지 물어봄(여기서는 장비 해체만 가능)
	void TotalequippedItems();
private:
	// 아이템의 실제 저장공간
	vector<NewItemInfo>  ItemBag;
	//손에 있는 아이템
	vector<NewItemInfo>::iterator handleItem; //일단 privite 로 만들어서 사용해야 될듯
private:
	//HandleItem 지우기, 일단 privite 로 만들어서 사용해야 될듯
	void HandleItemErase(vector<NewItemInfo>::iterator& ItemId);
	// 아이템 찾아주는 함수 그리고 아이템 나열 하는 함수(public으로 바꿀지 고민)
	void OpenItemBag();
	// iterator 주소값을 id int값 뽑아오는 함수
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// iterator 참조값을 id string값 뽑아오는 함수
	string SelectName(const vector<NewItemInfo>::iterator& ItemId);
	
	// ItemId 입력하면 장비에 추가하는 함수
	void AddItem(ItemId item);
	// int값 입력하면 ItemId값으로 변환하는 함수
	ItemId convert(int Num)
	{
		return static_cast<ItemId>(Num);
	}
public:	//아이템 사용함수
	
	//ItemEncyclopedia Itemsub; // 아이템 도감
	// 각 ItemId에 대응하는 효과 함수를 저장할 맵핑 테이블
	/*std::unordered_map<ItemId, std::function<void()>> effects;
	std::unordered_map<ItemId, std::function<void()>> removeEffects;*/
	vector<ItemId> equippedItems; // 장비한 장비 목록
	// TODO: 효과 중복가능 문제 미해결
	// 장착아이템 확인(view)
	bool ViewEquippedItems();
	// 장착아이템 해체
	void MoveEquipped(int choice);
	// 아이템 효과 초기화 부
	void initEffects();
	void ItemTypeEffect(ItemId itemId);    // 소비아이템 사용, 장비 장착
	void UnItemTypeEffect(ItemId itemId);  // 장비 해제
	void applyEquippedItems();        // 장비 효과 적용
	// ItemId를 인수로 아이템,장비 효과 함수적용, Private 처리예정
	void applyEffect(ItemId test);
	// ItemId를 인수로 장비 효과제거 함수적용, Private 처리예정
	void RemoveEffect(ItemId test);
	
 

};

