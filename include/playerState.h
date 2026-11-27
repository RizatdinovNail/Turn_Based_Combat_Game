#pragma once
#include "player.h"

class Player;

class PlayerState
{
public:
    virtual void enter(Player *player) = 0;
    virtual void toggle(Player *player) = 0;
    virtual void exit(Player *player) = 0;
    virtual ~PlayerState() {};

private:
};