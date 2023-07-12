#include "framework.h"
#include "Goblin.h"

#include "../Monster.h"

Goblin::Goblin()
{
	_col = make_shared<RectCollider>(Vector2(50, 50));
	_trans = make_shared<Transform>();

	_col->GetTransform()->SetParent(_trans);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	_trans->Update();
	_col->Update();
}

void Goblin::Render()
{

	_trans->SetWorldBuffer(0);
	_col->Render();
}

void Goblin::PostRender()
{
	ImGui::Text("%d", _hp);
}


