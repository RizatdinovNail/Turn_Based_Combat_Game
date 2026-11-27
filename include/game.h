#pragma once

#include <vector>
#include <cstddef>
#include "raylib.h"
#include "players.cpp"
#include "tile.h"

struct TileInstance
{
    size_t protoIdx = 0;
    Vector3 position{0.0f, 0.0f, 0.0f};
    float scale = 1.3f;
    int damage = 0;
};

class Game
{
public:
    Game(int gridSize, float gridSpacing);
    ~Game();

    // Prevent accidental shallow copies that would double-free Raylib GPU resources
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    void Run();
    void Stop();

private:
    int grid_size = 0;
    float grid_spacing = 1.0f;
    float grid_offset = 0.0f;
    float min_bound = 0.0f;
    float max_bound = 0.0f;

    Texture2D texture{};
    Texture2D player_texture{};

    std::vector<Tile> tilePrototypes;
    std::vector<TileInstance> gridCells;

    HumanPlayer humanPlayer;
    AIPlayer aiPlayer;

    bool isCleanedUp = false;

    std::vector<Tile> GetAllTiles();
    void BuildGrid();
    void DrawMap() const;

    void InitPlayers();
    void SetUpPlayer(Player &player);
    void ShowPlayers() const;

    void HandleInput();
    void TryMoveHuman(float dx, float dz);
    bool IsWithinBounds(float coord) const;
    bool TryGetCellIndex(Vector3 worldPos, size_t &outIdx) const;
};