#include <iostream>
#include <random>
#include "game.h"
#include <vector>

Game::Game(int gridSize, float gridSpacing)
{
    this->grid_size = gridSize;
    this->grid_spacing = gridSpacing;
    this->grid_offset = gridSize / 2 * gridSpacing - gridSpacing / 2;
    map = GenerateMap();
}

void Game::Run()
{
    InitMap();
}

std::vector<Tile> Game::GetAllTiles()
{
    return {Tile_A_Dirt(), Tile_B_Dirt(), Tile_C_Dirt(), Tile_D_Dirt(), Tile_Broken_A(), Tile_Broken_B(), Tile_Small(), Tile_Spikes()};
}

void Game::InitMap()
{
    if (map.empty() || tilePrototypes.empty())
        return;

    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            size_t mapIdx = static_cast<size_t>(i) * static_cast<size_t>(grid_size) + static_cast<size_t>(j);
            size_t protoIdx = map[mapIdx];
            if (protoIdx >= tilePrototypes.size())
                continue;

            float x = i * grid_spacing - grid_offset;
            float z = j * grid_spacing - grid_offset;
            float tile_size;
            switch (tilePrototypes[protoIdx].id)
            {
            case 5:
                tile_size = 0.7f;
                break;
            default:
                tile_size = 1.3f;
                break;
            }
            DrawModel(tilePrototypes[protoIdx].model, Vector3{x, 0.0f, z}, tile_size, WHITE);
        }
    }
}

std::vector<size_t> Game::GenerateMap()
{
    tilePrototypes = GetAllTiles();
    map.clear();

    if (tilePrototypes.empty())
    {
        return {};
    }

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<size_t> dist(0, tilePrototypes.size() - 1);

    const size_t totalTiles = static_cast<size_t>(grid_size) * static_cast<size_t>(grid_size);
    map.reserve(totalTiles);

    for (size_t i = 0; i < totalTiles; i++)
    {
        map.push_back(dist(rng));
    }

    return map;
}

void Game::Stop()
{
    for (Tile &tile : tilePrototypes)
    {
        tile.Unload();
    }
    tilePrototypes.clear();
    map.clear();
}