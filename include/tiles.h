#pragma once
#include <raylib.h>
#include <vector>

struct Tiles
{
    Model floor_a{};
    Model floor_b{};
    Model floor_c{};

    void Load()
    {
        floor_a = LoadModel("assets/models/floor_dirt_small_A.gltf");
        floor_b = LoadModel("assets/models/floor_dirt_small_B.gltf");
        floor_c = LoadModel("assets/models/floor_dirt_small_C.gltf");
    }

    void Unload() const
    {
        UnloadModel(floor_a);
        UnloadModel(floor_b);
        UnloadModel(floor_c);
    }

    std::vector<Model> All() const
    {
        return {floor_a, floor_b, floor_c};
    }
};