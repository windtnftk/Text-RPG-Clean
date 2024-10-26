#include "pch.h"
#include "Ccore.h"
#include "Item.h"
#include "Enemy.h"
#include "Equipment.h"

void Ccore::Init()
{
	if (Ccore::GetInst()->ModeCur != GameMode::GameEnd)
	{
		Equipment::GetInst()->ItemInit();
		EneMy::GetInst()->EnemyInit();
		EneMy::GetInst()->ViewEnemy();
	}
	
}

void Ccore::P_DataInit()
{
	Ccore::GetInst()->PlayerInfo = { "Player 1", 1,0 };
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
			int input = 0;
			std::cin >> input;
			// 이름 가져오는거 진행 ㄱ~~~
			switch (input)
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
		int input = 0;
		std::cin >> input;
		// 이름 가져오는거 진행 ㄱ~~~
		switch (input)
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
	int input = 0;
	bool End = true;
	while (End)
	{
		std::wcout << L"\n난이도를 정하십시오\n" << std::endl;
		std::cout << "1. Easy" << std::endl;
		std::cout << "2. Normal" << std::endl;
		std::cout << "3. Hard" << std::endl;
		
		std::wcin >> input;
		switch (input)
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
		NewName = Ccore::GetInst()->PlayerInfo.PlayerName;
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
void Ccore::SaveGame()
{	
	std::ofstream outFile("savegame.txt"); // 출력 스트림 생성

	if (outFile.is_open()) { // 파일이 정상적으로 열렸는지 확인
		outFile << Ccore::GetInst()->PlayerInfo.PlayerName << std::endl; // 플레이어 이름 저장
		outFile << Ccore::GetInst()->PlayerInfo.Level << std::endl;      // 레벨 저장
		outFile << Ccore::GetInst()->PlayerInfo.CurStage << std::endl;   // 스테이지 저장
		outFile.close(); // 파일 닫기
		std::cout << "Game saved successfully." << std::endl;
	}
	else 
	{
		std::cerr << "Unable to open file for writing" << std::endl; // 파일 열기 실패 시 에러 메시지 출력
	}	
}
void Ccore::LoadGame()
{
	std::ifstream inFile("savegame.txt");
	if (inFile.is_open())
	{
		std::getline(inFile, Ccore::GetInst()->PlayerInfo.PlayerName);
		inFile >> Ccore::GetInst()->PlayerInfo.Level;
		inFile >> Ccore::GetInst()->PlayerInfo.CurStage;
		inFile.close();
	}
	else
	{
		std::cerr << "Unable to open file for reading" << std::endl;
	}
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
			End = false;
			
			break;
		case 2:
			std::cout << "게임을 이어합니다." << std::endl;
			End = false;
			// 아직 구현 X
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
Ccore::Ccore()
	:PlayerInfo{}
	, ModeCur(GameMode::Normal)
{
}
Ccore::~Ccore()
{

}