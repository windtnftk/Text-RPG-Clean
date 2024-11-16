#include "pch.h"
#include "Ccore.h"
#include "Item.h"
#include "Enemy.h"
#include "Equipment.h"
#include "Attribute.h"
#include "Attribute.h"
void Ccore::Progress()
{
	if (!GameOff)// �����߿� gameOff�� �۵��ϸ� �ٷ� �������� ��
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
			std::cout << "������ �����մϴ�." << std::endl;
			P_DataInit();
			End = false;

			break;
		case 2:
			std::cout << "������ �̾��մϴ�." << std::endl;
			End = !SaveDataLoding();
			break;
		case 3:
			std::cout << "������ �����մϴ�." << std::endl;
			// ����â ���� ���� ����
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
	std::cout << "<���� ���� ȭ��>" << std::endl << std::endl;
	std::cout << "1. ���� ����" << std::endl;
	std::cout << "2. ���� �̾��ϱ�" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "4. ����" << std::endl;
}
void Ccore::G_M_Set()
{
	bool End = true;
	while (End)
	{
		std::cout << "1. ���� ���̵� ����" << std::endl;
		std::cout << "2. �÷��̾� �̸� ����" << std::endl;
		switch (CinAuto())
		{
		case 1:
			std::cout << "1. ���� ���̵� �����մϴ�." << std::endl << std::endl;
			G_DifficultySeting();
			End = false;
			break;
		case 2:
			std::cout << "2. �÷��̾� �̸� �����մϴ�." << std::endl << std::endl;
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
		std::wcout << L"\n���̵��� ���Ͻʽÿ�\n" << std::endl;
		std::cout << "1. Easy" << std::endl;
		std::cout << "2. Normal" << std::endl;
		std::cout << "3. Hard" << std::endl;
		switch (CinAuto())
		{
		case 1:
			std::cout << "���� ���̵��� Easy �� �����մϴ�." << std::endl;
			End = false;
			ModeCur = GameMode::Easy;
			break;
		case 2:
			std::cout << "���� ���̵��� Normal �� �����մϴ�." << std::endl;
			End = false;
			ModeCur = GameMode::Normal;
			break;
		case 3:
			std::cout << "���� ���̵��� Hard �� �����մϴ�." << std::endl;
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
	while (YesName) // ĳ���� �̸� ���� �Լ�
	{
		NewName = PlayerInfo.PlayerName;
		std::wcout << L"\n���ο� �̸��� �Է��ϼ���\n";
		std::wcin.ignore(); //�Է� â �ʱ�ȭ(get line �۵��� ���� �ѹ� �����)
		std::getline(std::cin, input);

		if (!input.empty())  // �Է��� ������� ���� ���
		{
			NewName = input; // �Էµ� �̸� ���
		}
		YesName = false;
		// �ٽ�Ȯ�� â, yes �Է� �� �̸� ���� �ݺ��� ����
		// no �Է� �� �̸� �ٽ� ���� �ٽ� Ȯ��â �ݺ�
		// �ٸ��� �۵��� �ٽ� Ȯ��â ����
		std::cout << std::endl << "������ " << NewName << "��(��) �½��ϱ�?" << std::endl;// �ٽ�Ȯ�� â
		if (Yes_No) return; // yes�Է½� �Լ� ����,no �Է½� while�� �ݺ�
	}
	Ccore::GetInst()->PlayerInfo.PlayerName = NewName;
}
void Ccore::BattleAfter(E_Check Info)
{
	if (!Info.Check) {
		std::cout << "�÷��̾ �׾����ϴ�." << std::endl; return;
	} // ��ȯ���� false�� ���� ����� ����
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
	// �ִ� Exp���� ���� Exp�� Ŭ��� �ݺ��ؼ� ������
	while (PlayerInfo.Exp > MaxDataInfo.Exp)
	{
		PlayerInfo.Exp -= MaxDataInfo.Exp;
		++PlayerInfo.Level;
		++MaxDataInfo.Level;
		MaxExpConnect();
		LevelUpView();
	}
	std::cout << "���� ����: " << PlayerInfo.Level << std::endl;
	L_Upstatus();
}
void Ccore::MaxExpConnect()
{
	MaxDataInfo.Exp = PlayerInfo.Level * Multiplier;
}
void Ccore::LevelUpView()
{
	std::cout << "!!!������!!!" << std::endl;
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
	// for�� �־ Attack type��ŭ ��ȸ
	if( 500 > PD_to_SP())
}
E_Check Ccore::BattleStartInit()
{
	E_Info test = EneMy::GetInst()->SetEnemyInfo();
	// �� �Ǵ� �÷��̾ ����ؾ� �ݺ����� ����
	// �÷��̾�, ���� ü���� �� �������� �ڵ����� �ݺ��� off
	while (EneMy::GetInst()->DeadCheck(test) && PlayerLifeCheck())
	{
		EneMy::GetInst()->printCurInfo(test);
		// �÷��̾� ��
		bool End = true;
		while (End)
		{
			std::cout << std::endl << "[1.�Ϲݰ���]" << " [2.�����ۻ��] " << "[3.����â]" << std::endl << std::endl;
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
		}// �÷��̾� �� ����
		if (!EneMy::GetInst()->DeadCheck(test)) //�� �������� üũ
		{//���ϰ��� �� ����, ID�� �ؼ� �� �ο��� ���ϰ����� óġ �������
			return { test.E_BInfo, PlayerLifeCheck() };
			//if (!EnemyTurn(test))
			//{
			//	// ���ϰ��� �������� �����ߴٴ� ��ȯ���� ����,�μ� 2��
			//	GameOver();
			//	return { test.E_BInfo, PlayerLifeCheck() };
			//};
		}
		EnemyTurn(test);// �� �� ����
	}
	return { test.E_BInfo, PlayerLifeCheck() };
}
void Ccore::PlayerInfoView()
{
	std::cout << "�̸�: " << PlayerInfo.PlayerName << std::endl;
	std::cout << "����: " << PlayerInfo.Level << std::endl;
	std::cout << "���ݷ�: " << PlayerInfo.Power << std::endl;
	std::cout << "����: " << PlayerInfo.Defense << std::endl;
	std::cout << "ü��: " << PlayerInfo.Health << std::endl;
	std::cout << "���� ����ġ: " << PlayerInfo.Exp << std::endl;
	std::cout << "�ʿ� ����ġ: " << MaxDataInfo.Exp << std::endl;
}
E_Info Ccore::Hitdamage(E_Info Info)
{
	if (Info.E_BInfo.C_Health > 0) // ���� ��ƾ� ���� ������
	{
		// ��� ������ ���� ���� ���ط��� 1/10�� ����ġ�� ���;�
		// �׷��� applydamage�� ��ȯ������ �޾�, �� �� ���� ���� Ÿ�Ը�ŭ �÷��̾�������
		// ���õ��� �־� �� �Ŀ� ���õ� �� �Լ��� üũ�� ����
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
	std::cout << damage << "�� ���ظ� �������ϴ�." << std::endl;
	Info.E_BInfo.C_Health -= damage;
}
bool Ccore::EnemyTurn(E_Info Info)
{
	EnemyAttack(Info);
	return true;

}
void Ccore::EnemyAttack(E_Info Info)
{
	std::cout << Info.E_BInfo.C_Name << "�� ���� !!!" << std::endl;
	PlayerHit(R_EnemyDamage(Info));
}
int Ccore::R_EnemyDamage(E_Info Info)
{
	return PlayerAT.calculateDamage(Info.E_BInfo.C_Power,Info.attribute.My_AT);
}
void Ccore::PlayerHit(int damage)
{
	std::cout << damage << "�� ���ظ� �Ծ����ϴ�." << std::endl;
	PlayerInfo.Health -= damage;
}
bool Ccore::PlayerLifeCheck()
{
	if (PlayerInfo.Health < 0)
	{
		//std::cout << "�÷��̾ �׾����ϴ�." << std::endl;
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
		std::cout << "����� �÷��̾� �����Ͱ� �����ϴ�." << std::endl;
	}
	std::cout << std::endl << "��� ������ ���� �Ͻðڽ��ϱ�?" << std::endl;
	std::cout << std::endl << "1~8�� ���Ͽ� �����ϼ���" << std::endl;
	std::cout << "0�� ���� = ������������" << std::endl;
	DataFileSave(convert(CinAuto()));
}
void Ccore::DataFileSave(DataFile Data)
{
	if (Data == DataFile::End || Data == DataFile::BasicData)
	{
		std::cout << "�߸��� ������ �����Դϴ�." << std::endl;
	}
	std::fstream file("PlayerData.txt", std::ios::in | std::ios::out);

	if (!file.is_open() || Data == DataFile::BasicData) {
		std::cerr << "������ �� �� �����ϴ�.\n";
		return;
	}
	int lineNumber = convert(Data);  // enum ���� ���� ���� ��ȣ ����
	std::string line;
	// �ӽ� ���Ͽ� ������ ���� �� ����
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "�ӽ� ������ ������ �� �����ϴ�.\n";
		file.close();
		return;
	}
	std::string check = std::to_string(lineNumber);
	while (std::getline(file, line)) {
		if (line.empty() || line[0] == '#' || line[0] != check[0])
		{
			tempFile << line << "\n";  // ������ �ٸ� ������ �״�� ����
			continue;
		}
		tempFile << lineNumber << "%" << PlayInfoToSting() << "\n";// ���� �����͸� �ش� ���ο� ����
	}
	// ���� ����
	file.close();
	tempFile.close();
	// ���� ������ �����
	if (std::remove("PlayerData.txt") != 0) {
		std::cerr << "���� ������ �����ϴ� �� ������ �߻��߽��ϴ�.\n";
		return;
	}
	if (std::rename("temp.txt", "PlayerData.txt") != 0) {
		std::cerr << "�ӽ� ������ ���� ���Ϸ� �̸� �����ϴ� �� ������ �߻��߽��ϴ�.\n";
	}
	std::cout << "�����Ͱ� ����Ǿ����ϴ� (����: " << lineNumber << ").\n";
	
}
bool Ccore::SaveDataLoding()
{
	if (!AllFileCheck())
	{
		std::cout << "����� �÷��̾� �����Ͱ� �����ϴ�." << std::endl;
		return false;
	}
	std::cout << std::endl << "��� ������ �ε��Ͻðڽ��ϱ�?" << std::endl;
	std::cout << std::endl << "1~8�� ������ �����ϼ���" << std::endl;
	//std::cout << "0�� ���� = ������������" << std::endl;
	//SaveDataView(SaveDataView(convert(CinAuto())));
	std::cout << "����� �÷��̾� ���� �Դϴ�." << std::endl;
	PlayerData Test = Selectview();
	if (Test.SaveThis) // �����ϰ� ������ ������ �����ֱ�
	{
		string boolinput;
		while (true)
		{
			std::cout << "�� �ε����Ϸ� �̾��Ͻðڽ��ϱ�?" << std::endl;
			std::cout << "yes �Ǵ� no�� �Է����ֽʽÿ�" << std::endl;
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
		std::cout << "�÷��̾� �̸�: " << data.PlayerName << std::endl;
		std::cout << "�÷��̾� ����: " << data.Level << std::endl;
		std::cout << "�÷��̾� ��: " << data.Power << std::endl;
		std::cout << "�÷��̾� ����: " << data.Defense << std::endl;
		std::cout << "�÷��̾� ü��: " << data.Health << std::endl;
		std::cout << "�÷��̾� ����ġ ������: " << data.Exp << std::endl;
		std::cout << "�÷��̾� ������: " << data.Money << std::endl;
		std::cout << "�÷��̾� �������� ��������: " << data.CurStage << std::endl;
		std::cout << "�÷��̾��� Ÿ�� ���õ�: " << PD_to_SL(data,AttackType::Blunt) << std::endl;
		std::cout << "�÷��̾��� ���� ���õ�: " << PD_to_SL(data, AttackType::Pierce) << std::endl;
		std::cout << "�÷��̾��� ���� ���õ�: " << PD_to_SL(data, AttackType::Slash) << std::endl;
		return data;
	}
	else
	{
		std::cout << "���� �о� ���µ� �����߽��ϴ�." << std::endl;
		return data;
	}
}
string Ccore::PlayInfoToSting() {
	std::ostringstream oss;

	// 1. ù ��° ��: �⺻ ����
	oss <<  "\t" << PlayerInfo.PlayerName << ", "
		<< PlayerInfo.Level << ", "
		<< PlayerInfo.Power << ", "
		<< PlayerInfo.Defense << ", "
		<< PlayerInfo.Health << ", "
		<< PlayerInfo.Exp << ", "
		<< PlayerInfo.Money << ", "
		<< PlayerInfo.CurStage << "$ "
		<< PlayerInfo.SaveThis << "!\n";

	// 2. �� ��° ��: ��ų ����
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
		std::cerr << "������ �� �� �����ϴ�." << std::endl;
		Data.SaveThis = false;
		return Data;
	}
	while (getline(inputFile, line)) 
	{
		if (line.empty() || line[0] == '#' || line[0] != check[0]) continue;
		// �ּ�, ���� �ʴ� �� ����

		std::istringstream ss(line);  // �о�� ���� ��Ʈ������ ��ȯ
		std::string token;
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());//tap Line ����
		getline(ss, token, '%'); getline(ss, Data.PlayerName, ','); // �̸� �б�
		getline(ss, token, ','); Data.Level = stoi(token);  // ���� �б�
		getline(ss, token, ','); Data.Power = stoi(token);	// �� �б�
		getline(ss, token, ','); Data.Defense = stoi(token); // ���� �б�
		getline(ss, token, ','); Data.Health = stoi(token);	// ü�� �б�
		getline(ss, token, ','); Data.Exp = std::stoi(token);  // ����ġ �б�
		getline(ss, token, ','); Data.Money = std::stoi(token);  // �� �б�
		getline(ss, token, '$'); Data.CurStage = std::stoi(token);  // ���൵ �б�
		getline(ss, token, '!'); Data.SaveThis = std::stoi(token);  // ���� ����
		getline(inputFile, line); std::istringstream sss(line);  // �о�� ���� ��Ʈ������ ��ȯ
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());//tap Line ����
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
				std::cout << "����Ǿ� �ִ� File" << std::endl;
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
		std::cerr << "������ �� �� �����ϴ�." << std::endl;
		return false;
	}
	while (std::getline(inputFile, line)) {
		if (line.empty() || line[0] == '#' || line[0] != check[0]) continue;
		// �ּ�, ���� �ʴ� �� ����

		std::istringstream ss(line);  // �о�� ���� ��Ʈ������ ��ȯ
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