#include "EnemyBullet.h"
#include "DxLib.h"

namespace
{
	const int ENEMY_BULLET_WIDTH = 11;
	const int ENEMY_BULLET_HEIGHT = 21;
	const int ENEMY_BULLET_INIT_SPEED = 500.0f;
}

EnemyBullet::EnemyBullet()
	:GameObject(), hImage_(-1), x_(0), y_(0),
	speed_(ENEMY_BULLET_INIT_SPEED),
	isFired_(false),
	imageSize_({ ENEMY_BULLET_WIDTH }, { ENEMY_BULLET_HEIGHT })
{
	isAlive_ = true;
	hImage_ = LoadGraph("Assets/ebeams.png");
	AddGameObject(this);
}

EnemyBullet::EnemyBullet(float x, float y)
	:GameObject(), hImage_(-1), x_(x), y_(y),
	speed_(ENEMY_BULLET_INIT_SPEED),
	isFired_(false),
	imageSize_({ ENEMY_BULLET_WIDTH }, { ENEMY_BULLET_HEIGHT })
{
	isAlive_ = true;
	hImage_ = LoadGraph("Assets/ebeams.png");
	AddGameObject(this);

}

EnemyBullet::~EnemyBullet()
{
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_);
	}
	hImage_ = -1;
}

void EnemyBullet::Update()
{
	float dt = GetDeltaTime();
	y_ += speed_ * dt;
	if (y_ > WIN_HEIGHT && isFired_)
	{
		isFired_ = false;
		SetAlive(false);
		SetPos(x_, y_ - 1000);
	}
}

void EnemyBullet::Draw()
{
	if (isFired_)
	{
		DrawExtendGraph(x_, y_, x_ + imageSize_.x, y_ + imageSize_.y, hImage_, TRUE);
	}
}

void EnemyBullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}