#include "playerClass.h"
#include "attacks.cpp"

class Barbarian : public PlayerClass
{
public:
    Barbarian()
    {
        action_points = 2;
        attacks = {MeleeAttack()};
    }
};

class Fighter : public PlayerClass
{
public:
    Fighter()
    {
        action_points = 1;
        attacks = {MeleeAttack(), RangeAttack()};
    }
};

class Wizard : public PlayerClass
{
public:
    Wizard()
    {
        action_points = 1;
        attacks = {};
    }
};

class Paladin : public PlayerClass
{
public:
    Paladin()
    {
        action_points = 1;
        attacks = {MeleeAttack()};
    }
};