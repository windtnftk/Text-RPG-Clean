#include "pch.h"
#include "Attribute.h"



// ������ ��� �Լ�
// int�� �������� ���ݷ�, AttackType�� �������� ����Ÿ��
// ��°����� ���� Ŭ�������� ������ Type ��갪�� �����
int Attribute::calculateDamage(int baseDamage, AttackType attackType) const
{
    auto it = resistanceLevels.find(attackType);
    if (it != resistanceLevels.end()) {
        int multiplier = static_cast<int>(it->second);
        return (baseDamage * multiplier) / 100;
    }
    return baseDamage; // �⺻ ������
}

// ���� ���� ���� �Լ�
void Attribute::setResistanceLevel(AttackType type, ResistanceLevel level) 
{
    resistanceLevels[type] = level;
}
// �⺻ �����ڿ��� ��� ���� Ÿ���� �⺻ ���� ����
Attribute::Attribute() {
    resistanceLevels[AttackType::Blunt] = ResistanceLevel::Normal;
    resistanceLevels[AttackType::Pierce] = ResistanceLevel::Normal;
    resistanceLevels[AttackType::Slash] = ResistanceLevel::Normal;
}

Attribute::~Attribute()
{
}
