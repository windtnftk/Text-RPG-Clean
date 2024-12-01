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
	bool E_Check = false;				// 장착되어 있는지 체크, flase면 사용하지 않고있다
};
class ItemEncyclopedia
{
	SINGLE(ItemEncyclopedia);
	
public:
	// ItemId 받아서 키는 함수, 끄는 함수
	
	// 아이템 Id 받으면 Itme 이름 전달
	string ItemName(ItemId id)const
	{
		return itemData.at(id).Name;
	}
	// 아이템 Id 받으면 ItemData 전달
	const NewItemInfo getNewItemInfo(ItemId id) const {
		return itemData.at(id);
	}
	// ItemId값 을 확인후 해당 장비를 사용중인지 확인하여
	// bool 값으로 반환, 사용중이면 true, 사용 x면 false
	const bool EffectCheck(ItemId id)const
	{
		return itemData.at(id).E_Check;
	}
	// 들어온 ItemId가 사용아이템인지 확인
	// 맞을경우 true, 아닐경우 false
	const bool ItemCheck(ItemId id)const
	{
		return(ItemId::Weapon1 > id) ? true : false;
	}
	// 들어온 ItemId가 무기인지 확인
	// 맞을경우 true, 아닐경우 false
	const bool WeaponCheck(ItemId id)const
	{
		if (ItemCheck(id)) return false;
		return(ItemId::Equipment1 > id) ? true : false;
	}
	// 들어온 ItemId가 Equipment인지 확인
	// 맞을경우 true, 아닐경우 false
	const bool EquipmentCheck(ItemId id)const
	{
		return(ItemId::Weapon10 < id) ? true : false;
	}
	// 그 후 맞을경우 해당 Id effect함수 호출, false면 아이템 효과 적용중인지 확인 후
	// 효과 적용
	const void E_Apply(ItemId Id)
	{
		if (!ItemCheck(Id)) // 소비 아이템일 경우 아래 Effect적용함수 진행
		{
			if (EffectCheck(Id)) // 장비 아이템이 사용중 일경우 못쓰게 막음
			{
				std::cout << "해당 장비는 사용중입니다." << std::endl;
				return;
			}
		}
		itemData.at(Id).effects();
	}
	// 그 후 맞을경우 해당 Id effect함수 호출, false면 아이템 효과 적용중인지 확인 후
	// 효과 적용
	const void ER_Apply(ItemId Id)
	{
		if (ItemCheck(Id)) return;// 소비 아이템일 경우 반환
		if (!EffectCheck(Id)) // 장비 아이템이 사용중이 아닐경우 장비 탈거 막음
		{
			std::cout << "해당 장비는 사용중이 아닙니다." << std::endl;
			return;
		}
		itemData.at(Id).removeEffects();
	}
	void E_Off(ItemId id) { E_ON_OFF(id, false); }
	void E_ON(ItemId id) { E_ON_OFF(id, true); }
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
	
	// ItemId 받으면 Effect사용끄고 키는 함수, Private 해야됨
	void E_ON_OFF(ItemId id, bool on_off)
	{
		itemData.at(id).E_Check = on_off;
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
	// 아이템칸 삭제하는 함수
	void DeleteItemManuOpen();
private:
	
	// 아이템의 실제 저장공간
	vector<ItemId>  ItemBag;
	//손에 있는 아이템, 이걸로만 아이템 삭제 하도록 하자
	vector<ItemId>::iterator handleItem;
private:
	// HandleItem 위치 변경 Auto, int값 받아서 진행함
	void handleAuto(int choice)
	{
		auto it = ItemBag.begin();
		handleItem = it + choice;
	}
	//HandleItem 지우기, 일단 privite 로 만들어서 사용해야 될듯
	void HandleItemErase(vector<ItemId>::iterator& ItemId);
	// 아이템 찾아주는 함수 그리고 아이템 나열 하는 함수(public으로 바꿀지 고민)
	void OpenItemBag();
	// iterator 주소값을 id int값 뽑아오는 함수
	//temId SelectId(const vector<NewItemInfo>::iterator& ItemId);
	
	// ItmeID을 id string값 뽑아오는 함수
	const string ViewItemName(ItemId id) const
	{
		return ItemEncyclopedia::GetInst()->getNewItemInfo(id).Name;
	}
	// TODO: 아이템 얻어서 ItemBag에 저장 할떄 같은게 들어오면 AddItem 함수에서 ItemBag에 수량을 관리할 변수를 넣자
	// 자 아이템을 삭제하는 경우
	// 1. 소모성 아이템을 사용할떄
	// 2. 장비를 집적 버릴떄
	// 3. 장비가 내구도가 끝날떄(아마도 안 넣을듯)
	// ItemId 입력하면 장비에 추가하는 함수
	void AddItem(ItemId item);
	// 현재 handleItem 위치 아이템 삭제하는 함수
	void DeleteItem();
	// 소모성아이템 사용하고 사용했다면 아이템칸에서 삭제하는 함수 1번
	void UsingItem();
	
	// int값 입력하면 ItemId값으로 변환하는 함수
	ItemId convert(int Num) const
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
	bool ViewEquippedItems();
	// 장착아이템 확인(Check)
	// 없을경우 false
	bool EquipmentCheck();
	// ItemId값을 받아 맞는지 확인
	bool EquipentCheckAuto(ItemId id)
	{
		return ItemEncyclopedia::GetInst()->EffectCheck(id);
	}
	
	// 장착아이템 해체
	bool MoveEquipped();
	// 아이템 창 순회 하면서 장비만 장착
	void UnItemTypeEffect(ItemId itemId);  
	// 장비 자동 장착
	// 아이템창 순회 하면서 장비 앞에있는 순서대로 장착
	void BagEffect();
	// 아이템창 아이템 사용하는 함수
	// ItemId 받아서 소모성아이템일경우 효과 적용
	// 소모성아이템이 아닌경우 false 반환, 아이템 효과적용 성공시 true 반환
	bool ItemEffect(ItemId Id);
	// ItemId를 인수로 장비효과 적용(삭제 안됨), Private 처리예정
	// 자동 장착 함수에서 호출함
	void applyEffect(ItemId test);
	// ItemId를 인수로 장비제거효과 적용(삭제 안됨), Private 처리예정
	// 자동해체 함수에서 호출함
	void RemoveEffect(ItemId test);
	
 

};

