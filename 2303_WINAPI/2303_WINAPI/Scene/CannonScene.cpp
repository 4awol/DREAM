#include "framework.h"
#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>();
	_cannon2 = make_shared<Cannon>();
	_cannon2->_isControll = false;
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	for (auto bullet : _cannon->GetBullets())
	{
		if(bullet->IsActive() == false)
			continue;

		if (bullet->AttackCannon(_cannon2))
		{
			_cannon2->TakeDamage();
		}
	}

	_cannon->Update();
	_cannon2->Update();
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_cannon2->Render(hdc);
}
