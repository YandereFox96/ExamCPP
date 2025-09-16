#include "Effect.h"
#include "DxLib.h"

namespace
{
	const float ANIM_DELAY = 0.05;
	const int ANIM_MAX = 9;

	const int ANIM_RECT_WIDTH = 48;
	const int ANIM_RECT_HEIGHT = 48;
}

Effect::Effect()
	:GameObject(), rect_({ 0,0,0,0 })
{
	hEffect = LoadGraph("Assets/explosion.png");
	cAnimT = ANIM_DELAY;
	anim = 0;
	draw_.x = rect_.x - rect_.width / 2;
	rect_.y = rect_.y - rect_.height / 2;

	AddGameObject(this);
}
Effect::Effect(int x, int y)
	:GameObject(), rect_( x, y, ANIM_RECT_WIDTH,ANIM_RECT_HEIGHT )
{
	hEffect = LoadGraph("Assets/explosion.png");
	cAnimT = ANIM_DELAY;
	anim = 0;
	draw_.x = rect_.x - rect_.width / 2;
	draw_.y = rect_.y - rect_.height / 2;

	AddGameObject(this);
}

Effect::~Effect()
{
	if (hEffect != -1)
	{
		DeleteGraph(hEffect);
	}
}

void Effect::Update()
{
	cAnimT -= GetDeltaTime();
	if (cAnimT <= 0.0f)
	{
		cAnimT += ANIM_DELAY;
		anim++;
	}
	rect_.x = anim % 3 * rect_.width;
	rect_.y = anim / 3 * rect_.height;

	if (anim >= ANIM_MAX)
	{
		SetAlive(false);
	}

}

void Effect::Draw()
{
	DrawRectGraph(draw_.x, draw_.y, rect_.x, rect_.y, rect_.width, rect_.height, hEffect, TRUE);
}
