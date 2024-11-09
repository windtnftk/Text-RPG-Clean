#pragma once

struct E_Info;
struct E_Check;
struct B_Status;
enum class GameMode
{
	GameEnd,
	Easy,
	Normal,
	Hard,



	End = 10
};
enum class DataFile
{
	CurData,
	DataFile1,
	DataFile2,
	DataFile3,
	DataFile4,
	DataFile5,
	DataFile6,
	DataFile7,
	DataFile8,
	BasicData,
	End = 10

};
// ++연산자 오버로딩, DataFile이 입력되면 다음 File로 이동하는 함수
// DataFile8이 들어오면 오류문구 출력후 그대로 반환함
inline DataFile& operator++(DataFile& File) {
	if (File == DataFile::BasicData) {
		std::cout << "DataFile의 한계에 도달했습니다." << std::endl;
		return File;
	}
	else {
		File = static_cast<DataFile>(static_cast<int>(File) + 1);
	}
	return File;
}
// 장비 같은 지속효과 관리 다른 계산할떄 항상 포함
// but 데이터저장시에는 미 포함, 후에 독같은 추가 효과 제공 예정
struct LastingEffect
{
	int		Power;		//지속 공격력 증가량
	int		Defense;	//지속 방어력 증가량
	int		Barrier;	//전투함수 중 순간 보호막 효과 발휘
};
struct Attribute {
	enum class AttackType {
		Blunt,  // 타격
		Pierce,  // 관통
		Slash    // 참격
	};

	AttackType attackType;
	// 다른 속성이나 변수 추가 가능
};

struct PlayerData
{
	string	PlayerName;	//플레이어 이름
	int		Level;		//플레이어 레밸, 레벨에 비레해 경험치 흭득양 정해짐
	int		Power;		//플레이어 공격력
	int		Defense;	//플레이어 방어력
	int		Health;		//플레이 체력
	int		Exp;		//플레이어 경험치
	int		Money;		//플레이어 돈
	int		CurStage;	//플레이어가 진행한 스테이지 위치
	//Data File에 저장을 실행했는지 확인하는 변수 
	//기본값은 false, 저장시 true로 변환, DataFileSave함수를 통해 true변환해야됨
	//오류 발생시에 false값으로 변환됨
	bool	SaveThis;
};
// 컴파일 타임 상수, 레벨업시 현재레벨 과 곱해서 최대 Exp를 만드는 상수값
constexpr int Multiplier = 20;  
// Main 설정 진행 장소 
class Ccore
{
	friend class EneMy;
	friend class MainItem;
	SINGLE(Ccore);
	PlayerData	MaxDataInfo; //플레이어 최대 값
	// 예) PlayerInfo의 경험치가 MaxDataInfo에 있는 경험치보다 높아지면 레벨업
	PlayerData	PlayerInfo; // 플레이어 정보
	GameMode	ModeCur; // 현재 설정한 모드로 진행
	LastingEffect lasting;// 지속중인 효과들 계산


public:		// 기본 Init관련 함수

	// Main 프로그램이 돌아가는 함수, 일단 여기서 모든 동작 진행하도록 하자
	void	Progress();
	// Main 프로그램이 시작하기전 초기값 설정
	void	Init();
	// Main Init 시 불러온 값에 따라 MaxDataInfo 초기화 하는 함수
	// LevelUp후 MaxDataInfo 초기화
	void	MaxDataInit();
	// Player 기본정보 Initial 진행 
	void	P_DataInit() { PlayerInfoLoding(LodingData(DataFile::BasicData)); }


public:		//게임 시작부관련함수

	// main 시작부 -> 플레이어 이름 정하기 및 기본 시작창 열기
	void	GameStartSet();
	// Game StartSet 중 메뉴 출력
	void	GameStartSetOutPut();
	// Game Over 되는 함수
	void	GameOver() { GameOff = false; }


public:		// 설정관련 함수

	// GameMode 설정
	void	G_M_Set();
	// Game 난이도 설정하는 함수
	void	G_DifficultySeting();
	// Player Name 설정함수
	void	PlayerNameSeting();


public:		//	전투후 처리 함수
	//	보상 흭득, 레벨업조건 확인 및 적용
	void	BattleAfter(E_Check Info);
	// 보상 얻은후 다음스테이지로 이동
	void	NextStage();

public:		// 레벨업 전담 함수

	// 보상얻는 함수, 적의 데이터 받아서 경험치만 얻는 함수
	// 후에 아이템이나 추가효과 얻게 바꿀예정(24.11.08 미적용)
	void	RewardCheck(B_Status Reward);
	// 경험치 보상 및 Exp 넘었는지 총괄 함수
	void	RewardExp(B_Status Reward);
	// 경험치 보상후 레벨업 Check 및 얼마나 남았는지 Check
	void	LevelUpCheck();
	// 최대 Exp값 조정작업
	void	MaxExpConnect();
	// 레벨업 시 알림, Init시에는 ㄴㄴ
	void	LevelUpView();
	// 레벨업 후 조정작업
	// 이걸로 평균 만들자
	void	L_Upstatus();

