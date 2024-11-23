#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


// �ڱ� �ڽ��� ���׷���
enum class Resistance : int {
    Immune,        // �鿪 (������ ����)
    Strong,      // ���� (0.25�� ������)
    Resistant,   // �ߵ� (0.5�� ������)
    Normal,     // ���� (1�� ������)
    Vulnerable, // ���� (1.5�� ������)
    Weak,        // ��� (2�� ������)
    end         //�̻��Ѱ� ó��
};
struct Main_AT
{
    Resistance      MY_RL; // ���׷���
    int             S_Level;// ���õ�(����)
    int             S_EXP; // ����ġ(����ġ)
};
enum class AttackType {
    Blunt,  // Ÿ��
    Pierce, // ����
    Slash,   // ����
    End
};
class Attribute{
public:
    AttackType  My_AT; //�ڱ� �ڽ��� ����Ÿ��
    // ������ ��� �Լ�, �����ڰ� �� �Լ��� ȣ���ؾߵ�
    // int�� �������� ���ݷ�, AttackType�� �������� ����Ÿ��
    // ��°����� �������� ���׷°� ���Ͽ� ���� ������ ����
    int calculateDamage(int baseDamage, AttackType attackType) const;
    // ������ ���ÿ� �ڽ��� ��ų���뿡 ����Ͽ� ������ ��°� ��ȯ
    int SLDamage(int base, Main_AT type) const;
    // ���� Ÿ�Ժ� ���� ���� ���� �Լ�
    void SetRL(AttackType type, Resistance level);
    // AttackType �ԷµǸ� �ش� ���õ� ��ȯ
    int AT_to_ATL(AttackType type);
    // AttackType �ԷµǸ� �ش� ���� ����ġ ��ȯ
    int AT_to_ATE(AttackType type);
    // Resistance�� �ԷµǸ� int��ȯ
    // ��� ������ �������� �ʵ��� ����
    int RLConvert(Resistance R_L) const;
    // int�� �ԷµǸ� Resistance��ȯ
    Resistance RLConvert(int Data);
    // int�� �ԷµǸ� AttackType��ȯ
    AttackType  ATConvert(int Data);
    // ������ �� ���ط� ��ŭ ����ġ ��� �Լ�
    void Damage_to_SPUP(int Damage)
    {
        T_MAP[My_AT].S_EXP += Damage;
    }
    // �ݺ����� for���� ���� �����Լ�
    vector<AttackType> getAttackTypes() {
        return { AttackType::Blunt, AttackType::Pierce, AttackType::Slash };
    }
    // AttackType �� �ش��ϴ� SL�� �����ϴ� �Լ�
    void Set_SL(AttackType type, int Data);
    // AttackType �� �ش��ϴ� SL�� �����ϴ� �Լ�
    void Set_SE(AttackType type, int Data);
    //	���� �ο� �� ���� ���õ� ����
    void	SkillUpCheck();
    // ���õ��� ������� ���õ� ������ ����
    // ����ġ���Ѹ�ŭ ���� ������ �ϴ� �Լ�
    // ���� �̻��, ���߿� �߰��Ѵٸ� while���� �Ű� �;� �ҵ�
    void	SU_Practice(int expCut);
private:
    // �Ӽ� ���� �������� ���
    std::unordered_map<AttackType, Main_AT> T_MAP;

public:
    Attribute();
    ~Attribute();
};
#endif // ATTRIBUTE_H
// ���� Ÿ���� ������ ���� ����
// ���� Ÿ�Կ� ���� ��ų ������ ������, Exp�� ����
// ���� Ÿ���� ����ϴ� ��൵ ������