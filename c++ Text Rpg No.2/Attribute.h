#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

struct Main_AT
{
    ResistanceLevel MY_RL;
    int             S_Level;
    int             S_EXP;
};
// �ڱ� �ڽ��� ���׷���
enum class ResistanceLevel : int {
    Immune,        // �鿪 (������ ����)
    Strong,      // ���� (0.25�� ������)
    Resistant,   // �ߵ� (0.5�� ������)
    Normal,     // ���� (1�� ������)
    Vulnerable, // ���� (1.5�� ������)
    Weak,        // ��� (2�� ������)
    end         //�̻��Ѱ� ó��
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
    // ������ ��� �Լ�
    // int�� �������� ���ݷ�, AttackType�� �������� ����Ÿ��
    // ��°����� ���� Ŭ�������� ������ Type ��갪�� �����
    int calculateDamage(int baseDamage, AttackType attackType) const;
    // ������ ���ÿ� �ڽ��� ��ų���뿡 ����Ͽ� ������ ��°� ��ȯ
    int SLDamage(int base, const Main_AT& type) const;
    // ���� Ÿ�Ժ� ���� ���� ���� �Լ�
    void SetRL(AttackType type, ResistanceLevel level);
    // AttackType �ԷµǸ� �ش� ���õ� ��ȯ
    int AT_to_ATL(AttackType type);
    // AttackType �ԷµǸ� �ش� ���� ����ġ ��ȯ
    int AT_to_ATE(AttackType type);
    // ResistanceLevel�� �ԷµǸ� int��ȯ
    int RLConvert(ResistanceLevel R_L);
    // int�� �ԷµǸ� ResistanceLevel��ȯ
    ResistanceLevel RLConvert(int Data);
    // int�� �ԷµǸ� AttackType��ȯ
    AttackType  ATConvert(int Data);
     
private:
    // �Ӽ� ���� �������� ���
    std::unordered_map<AttackType, Main_AT> resistanceLevels;

public:
    Attribute();
    ~Attribute();
};
#endif // ATTRIBUTE_H
// ���� Ÿ���� ������ ���� ����
// ���� Ÿ�Կ� ���� ��ų ������ ������, Exp�� ����
// ���� Ÿ���� ����ϴ� ��൵ ������