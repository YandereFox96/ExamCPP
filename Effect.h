#pragma once
#include "GameObject.h"
#include "global.h"

class Effect :
    public GameObject
{
public:
    Effect();
    Effect(int x, int y);
    ~Effect();
    void Update() override;
    void Draw() override;
protected:
private:
    int hEffect;
    float cAnimT;
    int anim;
    Rect rect_;
    Point draw_;
};

