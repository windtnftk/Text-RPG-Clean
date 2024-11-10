#include"pch.h"
#include "Attribute.h"
// �ϴ� �� ���� ����� ������� ���ĺ���
	// ĳ���� ������ ������ class
	// ���� ������ ������ class
	// ������ ������ ������ class
	// �װ� �������ִ� iterator ����� ����
	// �װ� ��� ����ؼ� ��� ����
class Attribute;
enum class GameMode; // �̷� enum class�� �ִٰ� �̸� ����
enum class EnemyId
{
	Enemy0,
	Enemy1,
	Enemy2,
	Enemy3,
	Enemy4,
	Enemy5,
	Enemy6,
	Enemy7,
	Enemy8,
	Enemy9,
	God
};

struct B_Status
{
	string		C_Name;// ĳ���� �̸�
	int			C_Level;// ĳ���� ����
	int			C_Power;// ĳ���� ��
	int			C_Health;// ĳ���� �����
	int			C_Exp;//óġ�� ����ġ
};
struct E_Info
{
	B_Status		E_BInfo;//���� �⺻����
	//B_Status		E_CurInfo;// ���� ���簪
	int				E_Plase;//���� ������ġ
	bool			E_Life;//���� ��������
	Attribute		attribute;// ���� Ư�� ���� (�߰�)
};
struct E_Check
{
	B_Status	Info;// �� óġ�� �� ����
	bool		Check;//��ȯ������ false�� ����, true�� ����
};



class EneMy
{
	SINGLE(EneMy);
public:
	map<EnemyId, E_Info> E_BasicInfo;//���� �������
	map<EnemyId, E_Info>::iterator	E_Point; //�� ����
	//Attribute		E_Type;			//������ ����Ÿ��
public:		// ���� �� �ʱ�ȭ �Լ�

	// ���� �ʱ�ȭ
	void EnemyInit();
	// ������ ���̵��� ���� ���� ������ ���� ��Ű�� �Լ�
	//B_Status StatChange(GameMode CurMode, EnemyId id);
	// ���� �� ����� ��ȯ���ִ� �Լ�
	int CurSize() { return (int)EneMy::GetInst()->E_BasicInfo.size(); };
	// ������ ���̵��� ���� ���� �����ϴ� �Լ�
	void CreateEnemy(GameMode CurMode);

public:		//���� �����ϴ� �Լ�

	// �ο�� �ִ� ���� ������ ������ִ� �Լ�
	// ��ȯ���� �޾Ƽ� ���� �� ����
	E_Info SetEnemyInfo();
	// ��� ���� ���� ��ȸ�ϴ� �Լ�
	void ViewEnemy();
	// �μ��� ���� ���� ������ �޾� ���� ������ �ִ��� Ȯ��
	// ���� ���� �� �ൿ �� �ѹ� Ȯ�ο�, false�� ������ �ٷ� ����
	bool DeadCheck(E_Info Info)
	{
		return (Info.E_BInfo.C_Health > 0) ? true : false;
	}


public:		// ���� ��ȯ �Լ�, ������� �Լ�

	// ���ϴ� id ���� Base ������ ������ִ� �Լ�
	void printEnemyBaseInfo(EnemyId data);
	// E_Info�� ������ ����ϴ� �Լ�
	// ��ȯ������ �Էµ� ���� ü���� ������ Ȯ��
	// �� DeadCheck�� Ȯ���ϵ��� ����
	void printCurInfo(E_Info data);
	// ���ϴ� id ���� Cur ������ ������ִ� �Լ�
	// ���� ������� ����
	void printEnemyCurInfo(EnemyId data);
	// id �� ���� ���� �ּҰ� ��ȯ�ϴ� �Լ�
	E_Info* IdReturn(EnemyId Id);
	// int �� ���� EnemyId�� �ٲ��ִ� �Լ�
	EnemyId EidReturn(int id);

private:
	//void CreateEnemy( int	id);
};

