#pragma once
enum class ResistanceLevel : int {
    Weak = 200,       // 취약 (2배 데미지)
    Vulnerable = 150, // 약점 (1.5배 데미지)
    Normal = 100,     // 보통 (1배 데미지)
    Resistant = 50,   // 견딤 (0.5배 데미지)
    Strong = 25,      // 내성 (0.25배 데미지)
    Immune = 0        // 면역 (데미지 없음)
};
enum class AttackType {
    Blunt,  // 타격
    Pierce, // 관통
    Slash   // 참격
};
class Attribute{
public:
    

    // 데미지 계산 함수
    int calculateDamage(int baseDamage, AttackType attackType) const;

    // 공격 타입별 저항 레벨 설정 함수
    void setResistanceLevel(AttackType type, ResistanceLevel level);

    // 
private:
    std::unordered_map<AttackType, ResistanceLevel> resistanceLevels;

public:
    Attribute();
    ~Attribute();
};

