#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

struct Main_AT
{
    ResistanceLevel MY_RL;
    int             S_Level;
    int             S_EXP;
};
// 자기 자신의 저항래벨
enum class ResistanceLevel : int {
    Immune,        // 면역 (데미지 없음)
    Strong,      // 내성 (0.25배 데미지)
    Resistant,   // 견딤 (0.5배 데미지)
    Normal,     // 보통 (1배 데미지)
    Vulnerable, // 약점 (1.5배 데미지)
    Weak,        // 취약 (2배 데미지)
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
    // int는 가해자의 공격력, AttackType은 가해자의 공격타입
    // 출력값으로 현재 클래스변수 선언한 Type 계산값을 출력함
    int calculateDamage(int baseDamage, AttackType attackType) const;
    // 데미지 계산시에 자신의 스킬레밸에 비례하여 데미지 상승값 반환
    int SLDamage(int base, const Main_AT& type) const;
    // 공격 타입별 저항 레벨 설정 함수
    void SetRL(AttackType type, ResistanceLevel level);
    // AttackType 입력되면 해당 숙련도 반환
    int AT_to_ATL(AttackType type);
    // AttackType 입력되면 해당 숙련 경험치 반환
    int AT_to_ATE(AttackType type);
    // ResistanceLevel가 입력되면 int변환
    int RLConvert(ResistanceLevel R_L);
    // int가 입력되면 ResistanceLevel변환
    ResistanceLevel RLConvert(int Data);
    // int가 입력되면 AttackType변환
    AttackType  ATConvert(int Data);
     
private:
    // 속성 도감 느낌으로 사용
    std::unordered_map<AttackType, Main_AT> resistanceLevels;

public:
    Attribute();
    ~Attribute();
};
#endif // ATTRIBUTE_H
// 공격 타입은 변수로 따로 있음
// 공격 타입에 따른 스킬 래벨도 존재함, Exp도 있음
// 공격 타입을 방어하는 취약도 가지기