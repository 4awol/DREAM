#include "framework.h"
#include "Knight.h"

Knight::Knight()
{
	_trans = make_shared<Transform>();
	_col = make_shared<class CircleCollider>(50);

	_col->GetTransform()->SetParent(_trans);
}

Knight::~Knight()
{
}

void Knight::Update()
{
	_trans->Update();
	_col->Update();
}

void Knight::Render()
{
	_trans->SetWorldBuffer(0);
	_col->Render();
}

void Knight::SetPosition(Vector2 pos)
{
	_trans->SetPosition(pos);
}


