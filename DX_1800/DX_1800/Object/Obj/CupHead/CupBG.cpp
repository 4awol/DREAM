#include "framework.h"
#include "CupBG.h"

CupBG::CupBG()
{
	_quad = make_shared<class Quad>(L"Resource/CupHead/track.png");
	_col = make_shared<class RectCollider>(_quad->GetImageSize());
	_transform = make_shared<class Transform>();
	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0.0f, 55.0f));
}

CupBG::~CupBG()
{
}

void CupBG::Update()
{
	_col->Update();
	_transform->Update();
	_quad->Update();
}

void CupBG::Render()
{
	_transform->SetWorldBuffer(0);
	_quad->Render();
	_col->Render();
}
