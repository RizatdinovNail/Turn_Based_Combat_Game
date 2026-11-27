#include "game.h"
#include "concretePlayerStates.h"
#include "tiles.cpp"
#include <cmath>
#include <iostream>
#include <random>

Game::Game(int gridSize, float gridSpacing)
    : grid_size(gridSize),
      grid_spacing(gridSpacing),
      grid_offset((static_cast<float>(gridSize) * gridSpacing) * 0.5f - (gridSpacing * 0.5f)),
      min_bound(-grid_offset),
      max_bound(grid_offset)
{
    texture = LoadTexture("assets/textures/dungeon_texture.png");
    player_texture = LoadTexture("assets/textures/boardgame_bits_texture.png");

    tilePrototypes = GetAllTiles();
    for (Tile &proto : tilePrototypes)
    {
        proto.AddTexture(texture);
    }

    BuildGrid();
    InitPlayers();
}

Game::~Game()
{
    Stop();
}

void Game::Run()
{
    HandleInput();
    DrawMap();
    ShowPlayers();
}

std::vector<Tile> Game::GetAllTiles()
{
    return {
        Tile_A_Dirt(),
        Tile_B_Dirt(),
        Tile_C_Dirt(),
        Tile_D_Dirt(),
        Tile_Broken_A(),
        Tile_Broken_B(),
        Tile_Small(),
        Tile_Spikes()};
}

void Game::BuildGrid()
{
    gridCells.clear();
    if (grid_size <= 0 || tilePrototypes.empty())
        return;

    static std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<size_t> dist(0, tilePrototypes.size() - 1);

    const size_t totalTiles = static_cast<size_t>(grid_size) * static_cast<size_t>(grid_size);
    gridCells.resize(totalTiles);

    for (int i = 0; i < grid_size; ++i)
    {
        for (int j = 0; j < grid_size; ++j)
        {
            const size_t idx = static_cast<size_t>(i) * static_cast<size_t>(grid_size) + static_cast<size_t>(j);
            const size_t protoIdx = dist(rng);
            const Tile &proto = tilePrototypes[protoIdx];

            TileInstance cell;
            cell.protoIdx = protoIdx;
            cell.position = Vector3{
                static_cast<float>(i) * grid_spacing - grid_offset,
                0.0f,
                static_cast<float>(j) * grid_spacing - grid_offset};
            cell.scale = (proto.id == 5) ? 0.7f : 1.3f;

            cell.damage = (proto.id == 5) ? 10 : 0;

            gridCells[idx] = cell;
        }
    }
}

void Game::DrawMap() const
{
    for (const TileInstance &cell : gridCells)
    {
        const Tile &proto = tilePrototypes[cell.protoIdx];
        DrawModel(proto.model, cell.position, cell.scale, WHITE);
    }
}

void Game::InitPlayers()
{
    humanPlayer = HumanPlayer();
    humanPlayer.DEFAULT_POSITION = Vector3{grid_spacing * 0.5f, 0.0f, max_bound};
    SetUpPlayer(humanPlayer);
    humanPlayer.setState(Play::getInstance());

    aiPlayer = AIPlayer();
    aiPlayer.DEFAULT_POSITION = Vector3{grid_spacing * 0.5f, 0.0f, min_bound};
    SetUpPlayer(aiPlayer);
}

void Game::SetUpPlayer(Player &player)
{
    player.position = player.DEFAULT_POSITION;
    player.hp = player.DEFAULT_HP;
    player.ac = player.DEFAULT_AC;
    player.speed = player.DEFAULT_SPEED;
    player.action_points = player.player_class.DEFAULT_ACTION_POINTS;

    for (int i = 0; i < player.model.materialCount; ++i)
    {
        SetMaterialTexture(&player.model.materials[i], MATERIAL_MAP_DIFFUSE, player_texture);
    }
}

void Game::ShowPlayers() const
{
    DrawModel(humanPlayer.model, humanPlayer.position, 3.0f, WHITE);
    DrawModel(aiPlayer.model, aiPlayer.position, 3.0f, WHITE);
}

void Game::HandleInput()
{
    if (humanPlayer.getCurrentState() != &Play::getInstance())
        return;

    switch (GetKeyPressed())
    {
    case KEY_DOWN:
        TryMoveHuman(0.0f, grid_spacing);
        break;
    case KEY_UP:
        TryMoveHuman(0.0f, -grid_spacing);
        break;
    case KEY_LEFT:
        TryMoveHuman(-grid_spacing, 0.0f);
        break;
    case KEY_RIGHT:
        TryMoveHuman(grid_spacing, 0.0f);
        break;
    case KEY_SPACE:
        humanPlayer.setState(Pass::getInstance());
        humanPlayer.toggle();
        aiPlayer.setState(Play::getInstance());
        break;
    default:
        break;
    }
}

void Game::TryMoveHuman(float dx, float dz)
{
    const float nextX = humanPlayer.position.x + dx;
    const float nextZ = humanPlayer.position.z + dz;

    if (!IsWithinBounds(nextX) || !IsWithinBounds(nextZ))
        return;

    if (dx > 0.0f)
        humanPlayer.MoveRight(grid_spacing);
    else if (dx < 0.0f)
        humanPlayer.MoveLeft(grid_spacing);
    else if (dz > 0.0f)
        humanPlayer.MoveDown(grid_spacing);
    else if (dz < 0.0f)
        humanPlayer.MoveUp(grid_spacing);

    size_t cellIdx = 0;
    if (TryGetCellIndex(humanPlayer.position, cellIdx))
    {
        const TileInstance &steppedCell = gridCells[cellIdx];
        const Tile &proto = tilePrototypes[steppedCell.protoIdx];

        if (steppedCell.damage > 0)
        {
            humanPlayer.ReciveDamage(steppedCell.damage);
        }
    }
}

bool Game::IsWithinBounds(float coord) const
{
    const float eps = grid_spacing * 0.01f;
    return coord >= (min_bound - eps) && coord <= (max_bound + eps);
}

bool Game::TryGetCellIndex(Vector3 worldPos, size_t &outIdx) const
{
    const int i = static_cast<int>(std::round((worldPos.x + grid_offset) / grid_spacing));
    const int j = static_cast<int>(std::round((worldPos.z + grid_offset) / grid_spacing));

    if (i < 0 || i >= grid_size || j < 0 || j >= grid_size)
        return false;

    outIdx = static_cast<size_t>(i) * static_cast<size_t>(grid_size) + static_cast<size_t>(j);
    return true;
}

void Game::Stop()
{
    if (isCleanedUp)
        return;
    isCleanedUp = true;

    for (Tile &tile : tilePrototypes)
    {
        tile.Unload();
    }
    tilePrototypes.clear();
    gridCells.clear();

    UnloadModel(humanPlayer.model);
    UnloadModel(aiPlayer.model);
    UnloadTexture(texture);
    UnloadTexture(player_texture);
}