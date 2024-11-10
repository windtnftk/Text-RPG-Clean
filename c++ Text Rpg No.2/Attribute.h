#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

// �ڱ� �ڽ��� ���׷���
enum class ResistanceLevel : int {
    Immune,        // �鿪 (������ ����)
    Strong,      // ���� (0.25�� ������)
    Resistant,   // �ߵ� (0.5�� ������)
    Normal,     // ���� (1�� ������)
    Vulnerable, // ���� (1.5�� ������)
    Weak,         // ��� (2�� ������)
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
    int calculateDamage(int baseDamage, AttackType attackType) const;

    // ���� Ÿ�Ժ� ���� ���� ���� �Լ�
    void SetRL(AttackType type, ResistanceLevel level);
    // ResistanceLevel�� �ԷµǸ� int��ȯ
    int RLConvert(ResistanceLevel R_L);
    // int�� �ԷµǸ� ResistanceLevel��ȯ
    ResistanceLevel RLConvert(int Data);
    // int�� �ԷµǸ� AttackType��ȯ
    AttackType  ATCovert(int Data);
     
private:
    std::unordered_map<AttackType, ResistanceLevel> resistanceLevels;

public:
    Attribute();
    ~Attribute();
};
#endif // ATTRIBUTE_H
