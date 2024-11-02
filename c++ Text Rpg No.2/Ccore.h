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
	End =10
};
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
	// Player �⺻���� Initial ���� 
	void	P_DataInit();
	// Main ���α׷��� ���ư��� �Լ�, �ϴ� ���⼭ ��� ���� �����ϵ��� ����
	void	Progress();
	// main ���ۺ� -> �÷��̾� �̸� ���ϱ� �� �⺻ ����â ����
	void	GameStartSet();
	// DataFile�� PlayerData�� ��ȯ�ϴ� �Լ�
	PlayerData	LodingData(DataFile dataFile);
	// DataFile�� PlayerInfo�� �ִ� �Լ�
	void	PlayerInfoLoding(PlayerData data) { PlayerInfo = data; }
	// �÷��̾� �̾��ϱ� ���ý� ������ ��� �������� ����� �Լ�
	void	SaveDataLoding();
	// Player Data�� �����ִ� �Լ� <== ���࿹�� (24.10.27)
	void	DataFileView(PlayerData data);
	// ���ϴ� ������ �Է°��� �����ִ� �Լ�(�Լ����ռ�Ʈ)
	void	Selectview(){ DataFileView(LodingData(intToDfile(CinAuto()))); }
	// Game Over �Ǵ� �Լ�
	void	GameOver() { GameOff = false; };
	// Game StartSet �� �޴� ���
	void	GameStartSetOutPut();
	// GameMode ����
	void	G_M_Set();
	// Game ���̵� �����ϴ� �Լ�
	void	G_DifficultySeting();
	// Player Name �����Լ�
	void	PlayerNameSeting();
	// ������ ������ �������̽� ���
	void	SelectSavePoint();
	// int ���ڸ� DataFile�� �����Լ�
	DataFile intToDfile(int data);
	// int ���ڸ� PlayerData���� �����Լ�
	//PlayerData intToPd(int data);
	// PlayerInfo �� DataFile�� �����ϴ� �Լ�
	void	DataFileSave(DataFile Data);
	// PlayerInfo�� CruData �� �����ϴ� �Լ�, ��������
	void	CurDataSave() { DataFileSave(DataFile::CurData); }
	// PlayerInfo�� string���� ��ȯ�ؼ� ��ȯ�ϴ� �Լ�
	string  PlayInfoToSting();
	// ��ȯ������ �Է��� int�� �޴� �Լ�
	int		CinAuto();
	// ����ȭ������ �����ϴ� �Լ�
	void	BattleStartInit();
	
	friend class EneMy;
};

