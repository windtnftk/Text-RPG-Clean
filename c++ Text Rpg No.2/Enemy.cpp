
#include "pch.h"
#include "Enemy.h"
#include "Ccore.h"
#include <random>

void EneMy::EnemyInit()
{
	/*
	std::random_device rd;
	std::mt19937 gen(rd()); // Mersenne Twister 알고리즘을 사용하는 엔진 생성

	// 균일 분포에서 랜덤한 정수 생성 (0 이상 99 이하)
	std::uniform_int_distribution<int> distribution(0, 99);
	int rendom = distribution(gen) % 10;
	*/

	EneMy::GetInst()->CreateEnemy(Ccore::GetInst()->ModeCur);

	EneMy::GetInst()->E_Point = EneMy::GetInst()->E_BasicInfo.begin();
}
void EneMy::CreateEnemy(GameMode CurMode)
{
	if (GameMode::GameEnd == CurMode)
	{
		std::wcout << L"게임 종료중에는 적을 소환 할 수 없습니다. " << std::endl;
	}
	std::ifstream inputFile("EnemyInit.txt");
	std::string line;

	if (!inputFile.is_open()) {
		std::cerr << "파일을 열 수 없습니다." << std::endl;
		return;
	}
	int ID = 0;
	while (std::getline(inputFile, line)) {
		if (line.empty() || line[0] == '#') continue;  // 주석 무시

		std::istringstream ss(line);  // 읽어온 줄을 스트림으로 변환
		std::string token; E_Info monster;
		getline(ss, monster.E_BInfo.C_Name, ',');
		getline(ss, token, ','); monster.E_BInfo.C_Level = stoi(token) * (int)CurMode;  // 레벨 읽기
		getline(ss, token, ','); monster.E_BInfo.C_Power = stoi(token) * (int)CurMode;	// 힘 읽기
		getline(ss, token, ','); monster.E_BInfo.C_Health = stoi(token) * (int)CurMode; // 기본 생명력 읽기
		getline(ss, token, ','); monster.E_BInfo.C_Exp = stoi(token) * (int)CurMode;	// 경험치 읽기
		getline(ss, token, ','); monster.E_Plase = std::stoi(token);  // 생존 위치 읽기
		getline(ss, token, ','); monster.E_Life = std::stoi(token);  // 생존 여부 읽기
		//monster.E_CurInfo = monster.E_BInfo; // 기본 세팅 값 현재값으로 복사
		EneMy::GetInst()->E_BasicInfo.emplace(EidReturn(ID), monster);// 몬스터 정보 저장
		++ID;
	}

	inputFile.close();
}
E_Info EneMy::SetEnemyInfo()
{
	/*std::cout << "Name: " << E_Point->second.E_BInfo.C_Name << std::endl;
	std::cout << "Level: " << E_Point->second.E_BInfo.C_Level << std::endl;
	std::cout << "Power: " << E_Point->second.E_BInfo.C_Power << std::endl;
	std::cout << "Health: " << E_Point->second.E_BInfo.C_Health << std::endl;
	std::cout << "Exp: " << E_Point->second.E_BInfo.C_Exp << std::endl;
	std::cout << "Place: " << E_Point->second.E_Plase << std::endl;
	std::cout << "Life: " << (E_Point->second.E_Life ? "Alive" : "Dead") << std::endl;*/
	return E_Point->second;
}
void EneMy::ViewEnemy()
{
	for (int i = 0; i < (int)EnemyId::God; ++i)
	{
		printEnemyBaseInfo(EidReturn(i));

	}
}
void EneMy::printEnemyBaseInfo(EnemyId data)
{
	auto it = EneMy::GetInst()->E_BasicInfo.find(data);
	std::cout << "Name: " << it->second.E_BInfo.C_Name << std::endl;
	std::cout << "Level: " << it->second.E_BInfo.C_Level << std::endl;
	std::cout << "Power: " << it->second.E_BInfo.C_Power << std::endl;
	std::cout << "Health: " << it->second.E_BInfo.C_Health << std::endl;
	std::cout << "Exp: " << it->second.E_BInfo.C_Exp << std::endl;
	std::cout << "Place: " << it->second.E_Plase << std::endl;
	std::cout << "Life: " << (it->second.E_Life ? "Alive" : "Dead") << std::endl;
}
bool EneMy::printCurInfo(E_Info data)
{
	std::cout << "Name: " << data.E_BInfo.C_Name << std::endl;
	std::cout << "Level: " << data.E_BInfo.C_Level << std::endl;
	std::cout << "Power: " << data.E_BInfo.C_Power << std::endl;
	std::cout << "Health: " << data.E_BInfo.C_Health << std::endl;
	std::cout << "Exp: " << data.E_BInfo.C_Exp << std::endl;
	std::cout << "Place: " << data.E_Plase << std::endl;
	std::cout << "Life: " << (data.E_Life ? "Alive" : "Dead") << std::endl;
	if (data.E_BInfo.C_Health > 0)
	{
		return true;
	}
	return false;
}
void EneMy::printEnemyCurInfo(EnemyId data)
{
	/*auto it = EneMy::GetInst()->E_BasicInfo.find(data);
	std::cout << "Name: " << it->second.E_CurInfo.C_Name << std::endl;
	std::cout << "Level: " << it->second.E_CurInfo.C_Level << std::endl;
	std::cout << "Power: " << it->second.E_CurInfo.C_Power << std::endl;
	std::cout << "Health: " << it->second.E_CurInfo.C_Health << std::endl;
	std::cout << "Exp: " << it->second.E_CurInfo.C_Exp << std::endl;
	std::cout << "Place: " << it->second.E_Plase << std::endl;
	std::cout << "Life: " << (it->second.E_Life ? "Alive" : "Dead") << std::endl;*/
}
EnemyId EneMy::EidReturn(int id)
{
	if (id < 0 || id > static_cast<int>(EnemyId::God)) {
		throw std::out_of_range("Invalid EnemyId");
	}
	return static_cast<EnemyId>(id);
}

