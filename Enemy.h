#pragma once
#include "GameObject.h"
#include "global.h"

class EnemyBullet;

enum ETYPE
{
    ZAKO, MID, KNIGHT, BOSS, MAX_ETYPE
};

class Enemy :
    public GameObject
{
public:
    Enemy(int id, ETYPE type);
    Enemy();
    ~Enemy();
    void Update() override;
    void Draw() override;
    void SetPos(float x, float y) { x_ = x;y_ = y; }
    //void SetID(int id) { ID_ = id; }
    Rect GetRect() const { return { x_,y_,imageSize_.x,imageSize_.y }; }
    std::vector<EnemyBullet*> GetAllBullets() const { return eBullets_; }

    void SetMaxMoveX(float xmax) { xMoveMax_ = xmax; }
    void SetXorigin(float x) { xorigin_ = x; }

    std::vector<EnemyBullet*> GetEBullets() { return eBullets_; }
private:
    int hImage_;
    float x_, y_;
    float speed_;
    float moveTime_;
    float xMoveMax_;
    float xorigin_;
    int ID_;
    ETYPE type_;
    Point imageSize_;

    std::vector<EnemyBullet*> eBullets_;
    EnemyBullet* GetActiveBullet();
};

