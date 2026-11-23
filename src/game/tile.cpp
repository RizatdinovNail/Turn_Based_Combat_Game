#include "tile.h"
#include <iostream>

Tile::Tile()
{
}

void Tile::AddTexture(Texture texture)
{
    for (int i = 0; i < model.materialCount; i++)
    {
        SetMaterialTexture(&model.materials[i], MATERIAL_MAP_DIFFUSE, texture);
    }
}

void Tile::Unload()
{
    if (model.meshCount > 0 && model.meshes != nullptr)
    {
        UnloadModel(model);
        model = {};
    }
}