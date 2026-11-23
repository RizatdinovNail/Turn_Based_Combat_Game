#include "tile.h"

Tile::Tile()
{
}

void Tile::Unload()
{
    if (model.meshCount > 0 && model.meshes != nullptr)
    {
        UnloadModel(model);
        model = {};
    }
}