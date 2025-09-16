#include "global.h"
#include "Bullet.h"
#include "DxLib.h"
#include <string>

namespace
{
	const int BULLET_IMAGE_WIDTH = 10;
	const int BULLET_IMAGE_HEIGHT = 33;
	const float BULLET_INIT_SPEED = 400.0f;
	const std::string BULLET_IMAGE_PATH = "Assets/laserBlue03.png";
	//const char* BULLET_IMAGE_PATH_CSTR = "Assets/laserBlue03.png";
}

Bullet::Bullet()
	:GameObject(), hImage_(-1), 
	x_(0), y_(0), speed_(0),isFired_(false),
	 isize_x(0), isize_y(0)
	, imageSize_({ BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT })
{

	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;

	isize_x = BULLET_IMAGE_WIDTH;
	isize_y = BULLET_IMAGE_HEIGHT;

	isAlive_ = true;
	AddGameObject(this);

}

Bullet::Bullet(float x, float y)
	:GameObject(), hImage_(-1),
	x_(x), y_(y), speed_(0),isFired_(false),
	isize_x(0), isize_y(0)
	, imageSize_({ BULLET_IMAGE_WIDTH,BULLET_IMAGE_HEIGHT })
{

	hImage_ = LoadGraph(BULLET_IMAGE_PATH.c_str());
	speed_ = BULLET_INIT_SPEED;

	isize_x = BULLET_IMAGE_WIDTH;
	isize_y = BULLET_IMAGE_HEIGHT;

	isAlive_ = true;
	AddGameObject(this);
}

Bullet::~Bullet()
{
	if (hImage_ != -1)
	{
		DeleteGraph(hImage_);
	}
	hImage_ = -1;
}

void Bullet::Update()
{
	float dt = GetDeltaTime();
	y_ -= speed_ * dt;
	if (y_  < 0)
	{
		isFired_ = false;
	}

	/*if (IsAlive())
	{
		SetFired(true);
	}*/
}

void Bullet::Draw()
{
	if (isFired_)
	{
		DrawExtendGraphF(x_ - isize_x / 2, y_ - isize_y / 2, x_ + isize_x / 2, y_ + isize_y / 2, hImage_, TRUE);
	}
}

void Bullet::SetPos(float x, float y)
{
	x_ = x;
	y_ = y;
}