	// 전투처리 함수
public:		
	// 전투화면으로 진행하는 함수
	// 반환값을 bool값으로 줄수 있으니까
	// 플레이어 사망, 각종 이유로 죽으면 false(지금은 PlayerLifeCheck로 확인)
	// 기본으로는 true로 반환하도록 해서 일관성을 주자(24.11.08 미적용)
	E_Check	BattleStartInit();
	// 플레이어 상태값 출력, 전투중
	// 이름, 레벨, 공격력, 방어력, 체력, 현재 경험치, 필요 경험치
	void	PlayerInfoView();
	// 적이 피해받는 함수, 플레이어 공격력 만큼만 데미지 받음
	// 추후에 다른 계산 필요
	E_Info Hitdamage(E_Info Info);
	// 적의 공격을 총괄하는 함수
	// 적 공격으로 플레이어 사망시 false 반환
	// ㄴ 이 기능 없앰
	bool	EnemyTurn(E_Info Info);
	// 적 입력시 적의 공격력 참고하여 플레이어에게 데미지입힘
	// 방어력 계산 X
	void EnemyAttack(E_Info Info);
	// 내가 죽었는지 확인하는 함수
	bool PlayerLifeCheck();
public:
	// 집적적으로 상대에게 추가뎀(보류)
	
	// 전투 후 강화상태 풀기 진행해야됨
	void PowerUp(int test) { PlayerInfo.Power += test; } //PowerUp
	void DefenseUp(int test) { PlayerInfo.Defense += test; } //DefenseUp
	void LimitHealthUp(int test); //최대 체력 확인해서 한계치 까지만 회복

	// 여기서 부터는 지속효과 적용, 장비 장착함수들은 여기를 호출할 예정
	// 여기서 int값 대신 enum class 만들어서 희귀도에 따라 효과 적용되는 양이
	// 다르게 만들게 하면 좋을거 같음 ㅇㅇ
	// 예))1번 무기는 노말 공업, 10번 무기는 전설등급 공업 + 추가효과 이런식으로

	void Newbarrier(int test);//방어막 생성
	void AddPowerUp(int test);//지속 공격력 생성
	void AddDefenseUp(int test);//지속 방어력 생성
	// 지속 효과 제거 (나중에 int대신 enum 넣자), 음수 까지 허용으로 하자
	void Removebarrier(int test);//방어막 생성
	void RemovePowerUp(int test);//지속 공격력 생성
	void RemoveDefenseUp(int test);//지속 방어력 생성
	
public:		// 데이터 저장

	// 데이터 저장전 인테페이스 출력
	void	SelectSavePoint();
	// PlayerInfo 를 DataFile에 저장하는 함수
	void	DataFileSave(DataFile Data);
	// PlayerInfo를 CruData 에 저장하는 함수, 빠른저장
	void	CurDataSave() { DataFileSave(DataFile::CurData); }

public:		// 데이터 불러오기

	// 플레이어 이어하기 선택시 데이터 어떤거 가져올지 물어보는 함수
	// Save된 데이터가 없을때, 선택한 데이터로 안한다고 할때 false 반환
	bool	SaveDataLoding();
	// Player Data를 보여주는 함수
	PlayerData	DataFileView(PlayerData data);
	// 데이터 입력후 파일을 보여주는 함수(함수종합세트)
	PlayerData	Selectview() { return DataFileView(LodingData(convert(CinAuto()))); }
	// PlayerData을 PlayerInfo에 넣는 함수
	void	PlayerInfoLoding(PlayerData data) { PlayerInfo = data; }

public:		// Auto 용

	// PlayerInfo를 string으로 변환해서 반환하는 함수
	string  PlayInfoToSting();
	// DataFile을 PlayerData로 반환하는 함수
	PlayerData	LodingData(DataFile dataFile);

public:		//오류체크용

	// 오류 및 저장한파일이 없는지 확인 함수, 있으면 있다고 알려줌
	// CheckSavefile 을 반복문 돌림, 0번 부터(curData부터 순회)
	bool	AllFileCheck();
	// DataFile 확인해서 해당 File이 오류가 있는지 확인하는 함수
	bool	CheckSavefile(DataFile dataFile);

public:		// 변환함수
	// int를 Static_cast로 DataFile로 변환하는 함수
	DataFile convert(int value) {
		return static_cast<DataFile>(value);
	}
	// DataFile를 Static_cast로 int로 변환하는 함수
	int convert(DataFile dataFile) {
		return static_cast<int>(dataFile);
	}

};

