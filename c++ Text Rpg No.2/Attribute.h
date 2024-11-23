#pragma once

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


// 자기 자신의 저항래벨
enum class Resistance : int {
    Immune,        // 면역 (데미지 없음)
    Strong,      // 내성 (0.25배 데미지)
    Resistant,   // 견딤 (0.5배 데미지)
    Normal,     // 보통 (1배 데미지)
    Vulnerable, // 약점 (1.5배 데미지)
    Weak,        // 취약 (2배 데미지)
    end         //이상한값 처리
};
struct Main_AT
{
    Resistance      MY_RL; // 저항레밸
    int             S_Level;// 숙련도(레벨)
    int             S_EXP; // 숙련치(경험치)
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
    // 데미지 계산 함수, 피해자가 이 함수를 호출해야됨
    // int는 가해자의 공격력, AttackType은 가해자의 공격타입
    // 출력값으로 피해자의 저항력과 비교하여 최종 데미지 나옴
    int calculateDamage(int baseDamage, AttackType attackType) const;
    // 데미지 계산시에 자신의 스킬레밸에 비례하여 데미지 상승값 반환
    int SLDamage(int base, Main_AT type) const;
    // 공격 타입별 저항 레벨 설정 함수
    void SetRL(AttackType type, Resistance level);
    // AttackType 입력되면 해당 숙련도 반환
    int AT_to_ATL(AttackType type);
    // AttackType 입력되면 해당 숙련 경험치 반환
    int AT_to_ATE(AttackType type);
    // Resistance가 입력되면 int변환
    // 멤버 변수를 변경하지 않도록 제한
    int RLConvert(Resistance R_L) const;
    // int가 입력되면 Resistance변환
    Resistance RLConvert(int Data);
    // int가 입력되면 AttackType변환
    AttackType  ATConvert(int Data);
    // 적에게 준 피해량 만큼 경험치 얻는 함수
    void Damage_to_SPUP(int Damage)
    {
        T_MAP[My_AT].S_EXP += Damage;
    }
    // 반복문시 for문을 위한 열거함수
    vector<AttackType> getAttackTypes() {
        return { AttackType::Blunt, AttackType::Pierce, AttackType::Slash };
    }
    // AttackType 에 해당하는 SL을 변경하는 함수
    void Set_SL(AttackType type, int Data);
    // AttackType 에 해당하는 SL을 변경하는 함수
    void Set_SE(AttackType type, int Data);
    //	적과 싸운 후 얻은 숙련도 적용
    void	SkillUpCheck();
    // 숙련도가 높을경우 숙련도 레벨업 적용
    // 경험치상한만큼 빼고 레벨업 하는 함수
    // 현재 미사용, 나중에 추가한다면 while문을 옮겨 와야 할듯
    void	SU_Practice(int expCut);
private:
    // 속성 도감 느낌으로 사용
    std::unordered_map<AttackType, Main_AT> T_MAP;

public:
    Attribute();
    ~Attribute();
};
#endif // ATTRIBUTE_H
// 공격 타입은 변수로 따로 있음
// 공격 타입에 따른 스킬 래벨도 존재함, Exp도 있음
// 공격 타입을 방어하는 취약도 가지기