#pragma once
#include "GameObject.h"
#include<vector>

class Player;
class Enemy;
class Effect;

class Stage :
    public GameObject
{
private:
    Player* player_;
    std::vector<Enemy*> enemy_;
    std::vector<Effect*> effects_;
    int hBackGround;
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;

    int GetPlayerHP();
};

