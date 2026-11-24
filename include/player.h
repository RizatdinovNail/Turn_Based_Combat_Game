#pragma once
#include <raylib.h>
#include "playerClass.h"
#include "consumable.h"
#include <map>

class Player
{
public:
    Player();
    void MoveDown(float);
    void MoveUp(float);
    void MoveRight(float);
    void MoveLeft(float);
    void ReciveDamage(int);
    void Attack(Player, int);
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

    PlayerClass player_class;
    std::map<Consumable, int> inventory;

private:
    int RollDice(int);
    bool EnoughMovement();
};