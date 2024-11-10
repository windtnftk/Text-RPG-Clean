#pragma once
enum class ResistanceLevel : int {
    Weak = 200,       // ��� (2�� ������)
    Vulnerable = 150, // ���� (1.5�� ������)
    Normal = 100,     // ���� (1�� ������)
    Resistant = 50,   // �ߵ� (0.5�� ������)
    Strong = 25,      // ���� (0.25�� ������)
    Immune = 0        // �鿪 (������ ����)
};
enum class AttackType {
    Blunt,  // Ÿ��
    Pierce, // ����
    Slash   // ����
};
class Attribute{
public:
    

    // ������ ��� �Լ�
    int calculateDamage(int baseDamage, AttackType attackType) const;

    // ���� Ÿ�Ժ� ���� ���� ���� �Լ�
    void setResistanceLevel(AttackType type, ResistanceLevel level);

    // 
private:
    std::unordered_map<AttackType, ResistanceLevel> resistanceLevels;

public:
    Attribute();
    ~Attribute();
};

