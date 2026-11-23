#pragma once
#include "tiles.h"

class Game
{
public:
    Game(int, float);

    void Run();
    void Stop();

private:
    // FUNCTIONS
    void InitMap();
    Model GetRandomTile();
    std::vector<Model> CreateMap();
    // VARIABLES
    Tiles tiles;
    std::vector<Model> allTiles;
    Texture texture;
    std::vector<Model> map;
    float grid_offset;
    int grid_size;
    float grid_spacing;
};