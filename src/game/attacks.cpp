#include "attack.h"

class MeleeAttack : public Attack
{
public:
    MeleeAttack()
    {
        name = "Melee Attack";
        type = MELEE;
        damage = 12;
    }
};

class RangeAttack : public Attack
{
public:
    RangeAttack()
    {
        name = "Range Attack";
        type = RANGE;
        damage = 12;
    }
};