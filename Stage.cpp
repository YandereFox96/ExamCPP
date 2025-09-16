#include <DxLib.h>
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "Effect.h"

namespace
{
	const int ENEMY_COL_SIZE = 10;
	const int ENEMY_ROW_SIZE = 7;
	const int ENEMY_NUM = ENEMY_COL_SIZE * ENEMY_ROW_SIZE;
	const float ENEMY_DEFAULT_X = 100.0f;
	bool IntersectRect(const Rect& a, const Rect& b)
	{
		float lx;
		float ly;
		float w = a.width / 2.0f + b.width / 2.0f;
		float h = a.height / 2.0f + b.height / 2.0f;
		lx = a.x - b.x;
		if (lx < 0)
			lx *= -1;
		ly = a.y - b.y;
		if (ly < 0)
			ly *= -1;

		if (lx <= w && ly <= h)
			return true;
		else
			return false;
	}
}

Stage::Stage()
	:GameObject(),player_(nullptr)
{
	AddGameObject(this);
	player_ = new Player();
	enemy_ = std::vector<Enemy*>(ENEMY_NUM);
	
	int t;
	for (int i = 0;i < ENEMY_NUM;i++)
	{
		switch (ENEMY_ROW_SIZE - i / ENEMY_COL_SIZE)
		{
		case ETYPE::BOSS + 4:
			t = ETYPE::BOSS;
			break;
		case ETYPE::KNIGHT + 4:
			t = ETYPE::KNIGHT;
			break;
		case ETYPE::MID + 4:
			t = ETYPE::MID;
			break;
		default:
			t = ETYPE::ZAKO;
			break;
		}
		enemy_[i] = new Enemy(i, (ETYPE)t);

		enemy_[i]->SetPos(ENEMY_DEFAULT_X + i % ENEMY_COL_SIZE * 50.0f, 100.0f + i / ENEMY_COL_SIZE * 50.0f);
		enemy_[i]->SetMaxMoveX(WIN_WIDTH / 2);
		enemy_[i]->SetXorigin(WIN_WIDTH / 2 - ENEMY_COL_SIZE * 50.0f / 2 + (i % ENEMY_COL_SIZE * 50.0f));
	}
	hBackGround = LoadGraph("Assets/bg.png");
}

Stage::~Stage()
{
}

void Stage::Update()
{
	int lx, ly;
	std::vector<Bullet*> bullets = player_->GetAllBullets();
	for (auto& e : enemy_)
	{
		std::vector<EnemyBullet*> eBullets = e->GetEBullets();
		for (auto& b : bullets)
		{
			if (IntersectRect(e->GetRect(), b->GetRect()))
			{
				if (b->IsFired())
				{
					b->SetFired(false);
					if (e->IsAlive())
					{
						effects_.push_back(new Effect(e->GetRect().x,e->GetRect().y));
						e->SetAlive(false);
					}
				}
			}
		}
		for (int i = 0;i < eBullets.size();i++)
		{
			lx = player_->GetRect().x - eBullets[i]->GetRect().x;
			if (lx < 0)
				lx *= -1;
			ly = player_->GetRect().y - eBullets[i]->GetRect().y;
			if (ly < 0)
				ly *= -1;
			if (lx < player_->GetRect().width / 2 + eBullets[i]->GetRect().width / 2 &&
				ly < player_->GetRect().height / 2 + eBullets[i]->GetRect().height / 2)
			{
				player_->Damaged();
			}
		}
	}
}

void Stage::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawExtendGraph(0, 0, WIN_WIDTH, WIN_HEIGHT, hBackGround, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(0, 0, GetColor(0, 255, 255), "HP -> %d", player_->GetHP());
}

int Stage::GetPlayerHP()
{
	return player_->GetHP();
}
