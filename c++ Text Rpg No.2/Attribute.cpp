#include "pch.h"
#include "Attribute.h"



// 데미지 계산 함수
int Attribute::calculateDamage(int baseDamage, AttackType attackType) const
{
    auto it = resistanceLevels.find(attackType);
    if (it != resistanceLevels.end()) {
        int multiplier = static_cast<int>(it->second);
        return (baseDamage * multiplier) / 100;
    }
    return baseDamage; // 기본 데미지
}

// 저항 레벨 설정 함수
void Attribute::SetRL(AttackType type, ResistanceLevel level) 
{
    resistanceLevels[type] = level;
}
int Attribute::RLConvert(ResistanceLevel R_L)
{
    switch (R_L)
    {
    case ResistanceLevel::Immune:
        return 0;
        break;
    case ResistanceLevel::Strong:
        return 25;
        break;
    case ResistanceLevel::Resistant:
        return 50;
        break;
    case ResistanceLevel::Normal:
        return 100;
        break;
    case ResistanceLevel::Vulnerable:
        return 150;
        break;
    case ResistanceLevel::Weak:
        return 200;
        break;
    default:
        return 200;
        break;
    }
}
ResistanceLevel Attribute::RLConvert(int Data)
{
    if (Data > 5)
    {
        std::cout << "경고!!! 잘못된 저항레벨이 입력되었습니다." << std::endl;
        return ResistanceLevel::end;
    }
    return static_cast<ResistanceLevel>(Data);
}
AttackType Attribute::ATCovert(int Data)
{
    if (Data > 2)
    {
        std::cout << "경고!!! 잘못된 저항레벨이 입력되었습니다." << std::endl;
        return AttackType::End;
    }
    return static_cast<AttackType>(Data);
}
// 기본 생성자에서 모든 공격 타입의 기본 저항 설정
Attribute::Attribute()
    :My_AT(AttackType::Blunt)
{
    resistanceLevels[AttackType::Blunt] = ResistanceLevel::Normal;
    resistanceLevels[AttackType::Pierce] = ResistanceLevel::Normal;
    resistanceLevels[AttackType::Slash] = ResistanceLevel::Normal;
}

Attribute::~Attribute()
{
}
