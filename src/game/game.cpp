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
    texture = LoadTexture("assets/textures/dungeon_texture.png");
    player_texture = LoadTexture("assets/textures/boardgame_bits_texture.png");
    InitPlayers();
}

void Game::Run()
{
    InitMap();
    ShowPlayers();
    HandleInput();
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
            tilePrototypes[protoIdx].AddTexture(texture);
            DrawModel(tilePrototypes[protoIdx].model, Vector3{x, 0.0f, z}, tile_size, WHITE);
        }
    }
}

void Game::InitPlayers()
{
    const float PLAYER_POSITION = grid_spacing * grid_size / 2;

    humanPlayer = HumanPlayer();
    humanPlayer.position = Vector3{grid_spacing / 2, 0.0f, PLAYER_POSITION - grid_spacing / 2};

    for (int i = 0; i < humanPlayer.model.materialCount; i++)
    {
        SetMaterialTexture(&humanPlayer.model.materials[i], MATERIAL_MAP_DIFFUSE, player_texture);
    }

    aiPlayer = AIPlayer();
    aiPlayer.position = Vector3(grid_spacing / 2, 0.0f, -PLAYER_POSITION + grid_spacing / 2);
    for (int i = 0; i < aiPlayer.model.materialCount; i++)
    {
        SetMaterialTexture(&aiPlayer.model.materials[i], MATERIAL_MAP_DIFFUSE, player_texture);
    }
}

void Game::ShowPlayers()
{
    DrawModel(humanPlayer.model, humanPlayer.position, 3.0f, WHITE);
    DrawModel(aiPlayer.model, aiPlayer.position, 3.0f, WHITE);
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

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    switch (keyPressed)
    {
    case KEY_DOWN:
        if (isInsideGrid(humanPlayer.position.z + grid_spacing))
            humanPlayer.MoveDown(grid_spacing);
        break;
    case KEY_UP:
        if (isInsideGrid(humanPlayer.position.z - grid_spacing))
            humanPlayer.MoveUp(grid_spacing);
        break;
    case KEY_LEFT:
        if (isInsideGrid(humanPlayer.position.x - grid_spacing))
            humanPlayer.MoveLeft(grid_spacing);
        break;
    case KEY_RIGHT:
        if (isInsideGrid(humanPlayer.position.x + grid_spacing))
            humanPlayer.MoveRight(grid_spacing);
        break;
    default:
        break;
    }
}

bool Game::isInsideGrid(float position)
{
    if (position >= -((grid_spacing * grid_size / 2) - grid_spacing / 2) &&
        position <= ((grid_spacing * grid_size / 2) - grid_spacing / 2))
    {
        return true;
    }

    return false;
}

void Game::Stop()
{
    for (Tile &tile : tilePrototypes)
    {
        tile.Unload();
    }
    UnloadModel(humanPlayer.model);
    UnloadModel(aiPlayer.model);
    tilePrototypes.clear();
    UnloadTexture(texture);
    UnloadTexture(player_texture);
    map.clear();
}
