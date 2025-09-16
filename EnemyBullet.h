#pragma once
#include "global.h"
#include "GameObject.h"

class EnemyBullet :
    public GameObject
{
public:
    EnemyBullet();
    EnemyBullet(float x, float y);
    ~EnemyBullet();
    void Update() override;
    void Draw() override;

    void SetPos(float x, float y);
    void SetFired(bool fired) { isFired_ = fired; }
    bool IsFired() const { return isFired_; }
    Rect GetRect() const { return { x_,y_,imageSize_.x,imageSize_.y }; }
protected:
private:
    int hImage_;
    float x_, y_;
    float speed_;
    //int isize_x, isize_y;
    bool isFired_;
    Point imageSize_;
};