#include "playerClass.h"
#include "attacks.cpp"

class Barbarian : public PlayerClass
{
public:
    Barbarian()
    {
        DEFAULT_ACTION_POINTS = 2;
        attacks = {MeleeAttack()};
    }
};

class Fighter : public PlayerClass
{
public:
    Fighter()
    {
        DEFAULT_ACTION_POINTS = 1;
        attacks = {MeleeAttack(), RangeAttack()};
    }
};

class Wizard : public PlayerClass
{
public:
    Wizard()
    {
        DEFAULT_ACTION_POINTS = 1;
        attacks = {};
    }
};

class Paladin : public PlayerClass
{
public:
    Paladin()
    {
        DEFAULT_ACTION_POINTS = 1;
        attacks = {MeleeAttack()};
    }
};