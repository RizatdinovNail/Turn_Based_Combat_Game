#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer()
    {
        id = 1;
        model = LoadModel("assets/models/players/pawn_A_blue.gltf");
        position;
    };
};

class AIPlayer : public Player
{
public:
    AIPlayer()
    {
        id = 2;
        model = LoadModel("assets/models/players/pawn_A_red.gltf");
        position;
    }
};