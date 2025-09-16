#pragma once
#include "GameObject.h"
#include "global.h"

class Bullet :
    public GameObject
{
public:
    Bullet();
    Bullet(float x, float y);
    ~Bullet();
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
    int isize_x, isize_y;
    bool isFired_;
    Point imageSize_;
};

