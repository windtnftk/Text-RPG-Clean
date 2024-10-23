#pragma once

enum class GameMode
{
	GameEnd,
	Easy,
	Normal,
	Hard,



	End = 10
};
struct PlayerData
{
	string	PlayerName;	//플레이어 이름
	int		Level;		//플레이어 레밸
	int		CurStage;	//플레이어가 진행한 스테이지 위치
};
// Main 설정 진행 장소 
class Ccore
{
	SINGLE(Ccore);
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
	// Player 정보를 저장하는 함수
	void	SaveGame();
	// Player 정보를 읽는 함수
	void	LoadGame();
	// 전투화면으로 진행하는 함수
	void	BattleStartInit();
	
	friend class EneMy;
};

