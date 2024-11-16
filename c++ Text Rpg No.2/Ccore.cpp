#include "pch.h"
#include "Ccore.h"
#include "Item.h"
#include "Enemy.h"
#include "Equipment.h"
#include "Attribute.h"
#include "Attribute.h"
void Ccore::Progress()
{
	if (!GameOff)// 도는중에 gameOff가 작동하면 바로 끝내도록 함
	{
		return;
	}
	//EneMy::GetInst()->ViewEnemy();
	//MainItem::GetInst()->OpenItemBag();
	//SelectSavePoint();
	//SaveDataLoding();
	//CurDataSave();
	BattleAfter(BattleStartInit());
}
void Ccore::Init()
{
	if (ModeCur != GameMode::GameEnd)
	{
		ATinit();
		MaxDataInit();
		MainItem::GetInst()->ItemInit();
		EneMy::GetInst()->EnemyInit();
		//EneMy::GetInst()->ViewEnemy();
	}
}
void Ccore::MaxDataInit()
{
	MaxDataInfo = PlayerInfo;
	MaxExpConnect();
}
void Ccore::ATinit()
{
	PlayerAT.SetRL(AttackType::Blunt, ResistanceLevel::Weak);
	PlayerAT.SetRL(AttackType::Pierce, ResistanceLevel::Weak);
	PlayerAT.SetRL(AttackType::Slash, ResistanceLevel::Weak);
	PlayerAT.My_AT = AttackType::Blunt;
}
void Ccore::GameStartSet()
{
	bool End = true;
	while (End)
	{
		GameStartSetOutPut();
		switch (CinAuto())
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
		YesName = false;
		// 다시확인 창, yes 입력 시 이름 쓰는 반복문 종료
		// no 입력 시 이름 다시 쓰고 다시 확인창 반복
		// 다른거 작동시 다시 확인창 시작
		std::cout << std::endl << "정말로 " << NewName << "이(가) 맞습니까?" << std::endl;// 다시확인 창
		if (Yes_No) return; // yes입력시 함수 종료,no 입력시 while문 반복
	}
	Ccore::GetInst()->PlayerInfo.PlayerName = NewName;
}
void Ccore::BattleAfter(E_Check Info)
{
	if (!Info.Check) {
		std::cout << "플레이어가 죽었습니다." << std::endl; return;
	} // 반환값이 false면 보상 못얻고 종료
	RewardCheck(Info.Info);
	NextStage();
}
void Ccore::NextStage()
{
	++PlayerInfo.CurStage;
	++MaxDataInfo.CurStage;
	++EneMy::GetInst()->E_Point;
}
void Ccore::RewardCheck(B_Status Reward)
{
	RewardExp(Reward);

}
void Ccore::RewardExp(B_Status Reward)
{
	PlayerInfo.Exp += Reward.C_Exp;
	LevelUpCheck();
}
void Ccore::LevelUpCheck()
{
	if (PlayerInfo.Exp < MaxDataInfo.Exp) return;
	// 최대 Exp보다 현재 Exp가 클경우 반복해서 레벨업
	while (PlayerInfo.Exp > MaxDataInfo.Exp)
	{
		PlayerInfo.Exp -= MaxDataInfo.Exp;
		++PlayerInfo.Level;
		++MaxDataInfo.Level;
		MaxExpConnect();
		LevelUpView();
	}
	std::cout << "현재 레벨: " << PlayerInfo.Level << std::endl;
	L_Upstatus();
}
void Ccore::MaxExpConnect()
{
	MaxDataInfo.Exp = PlayerInfo.Level * Multiplier;
}
void Ccore::LevelUpView()
{
	std::cout << "!!!레벨업!!!" << std::endl;
}
void Ccore::L_Upstatus()
{
	auto test = PlayerInfo.Level;
	PlayerInfo.Power = Multiplier * test;
	PlayerInfo.Defense = Multiplier * test;
	PlayerInfo.Health = Multiplier * test;
	MaxDataInit();
}
void Ccore::SkillUpCheck()
{
	// for문 넣어서 Attack type만큼 순회
	if( 500 > PD_to_SP())
}
E_Check Ccore::BattleStartInit()
{
	E_Info test = EneMy::GetInst()->SetEnemyInfo();
	// 적 또는 플레이어가 사망해야 반복문이 끝남
	// 플레이어, 적의 체력이 다 떨어지면 자동으로 반복문 off
	while (EneMy::GetInst()->DeadCheck(test) && PlayerLifeCheck())
	{
		EneMy::GetInst()->printCurInfo(test);
		// 플레이어 턴
		bool End = true;
		while (End)
		{
			std::cout << std::endl << "[1.일반공격]" << " [2.아이템사용] " << "[3.상태창]" << std::endl << std::endl;
			switch (CinAuto())
			{
			case 1:
				test = Hitdamage(test);
				End = false;
				break;
			case 2:
				MainItem::GetInst()->UseItemManuOpen();
				break;
			case 3:
				PlayerInfoView();
				break;
			default:
				ErrorCode();
				break;
			}
		}// 플레이어 턴 종료
		if (!EneMy::GetInst()->DeadCheck(test)) //적 생존여부 체크
		{//리턴값을 적 정보, ID로 해서 적 싸운후 리턴값으로 처치 보상받자
			return { test.E_BInfo, PlayerLifeCheck() };
			//if (!EnemyTurn(test))
			//{
			//	// 리턴값을 적정보랑 실패했다는 반환값을 넣자,인수 2개
			//	GameOver();
			//	return { test.E_BInfo, PlayerLifeCheck() };
			//};
		}
		EnemyTurn(test);// 적 턴 시작
	}
	return { test.E_BInfo, PlayerLifeCheck() };
}
void Ccore::PlayerInfoView()
{
	std::cout << "이름: " << PlayerInfo.PlayerName << std::endl;
	std::cout << "레벨: " << PlayerInfo.Level << std::endl;
	std::cout << "공격력: " << PlayerInfo.Power << std::endl;
	std::cout << "방어력: " << PlayerInfo.Defense << std::endl;
	std::cout << "체력: " << PlayerInfo.Health << std::endl;
	std::cout << "현재 경험치: " << PlayerInfo.Exp << std::endl;
	std::cout << "필요 경험치: " << MaxDataInfo.Exp << std::endl;
}
E_Info Ccore::Hitdamage(E_Info Info)
{
	if (Info.E_BInfo.C_Health > 0) // 적이 살아야 내가 공격함
	{
		// 고민 적에게 가한 실제 피해량의 1/10을 경험치로 얻고싶어
		// 그러면 applydamage를 반환값으로 받아, 그 후 현재 공격 타입만큼 플레이어정보에
		// 숙련도에 넣어 그 후에 숙련도 업 함수로 체크해 ㅇㅇ
		applydamage(Info, R_Hitdamage(Info));
		Damage_to_SPUP(PlayerAT.My_AT,R_Hitdamage(Info));
	}
	return Info;
}
int Ccore::R_Hitdamage(E_Info Info)
{
	return Info.attribute.calculateDamage(PlayerInfo.Power, PlayerAT.My_AT);
}
void Ccore::applydamage(E_Info Info, int damage)
{
	std::cout << damage << "의 피해를 입혔습니다." << std::endl;
	Info.E_BInfo.C_Health -= damage;
}
bool Ccore::EnemyTurn(E_Info Info)
{
	EnemyAttack(Info);
	return true;

}
void Ccore::EnemyAttack(E_Info Info)
{
	std::cout << Info.E_BInfo.C_Name << "의 공격 !!!" << std::endl;
	PlayerHit(R_EnemyDamage(Info));
}
int Ccore::R_EnemyDamage(E_Info Info)
{
	return PlayerAT.calculateDamage(Info.E_BInfo.C_Power,Info.attribute.My_AT);
}
void Ccore::PlayerHit(int damage)
{
	std::cout << damage << "의 피해를 입었습니다." << std::endl;
	PlayerInfo.Health -= damage;
}
bool Ccore::PlayerLifeCheck()
{
	if (PlayerInfo.Health < 0)
	{
		//std::cout << "플레이어가 죽었습니다." << std::endl;
		return false;
	}
	return true;
}
#pragma region ItemEffect
void Ccore::LimitHealthUp(int test)
{
	if (PlayerInfo.Health + test > MaxDataInfo.Health)
	{
		PlayerInfo.Health = MaxDataInfo.Health;
	}
	else
	{
		PlayerInfo.Health += test;
	}
}
void Ccore::Newbarrier(int test)
{
	lasting.Barrier += test;
}

