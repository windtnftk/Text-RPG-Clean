#include "pch.h"
#include "Attribute.h"



// 데미지 계산 함수
// int는 가해자의 공격력, AttackType은 가해자의 공격타입
// 출력값으로 현재 클래스변수 선언한 Type 계산값을 출력함
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
void Attribute::setResistanceLevel(AttackType type, ResistanceLevel level) 
{
    resistanceLevels[type] = level;
}
// 기본 생성자에서 모든 공격 타입의 기본 저항 설정
Attribute::Attribute() {
    resistanceLevels[AttackType::Blunt] = ResistanceLevel::Normal;
    resistanceLevels[AttackType::Pierce] = ResistanceLevel::Normal;
    resistanceLevels[AttackType::Slash] = ResistanceLevel::Normal;
}

Attribute::~Attribute()
{
}
