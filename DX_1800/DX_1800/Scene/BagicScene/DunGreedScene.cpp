#include "framework.h"
#include "DunGreedScene.h"

#include "../../Object/Obj/DunGreed/DunPlayer.h"
#include "../../Object/Obj/DunGreed/DunBullet.h"
#include "../../Object/Obj/DunGreed/DunMonster.h"

DunGreedScene::DunGreedScene()
{
	_player = make_shared<DunPlayer>();
	_player->SetPosition(CENTER);

	_monster= make_shared<DunMonster>();
	_monster->SetPosition(CENTER + Vector2(300,300));
}

DunGreedScene::~DunGreedScene()
{
}

void DunGreedScene::Update()
{
	_player->Update();
	_monster->Update();

	if (_monster->IsActive() == true)
	{
		for (auto bullet : _player->GetBullets())
		{
			if (bullet->_isActive == false)
				continue;

			if (bullet->GetCollider()->IsCollision(_monster->GetCollider()))
			{
				_monster->TakeDamage(1);
				bullet->_isActive = false;
			}
		}
	}
}

void DunGreedScene::Render()
{
	_player->Render();
	_monster->Render();
}

void DunGreedScene::PostRender()
{
	ImGui::Text("Monster HP : %d", _monster->_hp);
}