void Ccore::AddPowerUp(int test)
{
	lasting.Power += test;
}

void Ccore::AddDefenseUp(int test)
{
	lasting.Defense += test;
}

void Ccore::Removebarrier(int test)
{
	lasting.Barrier -= test;
}

void Ccore::RemovePowerUp(int test)
{
	lasting.Power -= test;
}

void Ccore::RemoveDefenseUp(int test)
{
	lasting.Defense -= test;
}
#pragma endregion
void Ccore::SelectSavePoint()
{
	if (!AllFileCheck())
	{
		std::cout << "저장된 플레이어 데이터가 없습니다." << std::endl;
	}
	std::cout << std::endl << "몇번 폴더에 저장 하시겠습니까?" << std::endl;
	std::cout << std::endl << "1~8번 파일에 저장하세요" << std::endl;
	std::cout << "0번 파일 = 빠른저장파일" << std::endl;
	DataFileSave(convert(CinAuto()));
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
	int lineNumber = convert(Data);  // enum 값에 따라 라인 번호 결정
	std::string line;
	// 임시 파일에 데이터 복사 및 수정
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "임시 파일을 생성할 수 없습니다.\n";
		file.close();
		return;
	}
	std::string check = std::to_string(lineNumber);
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#' || line[0] != check[0])
		{
			tempFile << line << "\n";  // 기존의 다른 라인은 그대로 유지
			continue;
		}
		tempFile << lineNumber << "%" << PlayInfoToSting() << "\n";// 현재 데이터를 해당 라인에 저장
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
	PlayerData Test = Selectview();
	if (Test.SaveThis) // 선택하고 선택한 데이터 보여주기
	{
		string boolinput;
		while (true)
		{
			std::cout << "이 로딩파일로 이어하시겠습니까?" << std::endl;
			std::cout << "yes 또는 no를 입력해주십시오" << std::endl;
			std::cin >> boolinput;
			for (char& c : boolinput)
			{
				c = std::tolower(c);
			}
			if ("yes" == boolinput)
			{
				PlayerInfoLoding(Test);
				return true;
			}
			else if ("no" == boolinput)
			{
				return false;
			}
			else
			{
				ErrorCode();
			}
		}
	}
	return false;
}
PlayerData Ccore::DataFileView(PlayerData data)
{

	if (data.SaveThis)
	{
		std::cout << "플레이어 이름: " << data.PlayerName << std::endl;
		std::cout << "플레이어 레벨: " << data.Level << std::endl;
		std::cout << "플레이어 힘: " << data.Power << std::endl;
		std::cout << "플레이어 방어력: " << data.Defense << std::endl;
		std::cout << "플레이어 체력: " << data.Health << std::endl;
		std::cout << "플레이어 경험치 보유량: " << data.Exp << std::endl;
		std::cout << "플레이어 소지금: " << data.Money << std::endl;
		std::cout << "플레이어 진행중인 스테이지: " << data.CurStage << std::endl;
		std::cout << "플레이어의 타격 숙련도: " << PD_to_SL(data,AttackType::Blunt) << std::endl;
		std::cout << "플레이어의 관통 숙련도: " << PD_to_SL(data, AttackType::Pierce) << std::endl;
		std::cout << "플레이어의 참격 숙련도: " << PD_to_SL(data, AttackType::Slash) << std::endl;
		return data;
	}
	else
	{
		std::cout << "값을 읽어 오는데 실패했습니다." << std::endl;
		return data;
	}
}
string Ccore::PlayInfoToSting() {
	std::ostringstream oss;

	// 1. 첫 번째 줄: 기본 정보
	oss <<  "\t" << PlayerInfo.PlayerName << ", "
		<< PlayerInfo.Level << ", "
		<< PlayerInfo.Power << ", "
		<< PlayerInfo.Defense << ", "
		<< PlayerInfo.Health << ", "
		<< PlayerInfo.Exp << ", "
		<< PlayerInfo.Money << ", "
		<< PlayerInfo.CurStage << "$ "
		<< PlayerInfo.SaveThis << "!\n";

	// 2. 두 번째 줄: 스킬 정보
	oss << "#\t";
	for (auto q : PlayerInfo.skills)
	{
		oss << q.second.S_Level << ", "
			<< q.second.S_Point << ", ";
	}

	return oss.str();
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
	while (getline(inputFile, line)) 
	{
		if (line.empty() || line[0] == '#' || line[0] != check[0]) continue;
		// 주석, 맞지 않는 값 무시

		std::istringstream ss(line);  // 읽어온 줄을 스트림으로 변환
		std::string token;
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());//tap Line 삭제
		getline(ss, token, '%'); getline(ss, Data.PlayerName, ','); // 이름 읽기
		getline(ss, token, ','); Data.Level = stoi(token);  // 레벨 읽기
		getline(ss, token, ','); Data.Power = stoi(token);	// 힘 읽기
		getline(ss, token, ','); Data.Defense = stoi(token); // 방어력 읽기
		getline(ss, token, ','); Data.Health = stoi(token);	// 체력 읽기
		getline(ss, token, ','); Data.Exp = std::stoi(token);  // 경험치 읽기
		getline(ss, token, ','); Data.Money = std::stoi(token);  // 돈 읽기
		getline(ss, token, '$'); Data.CurStage = std::stoi(token);  // 진행도 읽기
		getline(ss, token, '!'); Data.SaveThis = std::stoi(token);  // 오류 검출
		getline(inputFile, line); std::istringstream sss(line);  // 읽어온 줄을 스트림으로 변환
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());//tap Line 삭제
		getline(sss, token, '#');
		for(auto q: Data.skills)
		{
			getline(sss, token, ','); q.second.S_Level = std::stoi(token);
			getline(sss, token, ','); q.second.S_Point = std::stoi(token);
		}
	}

	inputFile.close();
	return Data;
}
bool Ccore::AllFileCheck()
{
	bool test = 0;
	for (DataFile i = DataFile::CurData; i < DataFile::BasicData; ++i)
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
Ccore::Ccore()
	: MaxDataInfo{}
	, PlayerInfo{}
	, ModeCur(GameMode::Normal)
	, lasting{}
	, PlayerAT{}
	//skills{ {AttackType::Blunt,{0,0}},{AttackType::Pierce,{0,0}},{AttackType::Slash,{0,0}}}
{
}
Ccore::~Ccore()
{

}