E_Info* EneMy::IdReturn(EnemyId Id)
{
	map<EnemyId, E_Info>::iterator It = E_BasicInfo.find(Id);
	if (It != E_BasicInfo.end())
	{
		return &It->second;
	}
	else
	{
		return nullptr;
	}

}
//void EneMy::CreateEnemy(int	id)
//{
//	EneMy::GetInst()->CreateEnemy(static_cast<EnemyId>(id));
//}
//B_Status EneMy::StatChange(GameMode CurMode, EnemyId id)
//{
//	string IdName;
//	int	IdLevel =0;
//	int	IdPower = 0;
//	int	IdHealth = 0;
//	int	IdExp = 0;
//	if ((int)id == 0)
//	{
//		IdLevel =   (int)CurMode ;
//		IdPower =   (int)CurMode ;
//		IdHealth =  (int)CurMode ;
//		IdExp =		(int)CurMode ;
//	}
//	else
//	{		
//		IdLevel = (int)CurMode * (int)id * 1;
//		IdPower = (int)CurMode * (int)id * 5;
//		IdHealth = (int)CurMode * (int)id * 10;
//		IdExp = (int)CurMode * (int)id * 10;
//	}
//
//	switch (id)
//	{
//	case EnemyId::Enemy1:
//		IdName = "Enemy1";
//		break;
//	case EnemyId::Enemy2:
//		IdName = "Enemy2";
//		break;
//	case EnemyId::Enemy3:
//		IdName = "Enemy3";
//		break;
//	case EnemyId::Enemy4:
//		IdName = "Enemy4";
//		break;
//	case EnemyId::Enemy5:
//		IdName = "Enemy5";
//		break;
//	case EnemyId::Enemy6:
//		IdName = "Enemy6";
//		break;
//	case EnemyId::Enemy7:
//		IdName = "Enemy7";
//		break;
//	case EnemyId::Enemy8:
//		IdName = "Enemy8";
//		break;
//	case EnemyId::Enemy9:
//		IdName = "Enemy9";
//		break;
//	case EnemyId::God:
//		IdName = "God";
//		IdLevel = 15 * (int)CurMode;
//		IdPower = 60 * (int)CurMode;
//		IdHealth = 100 * (int)CurMode;
//		IdExp = 500 * (int)CurMode;
//		break;
//	default:
//		break;
//	}
//	
//	
//	return B_Status{ IdName, IdLevel, IdPower, IdHealth,IdExp };
//	
//}
EneMy::EneMy()
	:E_BasicInfo{}
	, E_Point{}
{

}
EneMy::~EneMy()
{

}