#pragma once
#include <raylib.h>

class Player
{
public:
    Player();
    void MoveDown(float);
    void MoveUp(float);
    void MoveRight(float);
    void MoveLeft(float);

    int id;
    Model model;
    Vector3 position;
    int HP = 20;

private:
};