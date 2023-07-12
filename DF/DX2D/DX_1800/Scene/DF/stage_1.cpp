#include "framework.h"
#include "stage_1.h"

#include "../../Object/Obj/Monster/Monsters/Goblin.h"
#include "../../Object/Obj/BackGround/BattleField.h"
#include "../../Object/Obj/Player/Gunner_p.h"

#include "InvenScene.h"

stage_1::stage_1()
{
	_goblin = make_shared<class Goblin>();
	_bg = make_shared<class BattleField>();
}

stage_1::~stage_1()
{
}

void stage_1::Update()
{
	_bg->Update();

	IsCollision();
	Attack();
	
	if (_goblin->GetHp() > 0)
	{
		_goblin->Update();
	}
	else
	{
		_st1_OnAir = false;
		InvenScene::Instance()._inven_OnAir = true;
	}

	Gunner_p::Instance().Input();
	Gunner_p::Instance().Update();

}

void stage_1::Render()
{
	_bg->Render();

	if (_goblin->GetHp() > 0)
	{
		_goblin->Render();
	}

	Gunner_p::Instance().Render();
}

void stage_1::PostRender()
{
	Gunner_p::Instance().PostRender();
	_goblin->PostRender();
}

void stage_1::Attack()
{
	if (_goblin->GetHp() > 0)
	{
		for (auto bullet : Gunner_p::Instance().GetBullets())
		{
			if (bullet->_isActive == false)
				continue;

			if (bullet->GetCollider()->IsCollision(_goblin->GetCollider()))
			{
				bullet->_isActive = false;
				_goblin->Mhp();
			}
		}
	}
}

void stage_1::IsCollision()
{
	if (_bg->GetLeftCollider()->IsCollision(Gunner_p::Instance().GetCollider()))
	{
		Gunner_p::Instance().CanGoLeft();
		_bg->GetLeftCollider()->SetColorRed();
	}
	else
	{
		Gunner_p::Instance().CantGoLeft();
		_bg->GetLeftCollider()->SetColorGreen();

	}

	if (_bg->GetRightCollider()->IsCollision(Gunner_p::Instance().GetCollider()))
	{
		Gunner_p::Instance().CanGoRight();
		_bg->GetRightCollider()->SetColorRed();
	}
	else
	{
		Gunner_p::Instance().CantGoRight();
		_bg->GetRightCollider()->SetColorGreen();

	}
	
	_bg->GetBottomCollider()->Block(Gunner_p::Instance()._col);
}

