#include"pch.h"
// 일단 다 따로 만들고 상속으로 합쳐보자
	// 캐릭터 정보를 저장할 class
	// 몬스터 정보를 저장할 class
	// 아이템 정보를 저장할 class
	// 그걸 관리해주는 iterator 만들고 진행
	// 그걸 모두 상속해서 사용 하자

enum class GameMode; // 이런 enum class가 있다고 미리 선언
enum class EnemyId
{
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
	string		C_Name;// 캐릭터 이름
	int			C_Level;// 캐릭터 래벨
	int			C_Power;// 캐릭터 힘
	int			C_Health;// 캐릭터 생명력
	int			C_Exp;//처치시 경험치
};
struct E_Info
{
	B_Status		E_BInfo;//몬스터 기본정보
	B_Status		E_CurInfo;// 몬스터 현재값
	int				E_Plase;//몬스터 생존위치
	bool			E_Life;//몬스터 생존여부
};



class EneMy
{
	SINGLE(EneMy);
public:
	map<EnemyId, E_Info> E_BasicInfo;//적의 모든정보
	map<EnemyId, E_Info>::iterator	E_Point; //적 세팅
	
public:
	// 정보 초기화
	void EnemyInit();
	// 원하는 id 값을 Base 정보로 출력해주는 함수
	void printEnemyBaseInfo(EnemyId data);
	// 원하는 id 값을 Cur 정보로 출력해주는 함수
	void printEnemyCurInfo(EnemyId data);
	// 싸우고 있는 적의 정보로 출력해주는 함수
	void SetEnemyInfo();
	// id 값 쓰면 정보 주소값 변환하는 함수
	E_Info* IdReturn(EnemyId Id);
	// int 값 쓰면 EnemyId로 바꿔주는 함수
	EnemyId EidReturn(int id);
	// 설정한 난이도에 따라 적의 스탯을 변한 시키는 함수
	//B_Status StatChange(GameMode CurMode, EnemyId id);
	// 적의 총 사이즈를 변환해주는 함수
	int CurSize() { return (int)EneMy::GetInst()->E_BasicInfo.size(); };
	// 설정한 난이도에 따라 적을 생성하는 함수
	void CreateEnemy(GameMode CurMode);
	// 적들 정보 순회하는 함수
	void ViewEnemy();
private:
	//void CreateEnemy( int	id);
};

