#include "player.h"
#include <random>
#include <iostream>

Player::Player()
{
}

void Player::MoveDown(float gridSpacing)
{
    if (!EnoughMovement())
        return;
    position = Vector3{position.x, 0.0f, position.z + gridSpacing};
    speed -= 5;
}

void Player::MoveUp(float gridSpacing)
{
    if (!EnoughMovement())
        return;
    position = Vector3(position.x, 0.0f, position.z - gridSpacing);
    speed -= 5;
}

void Player::MoveLeft(float gridSpacing)
{
    if (!EnoughMovement())
        return;
    position = Vector3(position.x - gridSpacing, 0.0f, position.z);
    speed -= 5;
}

void Player::MoveRight(float gridSpacing)
{
    if (!EnoughMovement())
        return;
    position = Vector3(position.x + gridSpacing, 0.0f, position.z);
    speed -= 5;
}

void Player::ReciveDamage(int damage)
{
    hp -= damage;
}

void Player::Heal(int health)
{
    hp += health;
}

void Player::Attack(Player enemy, int attack_id)
{
    int dice_result = RollDice(20);
    if (dice_result >= enemy.ac)
    {
        int damage = RollDice(player_class.attacks[attack_id].damage);
        enemy.ReciveDamage(damage);
    }
}

void Player::UseConsumable() {}

int Player::RollDice(int diceSize)
{
    int result;
    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<size_t> dist(0, diceSize - 1);
    result = dist(rng);
    return result;
}

bool Player::EnoughMovement()
{
    if (speed < 5)
    {
        std::cout << "NOT ENOUGH MOVEMENT" << std::endl;
        return false;
    }

    return true;
}