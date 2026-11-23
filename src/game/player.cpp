#include "player.h"

Player::Player()
{
}

void Player::MoveDown(float gridSpacing)
{
    position = Vector3{position.x, 0.0f, position.z + gridSpacing};
}

void Player::MoveUp(float gridSpacing)
{
    position = Vector3(position.x, 0.0f, position.z - gridSpacing);
}

void Player::MoveLeft(float gridSpacing)
{
    position = Vector3(position.x - gridSpacing, 0.0f, position.z);
}

void Player::MoveRight(float gridSpacing)
{
    position = Vector3(position.x + gridSpacing, 0.0f, position.z);
}