#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

// 자기 자신의 저항래벨
enum class ResistanceLevel : int {
    Immune,        // 면역 (데미지 없음)
    Strong,      // 내성 (0.25배 데미지)
    Resistant,   // 견딤 (0.5배 데미지)
    Normal,     // 보통 (1배 데미지)
    Vulnerable, // 약점 (1.5배 데미지)
    Weak,         // 취약 (2배 데미지)
    end         //이상한값 처리
};
enum class AttackType {
    Blunt,  // 타격
    Pierce, // 관통
    Slash,   // 참격
    End
};
class Attribute{
public:
   
    AttackType  My_AT; //자기 자신의 공격타입
    // 데미지 계산 함수
    int calculateDamage(int baseDamage, AttackType attackType) const;

    // 공격 타입별 저항 레벨 설정 함수
    void SetRL(AttackType type, ResistanceLevel level);
    // ResistanceLevel가 입력되면 int변환
    int RLConvert(ResistanceLevel R_L);
    // int가 입력되면 ResistanceLevel변환
    ResistanceLevel RLConvert(int Data);
    // int가 입력되면 AttackType변환
    AttackType  ATCovert(int Data);
     
private:
    std::unordered_map<AttackType, ResistanceLevel> resistanceLevels;

public:
    Attribute();
    ~Attribute();
};
#endif // ATTRIBUTE_H
