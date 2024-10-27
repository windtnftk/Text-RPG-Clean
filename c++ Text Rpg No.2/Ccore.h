#pragma once

enum class GameMode
{
	GameEnd,
	Easy,
	Normal,
	Hard,



	End = 10
};
enum class PlayerDataSet
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
	// �÷��̾� ������� ���� �������� �Լ�
	void	LodingData(PlayerDataSet data);
	// �÷��̾� �̾��ϱ� ���ý� ������ ��� �������� ����� �Լ�
	void	SaveDataLoding();
	// �÷��̾� ���������� �Ѱ� �����ִ� �Լ� <== ���࿹�� (24.10.27)
	void	SaveDataView(PlayerDataSet data);
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
	// int ���ڸ� PlayerDataSet���� �����Լ�
	PlayerDataSet intToPds(int data);
	// PlayerInfo �� PlayerDataSet�� �����ϴ� �Լ�
	void	DataFileSave(PlayerDataSet Data);
	// PlayerInfo�� CruData �� �����ϴ� �Լ�, ��������
	void	CurDataSave() { DataFileSave(PlayerDataSet::CurData); }
	// PlayerInfo�� string���� ��ȯ�ؼ� ��ȯ�ϴ� �Լ�
	string  PlayInfoToSting();
	// ��ȯ������ �Է��� int�� �޴� �Լ�
	int		CinAuto();
	// ����ȭ������ �����ϴ� �Լ�
	void	BattleStartInit();
	
	friend class EneMy;
};

