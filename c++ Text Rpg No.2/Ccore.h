#pragma once

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
	NoDataFile,
	End = 10

};
// ++연산자 오버로딩, DataFile이 입력되면 다음 File로 이동하는 함수
// DataFile8이 들어오면 오류문구 출력후 그대로 반환함
inline DataFile& operator++(DataFile& File) {
	if (File == DataFile::NoDataFile) {
		std::cout << "DataFile8의 한계에 도달했습니다." << std::endl;
		return File;
	}
	else {
		File = static_cast<DataFile>(static_cast<int>(File) + 1);
	}
	return File;
}

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
	//Data File에 저장을 실행했는지 확인하는 변수 
	//기본값은 false, 저장시 true로 변환, DataFileSave함수를 통해 true변환해야됨
	//오류 발생시에 false값으로 변환됨
	bool	SaveThis;
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
	// Main Init 시 불러온 값에 따라 MaxDataInfo 초기화 하는 함수
	void	MaxDataInit();
	// Player 기본정보 Initial 진행 
	void	P_DataInit() { PlayerInfoLoding(LodingData(DataFile::BasicData)); };
	// Main 프로그램이 돌아가는 함수, 일단 여기서 모든 동작 진행하도록 하자
	void	Progress();
	// main 시작부 -> 플레이어 이름 정하기 및 기본 시작창 열기
	void	GameStartSet();
	// GameMode 설정
	void	G_M_Set();
	// Game StartSet 중 메뉴 출력
	void	GameStartSetOutPut();
	// Game Over 되는 함수
	void	GameOver() { GameOff = false; };
	// 전투화면으로 진행하는 함수
	void	BattleStartInit();
	// Game 난이도 설정하는 함수
	void	G_DifficultySeting();
	// Player Name 설정함수
	void	PlayerNameSeting();
public:		// 데이터 저장함수

	// 데이터 저장전 인테페이스 출력
	void	SelectSavePoint();
	// 원하는 데이터 입력값을 보여주는 함수(함수종합세트)
	void	Selectview() { DataFileView(LodingData(convert(CinAuto()))); }
	// Player Data를 보여주는 함수
	void	DataFileView(PlayerData data);

public:		// 데이터 저장함수
	// PlayerInfo 를 DataFile에 저장하는 함수
	void	DataFileSave(DataFile Data);
	// PlayerInfo를 CruData 에 저장하는 함수, 빠른저장
	void	CurDataSave() { DataFileSave(DataFile::CurData); }
	// DataFile을 PlayerInfo에 넣는 함수
	void	PlayerInfoLoding(PlayerData data) { PlayerInfo = data; }

public:
	// 플레이어 이어하기 선택시 데이터 어떤거 가져올지 물어보는 함수
	bool	SaveDataLoding();
	// PlayerInfo를 string으로 변환해서 반환하는 함수
	string  PlayInfoToSting();
	// 반환값으로 입력의 int값 받는 함수
	int		CinAuto();
	// DataFile을 PlayerData로 반환하는 함수
	PlayerData	LodingData(DataFile dataFile);

public:

	// DataFile 확인해서 해당 File이 오류가 있는지 확인하는 함수
	bool	CheckSavefile(DataFile dataFile);
	// 저장되어있는 데이터가 있는지 확인하는 함수, 있으면 있다고 알려줌
	bool	AllFileCheck();

public:
	// int를 Static_cast로 DataFile로 변환하는 함수
	DataFile convert(int value) {
		return static_cast<DataFile>(value);
	}
	// DataFile를 Static_cast로 int로 변환하는 함수
	int convert(DataFile dataFile) {
		return static_cast<int>(dataFile);
	}
	friend class EneMy;
};

