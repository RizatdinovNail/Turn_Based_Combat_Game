#include <iostream>
#include "concretePlayerStates.h"

void Wait::enter(Player *player)
{
    std::cout << player->id << " is waiting" << std::endl;
}

void Wait::toggle(Player *player)
{
    player->setState(Play::getInstance());
}

void Wait::exit(Player *player)
{
    std::cout << player->id << " is exiting waiting state" << std::endl;
}

PlayerState &Wait::getInstance()
{
    static Wait singleton;
    return singleton;
}

void Play::enter(Player *player)
{
    player->speed = player->DEFAULT_SPEED;
    player->action_points = player->player_class.DEFAULT_ACTION_POINTS;
    std::cout << player->id << " is playing" << std::endl;
}

void Play::toggle(Player *player)
{
    player->setState(Pass::getInstance());
}

void Play::exit(Player *player)
{
    std::cout << player->id << " is exiting playing state" << std::endl;
}

PlayerState &Play::getInstance()
{
    static Play singleton;
    return singleton;
}

void Pass::enter(Player *player)
{
    std::cout << player->id << " is passing the turn" << std::endl;
}

void Pass::toggle(Player *player)
{
    player->setState(Wait::getInstance());
}

void Pass::exit(Player *player)
{
    std::cout << player->id << " is exiting passing state" << std::endl;
}

PlayerState &Pass::getInstance()
{
    static Pass singleton;
    return singleton;
}