#pragma once

enum class GameMode
{
	GameEnd,
	Easy,
	Normal,
	Hard,



	End = 10
};
enum class PlayerDataSet
{
	BasicData,
	CurData,
	DataFile1,
	DataFile2,
	DataFile3,
	DataFile4,
	DataFile5,
	DataFile6,
	DataFile7,
	DataFile8,
	End =10
};
struct PlayerData
{
	string	PlayerName;	//플레이어 이름
	int		Level;		//플레이어 레밸, 레벨에 비레해 경험치 흭득양 정해짐
	int		Power;		//플레이어 힘
	int		Defense;	//플레이어 방어력
	int		Health;		//플레이 체력
	int		Exp;		//플레이어 경험치
	int		Money;		//플레이어 돈
	int		CurStage;	//플레이어가 진행한 스테이지 위치
};
// Main 설정 진행 장소 
class Ccore
{
	SINGLE(Ccore);
	PlayerData	MaxDataInfo; //플레이어 최대 값
	// 예) PlayerInfo의 경험치가 MaxDataInfo에 있는 경험치보다 높아지면 레벨업
	PlayerData	PlayerInfo; // 플레이어 정보
	GameMode	ModeCur; // 현재 설정한 모드로 진행
	

public:
	// Main 프로그램이 시작하기전 초기값 설정
	void	Init();
	// Player 기본정보 Initial 진행 
	void	P_DataInit();
	// Main 프로그램이 돌아가는 함수, 일단 여기서 모든 동작 진행하도록 하자
	void	Progress();
	// main 시작부 -> 플레이어 이름 정하기 및 기본 시작창 열기
	void	GameStartSet();
	// 플레이어 진행사항 정보 가져오는 함수
	void	LodingData(PlayerDataSet data);
	// 플레이어 이어하기 선택시 데이터 어떤거 가져올지 물어보는 함수
	void	SaveDataLoding();
	// 플레이어 데이터저장 한걸 보여주는 함수 <== 진행예정 (24.10.27)
	void	SaveDataView(PlayerDataSet data);
	// Game Over 되는 함수
	void	GameOver() { GameOff = false; };
	// Game StartSet 중 메뉴 출력
	void	GameStartSetOutPut();
	// GameMode 설정
	void	G_M_Set();
	// Game 난이도 설정하는 함수
	void	G_DifficultySeting();
	// Player Name 설정함수
	void	PlayerNameSeting();
	// 데이터 저장전 인테페이스 출력
	void	SelectSavePoint();
	// int 인자를 PlayerDataSet으로 변경함수
	PlayerDataSet intToPds(int data);
	// PlayerInfo 를 PlayerDataSet에 저장하는 함수
	void	DataFileSave(PlayerDataSet Data);
	// PlayerInfo를 CruData 에 저장하는 함수, 빠른저장
	void	CurDataSave() { DataFileSave(PlayerDataSet::CurData); }
	// PlayerInfo를 string으로 변환해서 반환하는 함수
	string  PlayInfoToSting();
	// 반환값으로 입력의 int값 받는 함수
	int		CinAuto();
	// 전투화면으로 진행하는 함수
	void	BattleStartInit();
	
	friend class EneMy;
};

