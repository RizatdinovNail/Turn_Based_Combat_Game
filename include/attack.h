#pragma once
#include <string>

class Attack
{
public:
    enum AttackType
    {
        SPELL,
        MELEE,
        RANGE
    };
    // Attack();
    std::string name;
    AttackType type;
    int damage;

private:
};