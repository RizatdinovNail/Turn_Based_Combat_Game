#include "tile.h"

class Tile_A_Dirt : public Tile
{
public:
    Tile_A_Dirt()
    {
        id = 1;
        model = LoadModel("assets/models/floor_dirt_small_A.gltf");
        damage = 0;
    }
};

class Tile_B_Dirt : public Tile
{
public:
    Tile_B_Dirt()
    {
        id = 2;
        model = LoadModel("assets/models/floor_dirt_small_B.gltf");
        damage = 0;
    }
};

class Tile_C_Dirt : public Tile
{
public:
    Tile_C_Dirt()
    {
        id = 3;
        model = LoadModel("assets/models/floor_dirt_small_C.gltf");
        damage = 0;
    }
};

class Tile_D_Dirt : public Tile
{
public:
    Tile_D_Dirt()
    {
        id = 4;
        model = LoadModel("assets/models/floor_dirt_small_D.gltf");
        damage = 0;
    }
};

class Tile_Spikes : public Tile
{
public:
    Tile_Spikes()
    {
        id = 5;
        model = LoadModel("assets/models/floor_tile_big_spikes.gltf");
        damage = 5;
    }
};

class Tile_Broken_A : public Tile
{
public:
    Tile_Broken_A()
    {
        id = 6;
        model = LoadModel("assets/models/floor_tile_small_broken_A.gltf");
        damage = 0;
    }
};

class Tile_Broken_B : public Tile
{
public:
    Tile_Broken_B()
    {
        id = 7;
        model = LoadModel("assets/models/floor_tile_small_broken_B.gltf");
        damage = 0;
    }
};

class Tile_Small : public Tile
{
public:
    Tile_Small()
    {
        id = 8;
        model = LoadModel("assets/models/floor_tile_small.gltf");
        damage = 0;
    }
};