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
// ++������ �����ε�, DataFile�� �ԷµǸ� ���� File�� �̵��ϴ� �Լ�
// DataFile8�� ������ �������� ����� �״�� ��ȯ��
inline DataFile& operator++(DataFile& File) {
	if (File == DataFile::BasicData) {
		std::cout << "DataFile�� �Ѱ迡 �����߽��ϴ�." << std::endl;
		return File;
	}
	else {
		File = static_cast<DataFile>(static_cast<int>(File) + 1);
	}
	return File;
}
// ��� ���� ����ȿ�� ���� �ٸ� ����ҋ� �׻� ����
// but ����������ÿ��� �� ����, �Ŀ� ������ �߰� ȿ�� ���� ����
struct LastingEffect
{
	int		Power;		//���� ���ݷ� ������
	int		Defense;	//���� ���� ������
	int		Barrier;	//�����Լ� �� ���� ��ȣ�� ȿ�� ����
};
struct Attribute {
	enum class AttackType {
		Blunt,  // Ÿ��
		Pierce,  // ����
		Slash    // ����
	};

	AttackType attackType;
	// �ٸ� �Ӽ��̳� ���� �߰� ����
};

struct PlayerData
{
	string	PlayerName;	//�÷��̾� �̸�
	int		Level;		//�÷��̾� ����, ������ ���� ����ġ ŉ��� ������
	int		Power;		//�÷��̾� ���ݷ�
	int		Defense;	//�÷��̾� ����
	int		Health;		//�÷��� ü��
	int		Exp;		//�÷��̾� ����ġ
	int		Money;		//�÷��̾� ��
	int		CurStage;	//�÷��̾ ������ �������� ��ġ
	//Data File�� ������ �����ߴ��� Ȯ���ϴ� ���� 
	//�⺻���� false, ����� true�� ��ȯ, DataFileSave�Լ��� ���� true��ȯ�ؾߵ�
	//���� �߻��ÿ� false������ ��ȯ��
	bool	SaveThis;
};
// ������ Ÿ�� ���, �������� ���緹�� �� ���ؼ� �ִ� Exp�� ����� �����
constexpr int Multiplier = 20;  
// Main ���� ���� ��� 
class Ccore
{
	friend class EneMy;
	friend class MainItem;
	SINGLE(Ccore);
	PlayerData	MaxDataInfo; //�÷��̾� �ִ� ��
	// ��) PlayerInfo�� ����ġ�� MaxDataInfo�� �ִ� ����ġ���� �������� ������
	PlayerData	PlayerInfo; // �÷��̾� ����
	GameMode	ModeCur; // ���� ������ ���� ����
	LastingEffect lasting;// �������� ȿ���� ���


public:		// �⺻ Init���� �Լ�

	// Main ���α׷��� ���ư��� �Լ�, �ϴ� ���⼭ ��� ���� �����ϵ��� ����
	void	Progress();
	// Main ���α׷��� �����ϱ��� �ʱⰪ ����
	void	Init();
	// Main Init �� �ҷ��� ���� ���� MaxDataInfo �ʱ�ȭ �ϴ� �Լ�
	// LevelUp�� MaxDataInfo �ʱ�ȭ
	void	MaxDataInit();
	// Player �⺻���� Initial ���� 
	void	P_DataInit() { PlayerInfoLoding(LodingData(DataFile::BasicData)); }


public:		//���� ���ۺΰ����Լ�

	// main ���ۺ� -> �÷��̾� �̸� ���ϱ� �� �⺻ ����â ����
	void	GameStartSet();
	// Game StartSet �� �޴� ���
	void	GameStartSetOutPut();
	// Game Over �Ǵ� �Լ�
	void	GameOver() { GameOff = false; }


public:		// �������� �Լ�

	// GameMode ����
	void	G_M_Set();
	// Game ���̵� �����ϴ� �Լ�
	void	G_DifficultySeting();
	// Player Name �����Լ�
	void	PlayerNameSeting();


public:		//	������ ó�� �Լ�
	//	���� ŉ��, ���������� Ȯ�� �� ����
	void	BattleAfter(E_Check Info);
	// ���� ������ �������������� �̵�
	void	NextStage();

public:		// ������ ���� �Լ�

	// ������ �Լ�, ���� ������ �޾Ƽ� ����ġ�� ��� �Լ�
	// �Ŀ� �������̳� �߰�ȿ�� ��� �ٲܿ���(24.11.08 ������)
	void	RewardCheck(B_Status Reward);
	// ����ġ ���� �� Exp �Ѿ����� �Ѱ� �Լ�
	void	RewardExp(B_Status Reward);
	// ����ġ ������ ������ Check �� �󸶳� ���Ҵ��� Check
	void	LevelUpCheck();
	// �ִ� Exp�� �����۾�
	void	MaxExpConnect();
	// ������ �� �˸�, Init�ÿ��� ����
	void	LevelUpView();
	// ������ �� �����۾�
	// �̰ɷ� ��� ������
	void	L_Upstatus();

