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
// ++������ �����ε�, DataFile�� �ԷµǸ� ���� File�� �̵��ϴ� �Լ�
// DataFile8�� ������ �������� ����� �״�� ��ȯ��
inline DataFile& operator++(DataFile& File) {
	if (File == DataFile::NoDataFile) {
		std::cout << "DataFile8�� �Ѱ迡 �����߽��ϴ�." << std::endl;
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


public:
	// Main ���α׷��� �����ϱ��� �ʱⰪ ����
	void	Init();
	// Main Init �� �ҷ��� ���� ���� MaxDataInfo �ʱ�ȭ �ϴ� �Լ�
	void	MaxDataInit();
	// Player �⺻���� Initial ���� 
	void	P_DataInit() { PlayerInfoLoding(LodingData(DataFile::BasicData)); };
	// Main ���α׷��� ���ư��� �Լ�, �ϴ� ���⼭ ��� ���� �����ϵ��� ����
	void	Progress();
	// main ���ۺ� -> �÷��̾� �̸� ���ϱ� �� �⺻ ����â ����
	void	GameStartSet();
	// GameMode ����
	void	G_M_Set();
	// Game StartSet �� �޴� ���
	void	GameStartSetOutPut();
	// Game Over �Ǵ� �Լ�
	void	GameOver() { GameOff = false; };
	// ����ȭ������ �����ϴ� �Լ�
	void	BattleStartInit();
	// Game ���̵� �����ϴ� �Լ�
	void	G_DifficultySeting();
	// Player Name �����Լ�
	void	PlayerNameSeting();
public:		// ������ �����Լ�

	// ������ ������ �������̽� ���
	void	SelectSavePoint();
	// ���ϴ� ������ �Է°��� �����ִ� �Լ�(�Լ����ռ�Ʈ)
	void	Selectview() { DataFileView(LodingData(convert(CinAuto()))); }
	// Player Data�� �����ִ� �Լ�
	void	DataFileView(PlayerData data);

public:		// ������ �����Լ�
	// PlayerInfo �� DataFile�� �����ϴ� �Լ�
	void	DataFileSave(DataFile Data);
	// PlayerInfo�� CruData �� �����ϴ� �Լ�, ��������
	void	CurDataSave() { DataFileSave(DataFile::CurData); }
	// DataFile�� PlayerInfo�� �ִ� �Լ�
	void	PlayerInfoLoding(PlayerData data) { PlayerInfo = data; }

public:
	// �÷��̾� �̾��ϱ� ���ý� ������ ��� �������� ����� �Լ�
	bool	SaveDataLoding();
	// PlayerInfo�� string���� ��ȯ�ؼ� ��ȯ�ϴ� �Լ�
	string  PlayInfoToSting();
	// ��ȯ������ �Է��� int�� �޴� �Լ�
	int		CinAuto();
	// DataFile�� PlayerData�� ��ȯ�ϴ� �Լ�
	PlayerData	LodingData(DataFile dataFile);

public:

	// DataFile Ȯ���ؼ� �ش� File�� ������ �ִ��� Ȯ���ϴ� �Լ�
	bool	CheckSavefile(DataFile dataFile);
	// ����Ǿ��ִ� �����Ͱ� �ִ��� Ȯ���ϴ� �Լ�, ������ �ִٰ� �˷���
	bool	AllFileCheck();

public:
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

