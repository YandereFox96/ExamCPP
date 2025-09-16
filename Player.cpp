#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Bullet.h"
#include <vector>

namespace
{
	const float PLAYER_INIT_SPEED = WIN_WIDTH / 5;
	const int PLAYER_IMAGE_WIDTH = 48;
	const int PLAYER_IMAGE_HEIGHT = 48;

	const float PLAYER_INIT_X = WIN_WIDTH / 2;
	const float PLAYER_INIT_Y = WIN_HEIGHT - PLAYER_IMAGE_HEIGHT / 2;

	const int BULLET_IMAGE_MARGIN = 1;
	const float BULLET_INTERVAL = 0.2f;
	const int PLAYER_BULLET_NUM = 5;
}

Player::Player()
	:GameObject(), hImage_(-1), x_(0), y_(0), speed_(0)
	, imageSize_({ PLAYER_IMAGE_WIDTH,PLAYER_IMAGE_HEIGHT })
	, hp_(3), damageDelay_(DAMAGE_DELAY)
{
	hImage_ = LoadGraph("Assets\\tiny_ship5.png");
	if (hImage_ == -1)
	{
		//
	}
	x_ = PLAYER_INIT_X;
	y_ = PLAYER_INIT_Y;
	speed_ = PLAYER_INIT_SPEED;
	for (int i = 0;i < PLAYER_BULLET_NUM;i++)
	{
		bullets_.push_back(new Bullet());
	}

	AddGameObject(this);

	playerHp = hp_;
}

Player::~Player()
{
}

void Player::Update()
{
	if (Input::IsKeepKeyDown(KEY_INPUT_LEFT))
	{
		x_ -= speed_ * GetDeltaTime();
	}
	if (Input::IsKeepKeyDown(KEY_INPUT_RIGHT))
	{
		x_ += speed_ * GetDeltaTime();
	}

	if (x_ < PLAYER_IMAGE_WIDTH / 2)
	{
		x_ = PLAYER_IMAGE_WIDTH / 2;
	}
	else if (x_ > WIN_WIDTH - PLAYER_IMAGE_WIDTH / 2)
	{
		x_ = WIN_WIDTH - PLAYER_IMAGE_WIDTH / 2;
	}

	static float bulletTimer = 0.0f;
	if (bulletTimer > 0.0f)
	{
		bulletTimer -= GetDeltaTime();
	}

	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		if (bulletTimer <= 0.0f)
		{
			//new Bullet(x_ - BULLET_IMAGE_MARGIN, y_);
			Shoot();
			bulletTimer = BULLET_INTERVAL;
		}
	}

	if (damageDelay_ > 0.0)
		damageDelay_ -= gDeltaTime;

	playerHp = hp_;
}

void Player::Draw()
{
	DrawExtendGraphF(x_ - PLAYER_IMAGE_WIDTH / 2, y_ - PLAYER_IMAGE_HEIGHT / 2, x_  + PLAYER_IMAGE_WIDTH / 2, y_ + PLAYER_IMAGE_HEIGHT / 2, hImage_, TRUE);
}

void Player::Shoot()
{
	//for (auto& itr : bullets_)
	//{
	//	if (itr->IsFired() == false)
	//	{
	//		itr->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);
	//		itr->SetFired(true);
	//		break;
	//	}
	//}

	Bullet* bit = GetActiveBullet();
	if (bit != nullptr)
	{
		bit->SetPos(x_ + BULLET_IMAGE_MARGIN, y_);
		bit->SetFired(true);
	}
}

void Player::Damaged()
{
	if (damageDelay_ <= 0.0)
	{
		hp_-=1;
		damageDelay_ += DAMAGE_DELAY;
	}
	if (hp_ <= 0)
	{
		isAlive_ = false;
	}
}

Bullet* Player::GetActiveBullet()
{
	for (auto& itr : bullets_)
	{
		if (!itr->IsFired())
		{
			return itr;
		}
	}

	return nullptr;
}
