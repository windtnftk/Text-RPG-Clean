#include "pch.h"
#include "Attribute.h"


// ������ ��� �Լ�
int Attribute::calculateDamage(int baseDamage, AttackType attackType) const
{
    auto it = resistanceLevels.find(attackType);
    if (it != resistanceLevels.end()) {
        SLDamage(baseDamage,it->second );
        int multiplier = static_cast<int>(it->second.MY_RL);
        return (baseDamage * multiplier) / 100;
    }
    return baseDamage; // �⺻ ������
}
int Attribute::SLDamage(int base, const Main_AT& type) const
{
    
    return 0;
}
// ���� ���� ���� �Լ�
void Attribute::SetRL(AttackType type, ResistanceLevel level) 
{
    resistanceLevels[type].MY_RL = level;
}
int Attribute::AT_to_ATL(AttackType type)
{
    return resistanceLevels[type].S_Level;
}
int Attribute::AT_to_ATE(AttackType type)
{
    return resistanceLevels[type].S_EXP;
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
        std::cout << "���!!! �߸��� ���׷����� �ԷµǾ����ϴ�." << std::endl;
        return ResistanceLevel::end;
    }
    return static_cast<ResistanceLevel>(Data);
}
AttackType Attribute::ATConvert(int Data)
{
    if (Data > 2)
    {
        std::cout << "���!!! �߸��� ���׷����� �ԷµǾ����ϴ�." << std::endl;
        return AttackType::End;
    }
    return static_cast<AttackType>(Data);
}
// �⺻ �����ڿ��� ��� ���� Ÿ���� �⺻ ���� ����
Attribute::Attribute()
    :My_AT(AttackType::Blunt)
{
    resistanceLevels[AttackType::Blunt] = { ResistanceLevel::Normal,1,0};
    resistanceLevels[AttackType::Pierce] = { ResistanceLevel::Normal,1,0 };
    resistanceLevels[AttackType::Slash] = { ResistanceLevel::Normal,1,0 };
}

Attribute::~Attribute()
{
}
