#pragma once
#include <raylib.h>
#include "tiles.cpp"
#include "players.cpp"
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
    void InitPlayers();
    void ShowPlayers();
    void SetUpPlayer(Player &);
    Model GetRandomTile();
    std::vector<Tile> GetAllTiles();
    std::vector<size_t> GenerateMap();
    void HandleInput();
    bool isValid(float);

    // VARIABLES
    float grid_offset;
    int grid_size;
    float grid_spacing;
    std::vector<size_t> map;
    std::vector<Tile> tilePrototypes;
    Texture texture;
    Texture player_texture;
    HumanPlayer humanPlayer;
    AIPlayer aiPlayer;
};