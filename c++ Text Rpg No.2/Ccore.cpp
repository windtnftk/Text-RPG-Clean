#include "pch.h"
#include "Ccore.h"
#include "Item.h"
#include "Enemy.h"
#include "Equipment.h"

void Ccore::Init()
{
	if (Ccore::GetInst()->ModeCur != GameMode::GameEnd)
	{
		
		MainItem::GetInst()->ItemInit();
		EneMy::GetInst()->EnemyInit();
		EneMy::GetInst()->ViewEnemy();
	}
	
}

void Ccore::P_DataInit()
{
	LodingData(DataFile::BasicData);
}
void Ccore::BattleStartInit()
{
	while (true)
	{
		bool End = true;
		while (End)
		{
			EneMy::GetInst()->SetEnemyInfo();
			std::cout << "[1.�Ϲݰ���]" << " [2.�����ۻ��] " << "[3.����â]" << std::endl << std::endl;
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

		// �ٽ�Ȯ�� â, yes �Է� �� �̸� ���� �ݺ��� ����
		// no �Է� �� �̸� �ٽ� ���� �ٽ� Ȯ��â �ݺ�
		// �ٸ��� �۵��� �ٽ� Ȯ��â ����
		while (true)
		{
			std::cout << std::endl << "������ " << NewName << "��(��) �½��ϱ�?" << std::endl;// �ٽ�Ȯ�� â
			std::cout << "yes �Ǵ� no�� �Է����ֽʽÿ�" << std::endl;
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
		std::cout << "�߸��� ������ �����Դϴ�." << std::endl;
	}
	std::fstream file("PlayerData.txt", std::ios::in | std::ios::out);
	
	if (!file.is_open() || Data == DataFile::BasicData) {
		std::cerr << "������ �� �� �����ϴ�.\n";
		return;
	}
	string CurData = PlayInfoToSting();
	// ���Ͽ��� �����͸� ������ ��ġ ���
	int lineNumber = static_cast<int>(Data);  // enum ���� ���� ���� ��ȣ ����
	std::string line;
	int currentLine = 0;

	// �ӽ� ���Ͽ� ������ ���� �� ����
	std::ofstream tempFile("temp.txt");
	if (!tempFile.is_open()) {
		std::cerr << "�ӽ� ������ ������ �� �����ϴ�.\n";
		file.close();
		return;
	}

	while (std::getline(file, line)) {
		if (currentLine == lineNumber + 4) {
			tempFile << lineNumber << "% " << CurData << "\n";  
			// ���� �����͸� �ش� ���ο� ����
		}
		else {
			tempFile << line << "\n";  // ������ �ٸ� ������ �״�� ����
		}
		currentLine++;
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
void Ccore::SelectSavePoint()
{
	std::cout << std::endl << "��� ������ ���� �Ͻðڽ��ϱ�?" << std::endl;
	std::cout << std::endl << "1~8�� ���Ͽ� �����ϼ���" << std::endl;
	std::cout << "0�� ���� = ������������" << std::endl;
	DataFileSave(intToDfile(CinAuto()+1));
}
DataFile Ccore::intToDfile(int data)
{
		if (data < 1 || data > static_cast<int>(DataFile::End)) {
			throw std::out_of_range("Invalid");
			return DataFile::End;
		}
		return static_cast<DataFile>(data);
}
int Ccore::CinAuto() {
	int choice;
	while (true) {
		std::cout << "���ڸ� �Է��ϼ���: ";
		std::cin >> choice;
		if (std::cin.fail()) {
			// �߸��� �Է��� �߻����� ���
			std::cin.clear(); // cin�� ���� ���� �÷��׸� �ʱ�ȭ
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �Է� ���۸� ���ϴ�.
			std::cout << "�߸��� �Է��Դϴ�.\n";
		}
		else 
		{
			// ��ȿ�� �Է��� ������ ���
			return choice; // �������� ��� �ݺ� ���� �� �� ��ȯ
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
	+ ", " + std::to_string(PlayerInfo.CurStage);
}
void Ccore::GameStartSet()
{
	bool End = true;
	while (End)
	{
		std::cout << "1. ���� ����" << std::endl;
		std::cout << "2. ���� �̾��ϱ�" << std::endl;
		std::cout << "3. ���� �����ϱ�" << std::endl;
		std::cout << "4. ���� �����ϱ�" << std::endl;
		int input = 0;
		std::cin >> input;
		// �̸� �������°� ���� ��~~~
		switch (input)
		{
		case 1:
			std::cout << "������ �����մϴ�." << std::endl;
			P_DataInit();
			End = false;
			
			break;
		case 2:
			std::cout << "������ �̾��մϴ�." << std::endl;
			End = false;
			// ���� ���� X
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
PlayerData Ccore::LodingData(DataFile dataFile)
{
	std::ifstream inputFile("PlayerData.txt");
	std::string line;
	std::string check = std::to_string(static_cast<int>(dataFile));
	PlayerData Data;
	if (!inputFile.is_open()) {
		std::cerr << "������ �� �� �����ϴ�." << std::endl;
		return;
	}
	while (std::getline(inputFile, line)) {
		if (line.empty() || line[0] == '#'|| line[0] != check[0]) continue;
		// �ּ�, ���� �ʴ� �� ����

		std::istringstream ss(line);  // �о�� ���� ��Ʈ������ ��ȯ
		std::string token; 
		getline(ss, token, '%'); getline(ss, Data.PlayerName, ','); // �̸� �б�
		getline(ss, token, ','); Data.Level = stoi(token)  ;  // ���� �б�
		getline(ss, token, ','); Data.Power = stoi(token)  ;	// �� �б�
		getline(ss, token, ','); Data.Defense = stoi(token); // ���� �б�
		getline(ss, token, ','); Data.Health = stoi(token) ;	// ü�� �б�
		getline(ss, token, ','); Data.Exp = std::stoi(token);  // ����ġ �б�
		getline(ss, token, ','); Data.Money = std::stoi(token);  // �� �б�
		getline(ss, token, ','); Data.CurStage = std::stoi(token);  // ���൵ �б�
	}
	inputFile.close();
	return Data;
}
// �а� �׿� ���� �����͸� PlayerInfo�� ������ �Լ�
// �а� �׿� ���� �����͸� 
// �а� �׿� ���� �����͸� view�� �� �Լ�
void Ccore::SaveDataLoding()
{
	if (false/*����� �����Ͱ� �������*/)
	{
		std::cout << "����� �÷��̾� �����Ͱ� �����ϴ�." << std::endl;
	}
	std::cout << "� �����͸� �����ñ��?" << std::endl;
	std::cout << std::endl << "��� ������ �ε��Ͻðڽ��ϱ�?" << std::endl;
	std::cout << std::endl << "1~8�� ������ �����ϼ���" << std::endl;
	//std::cout << "0�� ���� = ������������" << std::endl;
	//SaveDataView(SaveDataView(intToDfile(CinAuto())));
	Selectview();// ������ ������ �����ֱ�
	std::cout << "����� �÷��̾� ���� �Դϴ�." << std::endl;
}
void Ccore::DataFileView(PlayerData data)
{
	std::cout << "�÷��̾� �̸�: " << data.PlayerName << std::endl;
	std::cout << "�÷��̾� ����: " << data.Level	  << std::endl;  
	std::cout << "�÷��̾� ��: " << data.Power	  << std::endl;  
	std::cout << "�÷��̾� ����: " << data.Defense    << std::endl;
	std::cout << "�÷��̾� ü��: " << data.Health	  << std::endl;  
	std::cout << "�÷��̾� ����ġ ������: " << data.Exp	      << std::endl;
	std::cout << "�÷��̾� ������: " << data.Money	  << std::endl;  
	std::cout << "�÷��̾� �������� ��������: " << data.CurStage   << std::endl;
}
Ccore::Ccore()
	:PlayerInfo{}
	, ModeCur(GameMode::Normal)
{
}
Ccore::~Ccore()
{

}