#include <raylib.h>
#include <iostream>
#include <random>
#include "game.h"

Game::Game(int gridSize, float gridSpacing)
{
    this->grid_size = gridSize;
    this->grid_spacing = gridSpacing;
    this->grid_offset = gridSize / 2 * gridSpacing - gridSpacing / 2;
    this->texture = LoadTexture("asssets/textures/dungeon_texture.png");
    tiles.Load();
    allTiles = tiles.All();
    map = CreateMap();
}

void Game::Run()
{
    InitMap();
}

void Game::InitMap()
{
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            float x = i * grid_spacing - grid_offset;
            float z = j * grid_spacing - grid_offset;
            DrawModel(map[i * j], Vector3{x, 0.0f, z}, 1.3f, WHITE);
        }
    }
}

std::vector<Model> Game::CreateMap()
{
    for (int i = 0; i < grid_size * grid_size; i++)
    {
        map.push_back(GetRandomTile());
    }

    return map;
}

Model Game::GetRandomTile()
{
    int randomIndex = rand() % 3;
    return allTiles[randomIndex];
}

void Game::Stop()
{
    tiles.Unload();
    UnloadTexture(texture);
}