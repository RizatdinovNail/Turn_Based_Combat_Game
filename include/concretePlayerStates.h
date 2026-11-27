#pragma once
#include "playerState.h"
#include "player.h"

class Wait : public PlayerState
{
public:
    void enter(Player *player);
    void toggle(Player *player);
    void exit(Player *player);
    static PlayerState &getInstance();

private:
    Wait() {};
    Wait(const Wait &other);
    Wait &operator=(const Wait &other);
};

class Play : public PlayerState
{
public:
    void enter(Player *player);
    void toggle(Player *player);
    void exit(Player *player);
    static PlayerState &getInstance();

private:
    Play() {};
    Play(const Play &other);
    Play &operator=(const Play &other);
};

class Pass : public PlayerState
{
public:
    void enter(Player *player);
    void toggle(Player *player);
    void exit(Player *player);
    static PlayerState &getInstance();

private:
    Pass() {};
    Pass(const Pass &other);
    Pass &operator=(const Pass &other);
};