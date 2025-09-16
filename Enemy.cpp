#include "Enemy.h"
#include "DxLib.h"
#include <string>
#include "EnemyBullet.h"
#include <vector>

namespace
{
	const float ENEMY_INIT_SPEED = 100.0f;
	const int ENEMY_IMAGE_WIDTH = 48;
	const int ENEMY_IMAGE_HEIGHT = 48;

	const int ENEMY_INIT_X = WIN_WIDTH / 2;
	const int ENEMY_INIT_Y = 50;

	const int ENEMY_BULLET_NUM = 3;
}

Enemy::Enemy()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), ID_(0), type_()
	, imageSize_({ ENEMY_IMAGE_WIDTH,ENEMY_IMAGE_HEIGHT })
{
	std::string imagePath[MAX_ETYPE] =
	{
		"Assets/tiny_ship10.png",
		"Assets/tiny_ship18.png",
		"Assets/tiny_ship16.png",
		"Assets/tiny_ship9.png"
	};

	hImage_ = LoadGraph(imagePath[type_].c_str());
	if (hImage_ == -1)
	{
		//
	}
	x_ = ENEMY_INIT_X;
	y_ = ENEMY_INIT_Y;
	speed_ = ENEMY_INIT_SPEED;
	eBullets_.push_back(new EnemyBullet(x_, y_));

	AddGameObject(this);
}
Enemy::Enemy(int id, ETYPE type)
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0), ID_(id), type_(type)
	,imageSize_({ENEMY_IMAGE_WIDTH,ENEMY_IMAGE_HEIGHT})
{
	std::string imagePath[MAX_ETYPE] =
	{
		"Assets/tiny_ship10.png",
		"Assets/tiny_ship18.png",
		"Assets/tiny_ship16.png",
		"Assets/tiny_ship9.png"
	};

	moveTime_ = 0.0f;

	hImage_ = LoadGraph(imagePath[type_].c_str());
	if (hImage_ == -1)
	{
		//
	}
	x_ = ENEMY_INIT_X;
	y_ = ENEMY_INIT_Y;
	speed_ = ENEMY_INIT_SPEED;
	eBullets_.push_back(new EnemyBullet(x_, y_));

	AddGameObject(this);
}

Enemy::~Enemy()
{
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_);
	}
}

void Enemy::Update()
{
	static float bulletTimer = 5.0f + (float)(GetRand(100) / 10.0f);
	float period = 10.0f;
	float omega = 2.0f * DX_PI / period;
	moveTime_ += GetDeltaTime();
	x_ = xorigin_ + xMoveMax_ / 2.0 * sinf(omega * moveTime_);
	y_ = y_;

	if (bulletTimer < 0)
	{
		EnemyBullet* bit = GetActiveBullet();
		if (bit != nullptr)
		{
			bit->SetPos(x_, y_);
			bit->SetFired(true);
		}
		bulletTimer = 3.0f + (float)(GetRand(70) / 10.0f);
	}

	bulletTimer -= GetDeltaTime();
	
}

void Enemy::Draw()
{
	DrawExtendGraphF(x_ - ENEMY_IMAGE_WIDTH / 2, y_ - ENEMY_IMAGE_HEIGHT / 2, x_ + ENEMY_IMAGE_WIDTH / 2, y_ + ENEMY_IMAGE_HEIGHT / 2, hImage_, TRUE);
}

EnemyBullet* Enemy::GetActiveBullet()
{
	for (auto& itr : eBullets_)
	{
		if (!itr->IsFired())
		{
			return itr;
		}
	}

	return nullptr;
}