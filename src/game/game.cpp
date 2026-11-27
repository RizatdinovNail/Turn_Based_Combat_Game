#include <iostream>
#include <random>
#include "game.h"
#include <vector>
#include <string>
#include "concretePlayerStates.h"

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
            tilePrototypes[protoIdx].position = Vector3{x + grid_spacing, 0.0f, z + grid_spacing};
        }
    }
}

void Game::InitPlayers()
{
    const float PLAYER_POSITION = grid_spacing * grid_size / 2;
    humanPlayer = HumanPlayer();
    humanPlayer.DEFAULT_POSITION = Vector3(grid_spacing / 2, 0.0f, PLAYER_POSITION - grid_spacing / 2);
    SetUpPlayer(humanPlayer);
    humanPlayer.setState(Play::getInstance());

    aiPlayer = AIPlayer();
    aiPlayer.DEFAULT_POSITION = Vector3(grid_spacing / 2, 0.0f, -PLAYER_POSITION + grid_spacing / 2);
    SetUpPlayer(aiPlayer);
}

void Game::SetUpPlayer(Player &player)
{
    player.position = player.DEFAULT_POSITION;
    player.hp = player.DEFAULT_HP;
    player.ac = player.DEFAULT_AC;
    player.speed = player.DEFAULT_SPEED;
    player.action_points = player.player_class.DEFAULT_ACTION_POINTS;
    for (int i = 0; i < player.model.materialCount; i++)
    {
        SetMaterialTexture(&player.model.materials[i], MATERIAL_MAP_DIFFUSE, player_texture);
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
        if (isValid(humanPlayer.position.z + grid_spacing) && humanPlayer.getCurrentState() == &Play::getInstance())
        {
            humanPlayer.MoveDown(grid_spacing);
        }

        break;
    case KEY_UP:
        if (isValid(humanPlayer.position.z - grid_spacing) && humanPlayer.getCurrentState() == &Play::getInstance())
        {
            humanPlayer.MoveUp(grid_spacing);
        }

        break;
    case KEY_LEFT:
        if (isValid(humanPlayer.position.x - grid_spacing) && humanPlayer.getCurrentState() == &Play::getInstance())
        {
            humanPlayer.MoveLeft(grid_spacing);
        }

        break;
    case KEY_RIGHT:
        if (isValid(humanPlayer.position.x + grid_spacing) && humanPlayer.getCurrentState() == &Play::getInstance())
        {
            humanPlayer.MoveRight(grid_spacing);
        }
        break;
    case KEY_SPACE:
        if (humanPlayer.getCurrentState() == &Play::getInstance())
        {
            humanPlayer.setState(Pass::getInstance());
            humanPlayer.toggle();
            aiPlayer.setState(Play::getInstance());
        }
    default:
        break;
    }
}

bool Game::isValid(float position)
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
