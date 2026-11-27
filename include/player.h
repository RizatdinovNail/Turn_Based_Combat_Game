#pragma once
#include <raylib.h>
#include "playerClass.h"
#include "consumable.h"
#include <map>
#include "playerState.h"

class PlayerState;

class Player
{
public:
    Player();
    void MoveDown(float);
    void MoveUp(float);
    void MoveRight(float);
    void MoveLeft(float);
    void ReciveDamage(int);
    void Attack(Player &, int);
    void UseConsumable();
    void Heal(int);

    int id;
    Model model;

    Vector3 DEFAULT_POSITION;
    int DEFAULT_HP;
    int DEFAULT_AC;
    int DEFAULT_SPEED;

    int hp;
    int ac;
    int speed;
    Vector3 position;
    int action_points;

    PlayerClass player_class;
    std::map<Consumable, int> inventory;

    void setState(PlayerState &newState);
    void toggle();
    inline PlayerState *getCurrentState() const { return currentState; }

private:
    int RollDice(int);
    bool EnoughMovement();
    PlayerState *currentState;
};