#include "pch.h"
#include "Attribute.h"


// 데미지 계산 함수
int Attribute::calculateDamage(int baseDamage, AttackType attackType) const
{
    auto it = T_MAP.find(attackType);
    if (it != T_MAP.end()) {
        return SLDamage(baseDamage, it->second);
    }
    return baseDamage; // 기본 데미지
}
int Attribute::SLDamage(int base, Main_AT type) const
{
    // 기본 데미지 * 공격타입의 숙련도 * 저항레밸(특성에 따라 편차있음) / RLConvert에 의한 100 나누기
    return base* type.S_Level* RLConvert(type.MY_RL)/100;
}
// 저항 레벨 설정 함수
void Attribute::SetRL(AttackType type, Resistance level) 
{
    T_MAP[type].MY_RL = level;
}
int Attribute::AT_to_ATL(AttackType type)
{
    return T_MAP[type].S_Level;
}
int Attribute::AT_to_ATE(AttackType type)
{
    return T_MAP[type].S_EXP;
}
int Attribute::RLConvert(Resistance R_L) const
{
    switch (R_L)
    {
    case Resistance::Immune:
        return 0;
        break;
    case Resistance::Strong:
        return 25;
        break;
    case Resistance::Resistant:
        return 50;
        break;
    case Resistance::Normal:
        return 100;
        break;
    case Resistance::Vulnerable:
        return 150;
        break;
    case Resistance::Weak:
        return 200;
        break;
    default:
        return 200;
        break;
    }
}
Resistance Attribute::RLConvert(int Data)
{
    if (Data > 5)
    {
        std::cout << "경고!!! 잘못된 저항레벨이 입력되었습니다." << std::endl;
        return Resistance::end;
    }
    return static_cast<Resistance>(Data);
}
AttackType Attribute::ATConvert(int Data)
{
    if (Data > 2)
    {
        std::cout << "경고!!! 잘못된 저항레벨이 입력되었습니다." << std::endl;
        return AttackType::End;
    }
    return static_cast<AttackType>(Data);
}
void Attribute::Set_SL(AttackType type, int Data)
{
    T_MAP[type].S_EXP = Data;
}
void Attribute::Set_SE(AttackType type, int Data)
{
    T_MAP[type].S_Level = Data;
}
void Attribute::SkillUpCheck()
{
    int expCut = 500;
    // for문 넣어서 Attack type만큼 순회
    for (auto q : getAttackTypes())
    {
        while (AT_to_ATE(q) >= expCut && AT_to_ATL(q) < 20) // TODO: 최대레밸,EXP 상수로 함 추후에 변경
        {
            T_MAP[q].S_EXP -= expCut;
            ++T_MAP[q].S_Level;
        }
    }
}
void Attribute::SU_Practice(int expCut)
{
    
}
// 기본 생성자에서 모든 공격 타입의 기본 저항 설정
Attribute::Attribute()
    :My_AT(AttackType::Blunt)
{
    T_MAP[AttackType::Blunt] = { Resistance::Normal,1,0};
    T_MAP[AttackType::Pierce] = { Resistance::Normal,1,0 };
    T_MAP[AttackType::Slash] = { Resistance::Normal,1,0 };
}

Attribute::~Attribute()
{
}