	// ����ó�� �Լ�
public:		
	// ����ȭ������ �����ϴ� �Լ�
	// ��ȯ���� bool������ �ټ� �����ϱ�
	// �÷��̾� ���, ���� ������ ������ false(������ PlayerLifeCheck�� Ȯ��)
	// �⺻���δ� true�� ��ȯ�ϵ��� �ؼ� �ϰ����� ����(24.11.08 ������)
	E_Check	BattleStartInit();
	// �÷��̾� ���°� ���, ������
	// �̸�, ����, ���ݷ�, ����, ü��, ���� ����ġ, �ʿ� ����ġ
	void	PlayerInfoView();
	// ���� ���ع޴� �Լ�, �÷��̾� ���ݷ� ��ŭ�� ������ ����
	// ���Ŀ� �ٸ� ��� �ʿ�
	E_Info Hitdamage(E_Info Info);
	// ���� ������ �Ѱ��ϴ� �Լ�
	// �� �������� �÷��̾� ����� false ��ȯ
	// �� �� ��� ����
	bool	EnemyTurn(E_Info Info);
	// �� �Է½� ���� ���ݷ� �����Ͽ� �÷��̾�� ����������
	// ���� ��� X
	void EnemyAttack(E_Info Info);
	// ���� �׾����� Ȯ���ϴ� �Լ�
	bool PlayerLifeCheck();
public:
	// ���������� ��뿡�� �߰���(����)
	
	// ���� �� ��ȭ���� Ǯ�� �����ؾߵ�
	void PowerUp(int test) { PlayerInfo.Power += test; } //PowerUp
	void DefenseUp(int test) { PlayerInfo.Defense += test; } //DefenseUp
	void LimitHealthUp(int test); //�ִ� ü�� Ȯ���ؼ� �Ѱ�ġ ������ ȸ��

	// ���⼭ ���ʹ� ����ȿ�� ����, ��� �����Լ����� ���⸦ ȣ���� ����
	// ���⼭ int�� ��� enum class ���� ��͵��� ���� ȿ�� ����Ǵ� ����
	// �ٸ��� ����� �ϸ� ������ ���� ����
	// ��))1�� ����� �븻 ����, 10�� ����� ������� ���� + �߰�ȿ�� �̷�������

	void Newbarrier(int test);//�� ����
	void AddPowerUp(int test);//���� ���ݷ� ����
	void AddDefenseUp(int test);//���� ���� ����
	// ���� ȿ�� ���� (���߿� int��� enum ����), ���� ���� ������� ����
	void Removebarrier(int test);//�� ����
	void RemovePowerUp(int test);//���� ���ݷ� ����
	void RemoveDefenseUp(int test);//���� ���� ����
	
public:		// ������ ����

	// ������ ������ �������̽� ���
	void	SelectSavePoint();
	// PlayerInfo �� DataFile�� �����ϴ� �Լ�
	void	DataFileSave(DataFile Data);
	// PlayerInfo�� CruData �� �����ϴ� �Լ�, ��������
	void	CurDataSave() { DataFileSave(DataFile::CurData); }

public:		// ������ �ҷ�����

	// �÷��̾� �̾��ϱ� ���ý� ������ ��� �������� ����� �Լ�
	// Save�� �����Ͱ� ������, ������ �����ͷ� ���Ѵٰ� �Ҷ� false ��ȯ
	bool	SaveDataLoding();
	// Player Data�� �����ִ� �Լ�
	PlayerData	DataFileView(PlayerData data);
	// ������ �Է��� ������ �����ִ� �Լ�(�Լ����ռ�Ʈ)
	PlayerData	Selectview() { return DataFileView(LodingData(convert(CinAuto()))); }
	// PlayerData�� PlayerInfo�� �ִ� �Լ�
	void	PlayerInfoLoding(PlayerData data) { PlayerInfo = data; }

public:		// Auto ��

	// PlayerInfo�� string���� ��ȯ�ؼ� ��ȯ�ϴ� �Լ�
	string  PlayInfoToSting();
	// DataFile�� PlayerData�� ��ȯ�ϴ� �Լ�
	PlayerData	LodingData(DataFile dataFile);

public:		//����üũ��

	// ���� �� ������������ ������ Ȯ�� �Լ�, ������ �ִٰ� �˷���
	// CheckSavefile �� �ݺ��� ����, 0�� ����(curData���� ��ȸ)
	bool	AllFileCheck();
	// DataFile Ȯ���ؼ� �ش� File�� ������ �ִ��� Ȯ���ϴ� �Լ�
	bool	CheckSavefile(DataFile dataFile);

public:		// ��ȯ�Լ�
	// int�� Static_cast�� DataFile�� ��ȯ�ϴ� �Լ�
	DataFile convert(int value) {
		return static_cast<DataFile>(value);
	}
	// DataFile�� Static_cast�� int�� ��ȯ�ϴ� �Լ�
	int convert(DataFile dataFile) {
		return static_cast<int>(dataFile);
	}

};

