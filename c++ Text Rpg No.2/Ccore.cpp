#include "pch.h"
#include "Ccore.h"
#include "Item.h"
#include "Enemy.h"
#include "Equipment.h"

void Ccore::Init()
{
	if (ModeCur != GameMode::GameEnd)
	{
		Ccore::MaxDataInit();
		MainItem::GetInst()->ItemInit();
		EneMy::GetInst()->EnemyInit();
		EneMy::GetInst()->ViewEnemy();
	}

}
void Ccore::MaxDataInit()
{
	MaxDataInfo = PlayerInfo;
	MaxDataInfo.Exp = PlayerInfo.Level *20;
}
void Ccore::BattleStartInit()
{
	while (true)
	{
		bool End = true;
		while (End)
		{
			EneMy::GetInst()->SetEnemyInfo();
			std::cout << "[1.일반공격]" << " [2.아이템사용] " << "[3.상태창]" << std::endl << std::endl;
			switch (CinAuto())
			{
			case 1:

				End = false;
				break;
			case 2:


				break;
			case 3:


				break;
			default:
				ErrorCode();
				break;
			}
		}
	}
}


void Ccore::Progress()
{
	EneMy::GetInst()->ViewEnemy();
	//MainItem::GetInst()->OpenItemBag();
	SelectSavePoint();
	SaveDataLoding();
	//CurDataSave();
}
void Ccore::GameStartSetOutPut()
{
	std::cout << "<게임 메인 화면>" << std::endl << std::endl;
	std::cout << "1. 게임 시작" << std::endl;
	std::cout << "2. 게임 이어하기" << std::endl;
	std::cout << "3. 설정" << std::endl;
	std::cout << "4. 종료" << std::endl;
}
void Ccore::G_M_Set()
{
	bool End = true;
	while (End)
	{
		std::cout << "1. 게임 난이도 변경" << std::endl;
		std::cout << "2. 플레이어 이름 변경" << std::endl;
		switch (CinAuto())
		{
		case 1:
			std::cout << "1. 게임 난이도 변경합니다." << std::endl << std::endl;
			G_DifficultySeting();
			End = false;
			break;
		case 2:
			std::cout << "2. 플레이어 이름 변경합니다." << std::endl << std::endl;
			PlayerNameSeting();
			End = false;
			break;
		default:
			ErrorCode();
			break;
		}
	}
}
void Ccore::G_DifficultySeting()
{
	bool End = true;
	while (End)
	{
		std::wcout << L"\n난이도를 정하십시오\n" << std::endl;
		std::cout << "1. Easy" << std::endl;
		std::cout << "2. Normal" << std::endl;
		std::cout << "3. Hard" << std::endl;
		switch (CinAuto())
		{
		case 1:
			std::cout << "게임 난이도를 Easy 로 설정합니다." << std::endl;
			End = false;
			ModeCur = GameMode::Easy;
			break;
		case 2:
			std::cout << "게임 난이도를 Normal 로 설정합니다." << std::endl;
			End = false;
			ModeCur = GameMode::Normal;
			break;
		case 3:
			std::cout << "게임 난이도를 Hard 로 설정합니다." << std::endl;
			End = false;
			ModeCur = GameMode::Hard;
			break;
		default:
			ErrorCode();
			break;
		}

	}
}
void Ccore::PlayerNameSeting()
{

	string NewName = {};
	string input;
	string boolinput;


	bool YesName = true;
	while (YesName) // 캐릭터 이름 생성 함수
	{
		NewName = PlayerInfo.PlayerName;
		std::wcout << L"\n새로운 이름을 입력하세요\n";
		std::wcin.ignore(); //입력 창 초기화(get line 작동을 위해 한번 비워줌)
		std::getline(std::cin, input);

		if (!input.empty())  // 입력이 비어있지 않은 경우
		{
			NewName = input; // 입력된 이름 사용
		}

		// 다시확인 창, yes 입력 시 이름 쓰는 반복문 종료
		// no 입력 시 이름 다시 쓰고 다시 확인창 반복
		// 다른거 작동시 다시 확인창 시작
		while (true)
		{
			std::cout << std::endl << "정말로 " << NewName << "이(가) 맞습니까?" << std::endl;// 다시확인 창
			std::cout << "yes 또는 no를 입력해주십시오" << std::endl;
			std::cin >> boolinput;
			for (char& c : boolinput)
			{
				c = std::tolower(c);
			}
			if ("yes" == boolinput)
			{
				YesName = false;
				break;
			}
			else if ("no" == boolinput)
			{
				break;
			}
			else
			{
				ErrorCode();
			}
		}
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	Ccore::GetInst()->PlayerInfo.PlayerName = NewName;
}
void Ccore::DataFileSave(DataFile Data)
{
	if (Data == DataFile::End || Data == DataFile::BasicData)
	{
		std::cout << "잘못된 데이터 파일입니다." << std::endl;
	}
	std::fstream file("PlayerData.txt", std::ios::in | std::ios::out);

	if (!file.is_open() || Data == DataFile::BasicData) {
		std::cerr << "파일을 열 수 없습니다.\n";
		return;
	}
	string CurData = PlayInfoToSting();
	// 파일에서 데이터를 수정할 위치 계산
	int lineNumber = convert(Data);  // enum 값에 따라 라인 번호 결정
	std::string line;
	int currentLine = 0;

	// 임시 파일에 데이터 복사 및 수정
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "임시 파일을 생성할 수 없습니다.\n";
		file.close();
		return;
	}

	while (std::getline(file, line)) {
		if (currentLine == lineNumber + 4) {
			tempFile << lineNumber << "%" << CurData << "\n";
			// 현재 데이터를 해당 라인에 저장
		}
		else {
			tempFile << line << "\n";  // 기존의 다른 라인은 그대로 유지
		}
		currentLine++;
	}
	// 파일 정리
	file.close();
	tempFile.close();
	// 원본 파일을 덮어쓰기
	if (std::remove("PlayerData.txt") != 0) {
		std::cerr << "원본 파일을 삭제하는 중 오류가 발생했습니다.\n";
		return;
	}
	if (std::rename("temp.txt", "PlayerData.txt") != 0) {
		std::cerr << "임시 파일을 원본 파일로 이름 변경하는 중 오류가 발생했습니다.\n";
	}
	std::cout << "데이터가 저장되었습니다 (슬롯: " << lineNumber << ").\n";
}
void Ccore::SelectSavePoint()
{
	if (!AllFileCheck())
	{
		std::cout << "저장된 플레이어 데이터가 없습니다." << std::endl;
	}
	std::cout << std::endl << "몇번 폴더에 저장 하시겠습니까?" << std::endl;
	std::cout << std::endl << "1~8번 파일에 저장하세요" << std::endl;
	std::cout << "0번 파일 = 빠른저장파일" << std::endl;
	DataFileSave(convert(CinAuto() + 1));
}
//DataFile Ccore::intToDfile(int data)
//{
//	if (data < 1 || data > convert(DataFile::End)) {
//		throw std::out_of_range("Invalid");
//		return DataFile::End;
//	}
//	return convert(data);
//}
int Ccore::CinAuto() {
	int choice;
	while (true) {
		std::cout << "숫자를 입력하세요: ";
		std::cin >> choice;
		if (std::cin.fail()) {
			// 잘못된 입력이 발생했을 경우
			std::cin.clear(); // cin의 오류 상태 플래그를 초기화
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 입력 버퍼를 비웁니다.
			std::cout << "잘못된 입력입니다.\n";
		}
		else
		{
			// 유효한 입력이 들어왔을 경우
			return choice; // 정상적인 경우 반복 종료 후 값 반환
		}
	}
}
string Ccore::PlayInfoToSting()
{
	return PlayerInfo.PlayerName
		+ ", " + std::to_string(PlayerInfo.Level)
		+ ", " + std::to_string(PlayerInfo.Power)
		+ ", " + std::to_string(PlayerInfo.Defense)
		+ ", " + std::to_string(PlayerInfo.Health)
		+ ", " + std::to_string(PlayerInfo.Exp)
		+ ", " + std::to_string(PlayerInfo.Money)
		+ ", " + std::to_string(PlayerInfo.CurStage)
		+ "$ " + std::to_string(1) + "!";
}
void Ccore::GameStartSet()
{
	bool End = true;
	while (End)
	{
		std::cout << "1. 게임 시작" << std::endl;
		std::cout << "2. 게임 이어하기" << std::endl;
		std::cout << "3. 설정 변경하기" << std::endl;
		std::cout << "4. 게임 종료하기" << std::endl;
		int input = 0;
		std::cin >> input;
		// 이름 가져오는거 진행 ㄱ~~~
		switch (input)
		{
		case 1:
			std::cout << "게임을 시작합니다." << std::endl;
			P_DataInit();
			End = false;

			break;
		case 2:
			std::cout << "게임을 이어합니다." << std::endl;
			End = !SaveDataLoding();
			break;
		case 3:
			std::cout << "설정을 변경합니다." << std::endl;
			// 설정창 열기 진행 예정
			G_M_Set();
			break;
		case 4:
			GameOver();
			ModeCur = GameMode::GameEnd;
			End = false;
			break;
		default:
			ErrorCode();
			break;
		}
	}
}
PlayerData Ccore::LodingData(DataFile dataFile)
{
	std::ifstream inputFile("PlayerData.txt");
	std::string line;
	std::string check = std::to_string(convert(dataFile));
	PlayerData Data;
	if (!inputFile.is_open()) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		Data.SaveThis = false;
		return Data;
	}
	while (std::getline(inputFile, line)) {
		if (line.empty() || line[0] == '#' || line[0] != check[0]) continue;
		// 주석, 맞지 않는 값 무시

		std::istringstream ss(line);  // 읽어온 줄을 스트림으로 변환
		std::string token;
		getline(ss, token, '%'); getline(ss, Data.PlayerName, ','); // 이름 읽기
		getline(ss, token, ','); Data.Level = stoi(token);  // 레벨 읽기
		getline(ss, token, ','); Data.Power = stoi(token);	// 힘 읽기
		getline(ss, token, ','); Data.Defense = stoi(token); // 방어력 읽기
		getline(ss, token, ','); Data.Health = stoi(token);	// 체력 읽기
		getline(ss, token, ','); Data.Exp = std::stoi(token);  // 경험치 읽기
		getline(ss, token, ','); Data.Money = std::stoi(token);  // 돈 읽기
		getline(ss, token, '$'); Data.CurStage = std::stoi(token);  // 진행도 읽기
		getline(ss, token, '!'); Data.SaveThis = std::stoi(token);  // 오류 검출
	}
	inputFile.close();
	return Data;
}
bool Ccore::SaveDataLoding()
{
	if (!AllFileCheck())
	{
		std::cout << "저장된 플레이어 데이터가 없습니다." << std::endl;
		return false;
	}
	std::cout << std::endl << "몇번 폴더를 로딩하시겠습니까?" << std::endl;
	std::cout << std::endl << "1~8번 파일중 선택하세요" << std::endl;
	//std::cout << "0번 파일 = 빠른저장파일" << std::endl;
	//SaveDataView(SaveDataView(convert(CinAuto())));
	std::cout << "저장된 플레이어 정보 입니다." << std::endl;
	Selectview();// 선택하고 선택한 데이터 보여주기
	return true;
}
void Ccore::DataFileView(PlayerData data)
{

	if (!data.SaveThis)
	{
		std::cout << "플레이어 이름: " << data.PlayerName << std::endl;
		std::cout << "플레이어 레벨: " << data.Level << std::endl;
		std::cout << "플레이어 힘: " << data.Power << std::endl;
		std::cout << "플레이어 방어력: " << data.Defense << std::endl;
		std::cout << "플레이어 체력: " << data.Health << std::endl;
		std::cout << "플레이어 경험치 보유량: " << data.Exp << std::endl;
		std::cout << "플레이어 소지금: " << data.Money << std::endl;
		std::cout << "플레이어 진행중인 스테이지: " << data.CurStage << std::endl;
	}
	else
	{
		std::cout << "값을 읽어 오는데 실패했습니다." << std::endl;
	}
}
bool Ccore::CheckSavefile(DataFile dataFile)
{
	std::ifstream inputFile("PlayerData.txt");
	std::string line;
	std::string check = std::to_string(convert(dataFile));
	if (!inputFile.is_open()) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	while (std::getline(inputFile, line)) {
		if (line.empty() || line[0] == '#' || line[0] != check[0]) continue;
		// 주석, 맞지 않는 값 무시

		std::istringstream ss(line);  // 읽어온 줄을 스트림으로 변환
		std::string token;
		getline(ss, token, '$'); getline(ss, token, '!');
		inputFile.close();
		return stoi(token);
	}
	inputFile.close();
	return false;
}
bool Ccore::AllFileCheck()
{
	bool test = 0;
	for (DataFile i = DataFile::DataFile1; i <= DataFile::DataFile8; ++i)
	{
		if (CheckSavefile(i))
		{
			if (!test)
			{
				std::cout << "저장되어 있는 File" << std::endl;
				test = 1;
			}
			std::cout << "Datafile " << convert(i) << ", ";
		}
	}
	std::cout << std::endl;
	return test;
}

Ccore::Ccore()
	:PlayerInfo{}
	, ModeCur(GameMode::Normal)
{
}
Ccore::~Ccore()
{

}