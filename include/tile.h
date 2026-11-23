#pragma once
#include <raylib.h>

class Tile
{
public:
    Tile();
    void Unload();
    int id;
    Model model;
    int damage;

private:
};