#pragma once
#include <raylib.h>

class Tile
{
public:
    Tile();
    void Unload();
    void AddTexture(Texture);
    int id;
    Model model;
    Texture texture;
    int damage;

private:
};