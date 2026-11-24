#include "player.h"
#include "classes.cpp"

class HumanPlayer : public Player
{
public:
    HumanPlayer()
    {
        id = 1;
        model = LoadModel("assets/models/players/pawn_A_blue.gltf");
        DEFAULT_POSITION;
        DEFAULT_HP = 20;
        DEFAULT_AC = 12;
        DEFAULT_SPEED = 30;

        hp = DEFAULT_HP;
        ac = DEFAULT_AC;
        speed = DEFAULT_SPEED;
        position = DEFAULT_POSITION;
        player_class = Barbarian();
    };
};

class AIPlayer : public Player
{
public:
    AIPlayer()
    {
        id = 2;
        model = LoadModel("assets/models/players/pawn_A_red.gltf");
        DEFAULT_POSITION;
        DEFAULT_HP = 20;
        DEFAULT_AC = 12;
        DEFAULT_SPEED = 30;

        hp = DEFAULT_HP;
        ac = DEFAULT_AC;
        speed = DEFAULT_SPEED;
        position = DEFAULT_POSITION;
        player_class = Fighter();
    }
};