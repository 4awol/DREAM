#include "framework.h"
#include "BattleField.h"

BattleField::BattleField()
{
	_transformBottom = make_shared<Transform>();
	_colBottom = make_shared<RectCollider>(Vector2(2000,500));
	_colBottom->GetTransform()->AddVector2(Vector2(0, -500));
	_colBottom->GetTransform()->SetParent(_transformBottom);

	_transformRight = make_shared<Transform>();
	_colRight = make_shared<RectCollider>(Vector2(500, 2000));
	_colRight->GetTransform()->AddVector2(Vector2(1190, 0));
	_colRight->GetTransform()->SetParent(_transformRight);

	_transformLeft = make_shared<Transform>();
	_colLeft = make_shared<RectCollider>(Vector2(100, 2000)); 
	_transformLeft->AddVector2(Vector2(-1000, 0));
	_colLeft->GetTransform()->SetParent(_transformLeft);

}

BattleField::~BattleField()
{
}

void BattleField::Update()
{

	_colBottom->GetTransform()->SetPosition(Vector2(0, -500));

	_transformBottom->Update();
	_colBottom->Update();

	_transformRight->Update();
	_colRight->Update();

	_transformLeft->Update();
	_colLeft->Update();
}

void BattleField::Render()
{
	_transformBottom->SetWorldBuffer(0);
	_colBottom->Render();

	_transformLeft->SetWorldBuffer(0);
	_colLeft->Render();

	_transformRight->SetWorldBuffer(0);
	_colRight->Render();
}


