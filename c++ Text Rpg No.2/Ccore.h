#pragma once
#include "Enemy.h"

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

struct PlayerData
{
	string	PlayerName;	//�÷��̾� �̸�
	int		Level;		//�÷��̾� ����, ������ ���� ����ġ ŉ��� ������
	int		Power;		//�÷��̾� ��
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
// Main ���� ���� ��� 
class Ccore
{
	
	SINGLE(Ccore);
	PlayerData	MaxDataInfo; //�÷��̾� �ִ� ��
	// ��) PlayerInfo�� ����ġ�� MaxDataInfo�� �ִ� ����ġ���� �������� ������
	PlayerData	PlayerInfo; // �÷��̾� ����
	GameMode	ModeCur; // ���� ������ ���� ����


public:		// �⺻ Init���� �Լ�

	// Main ���α׷��� ���ư��� �Լ�, �ϴ� ���⼭ ��� ���� �����ϵ��� ����
	void	Progress();
	// Main ���α׷��� �����ϱ��� �ʱⰪ ����
	void	Init();
	// Main Init �� �ҷ��� ���� ���� MaxDataInfo �ʱ�ȭ �ϴ� �Լ�
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

public:		// �������� �Լ�

	// ����ȭ������ �����ϴ� �Լ�
	void	BattleStartInit();
	// �÷��̾� ���°� ���, ������
	// �̸�, ����, ���ݷ�, ����, ü��, ���� ����ġ, �ʿ� ����ġ
	void	PlayerInfoView();
	// ���� ���ع޴� �Լ�, �÷��̾� ���ݷ� ��ŭ�� ������ ����
	// ���Ŀ� �ٸ� ��� �ʿ�
	E_Info Hitdamage(E_Info Enemy);
	// ���� ������ �Ѱ��ϴ� �Լ�
	// �� �������� �÷��̾� ����� false ��ȯ
	// �����ؼ� �ٷ� �ݺ��� ����� �Ѿ�� ������
	bool	EnemyTurn(E_Info Enemy);
	// �� �Է½� ���� ���ݷ� �����Ͽ� �÷��̾�� ����������
	// ���� ��� X
	void EnemyAttack(E_Info Enemy);
	// ���� �׾����� Ȯ���ϴ� �Լ�
	bool PlayerLifeCheck();
	
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

	// ��ȯ������ �Է��� int�� �޴� �Լ�
	int		CinAuto();
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
	friend class EneMy;
};

