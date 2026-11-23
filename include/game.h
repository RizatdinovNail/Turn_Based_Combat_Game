#pragma once
#include <raylib.h>
#include "tiles.cpp"
#include <vector>

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
    std::vector<Tile> GetAllTiles();
    std::vector<size_t> GenerateMap();

    // VARIABLES
    float grid_offset;
    int grid_size;
    float grid_spacing;
    std::vector<size_t> map;
    std::vector<Tile> tilePrototypes;
};