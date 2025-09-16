#pragma once
#include "GameObject.h"
#include "global.h"

class Bullet;

class Player :
    public GameObject
{
public:
    Player();
    ~Player();
    void Update() override;
    void Draw() override;
    void Shoot();
    Rect GetRect() const { return { x_,y_,imageSize_.x,imageSize_.y }; }
    int GetHP() { return hp_; }
    std::vector<Bullet*> GetAllBullets() const { return bullets_; }

    void Damaged();
protected:
private:
    int hImage_;
    float x_, y_;
    float speed_;
    Point imageSize_;
    std::vector<Bullet*> bullets_;
    Bullet* GetActiveBullet();

    int hp_;
    float damageDelay_;
    const float DAMAGE_DELAY = 1.5;
};

