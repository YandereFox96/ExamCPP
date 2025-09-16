#pragma once
#include <string>

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

extern float gDeltaTime;

namespace
{
	int playerHp;
}

enum Scene
{
	TITLE = 0,
	PLAY,
	RESULT
};

inline float GetDeltaTime()
{
	return gDeltaTime;
}

struct Point
{
	float x;
	float y;
};

struct Rect
{
	float x;
	float y;
	float width;
	float height;
	inline Point GetCenter() const
	{
		return { x + width / 2,y + height / 2 };
	}
};

struct TITLE_SCENE
{
	const std::string TEXT_ = "-THE GALAX!-";
	const int COLOR_ = 0xff0000;
	const int TEXT_SIZE_ = 50;
	const int TEXT_MARGIN_X_ = TEXT_SIZE_ * 3;
	const int TEXT_MARGIN_Y_ = 200;
	const int TEXT_X_ = WIN_WIDTH / 2 - TEXT_MARGIN_X_;
	const int TEXT_Y_ = WIN_HEIGHT / 2 - TEXT_MARGIN_Y_;
};

struct RESULT_SCENE
{
	const std::string TEXT_ = "-GAME OVER!-";
	const int COLOR_ = 0xff0000;
	const int TEXT_SIZE_ = 50;
	const int TEXT_MARGIN_X_ = TEXT_SIZE_ * 3;
	const int TEXT_MARGIN_Y_ = 200;
	const int TEXT_X_ = WIN_WIDTH / 2 - TEXT_MARGIN_X_;
	const int TEXT_Y_ = WIN_HEIGHT / 2 - TEXT_MARGIN_Y_;
};