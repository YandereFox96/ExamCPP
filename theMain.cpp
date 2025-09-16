#include "DxLib.h"
#include "global.h"
#include "Input.h"
#include <vector>
#include "Stage.h"
#include "Input.h"

namespace
{
	const int BGCOLOR[3] = { 0,0,0 };
	int crrTime;
	int prevTime;
}

std::vector<GameObject*> gameObjects;
std::vector<GameObject*> newObjects;

float gDeltaTime = 0.0f;

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(BGCOLOR[0], BGCOLOR[1], BGCOLOR[2]);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}



int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Scene scene = TITLE;
	TITLE_SCENE title_;
	RESULT_SCENE result_;

	DxInit();
	prevTime = GetNowCount();
	crrTime = GetNowCount();

	Stage* stage = nullptr;

	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();

		crrTime = GetNowCount();
		float deltaTime = (crrTime - prevTime) / 1000.0f;
		gDeltaTime = deltaTime;

		switch (scene)
		{
		case TITLE:
			SetFontSize(title_.TEXT_SIZE_);
			DrawFormatString(title_.TEXT_X_, title_.TEXT_Y_, title_.COLOR_, title_.TEXT_.c_str());
			SetFontSize(20);
			if (Input::IsKeyDown(KEY_INPUT_RETURN))
			{
				stage = new Stage();
				scene = PLAY;
				continue;
			}
			break;
		case PLAY:
			//ここにやりたい処理を書く
			if (newObjects.size() > 0)
			{
				for (auto& obj : newObjects)
				{
					gameObjects.push_back(obj);
				}
				newObjects.clear();
			}
			for (auto& obj : gameObjects)
			{
				obj->Update();
			}
			for (auto& obj : gameObjects)
			{
				obj->Draw();
			}

			for (auto it = gameObjects.begin(); it != gameObjects.end();)
			{
				if (!(*it)->IsAlive())
				{
					delete* it;
					it = gameObjects.erase(it);
				}
				else
				{
					++it;
				}
			}

			if (stage->GetPlayerHP() <= 0)
				scene = RESULT;
			break;
		case RESULT:
			if (Input::IsKeyDown(KEY_INPUT_RETURN))
			{
				delete stage;
				scene = TITLE;
				continue;
			}
			SetFontSize(result_.TEXT_SIZE_);
			DrawFormatString(result_.TEXT_X_, result_.TEXT_Y_, result_.COLOR_, result_.TEXT_.c_str());
			SetFontSize(20);
			break;
		}
	
		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime;

		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	return 0;
}