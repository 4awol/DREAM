#include "framework.h"
#include "CupHeadScene.h"

#include "../../Object/Obj/CupHead/CupHead.h"
#include "../../Object/Obj/CupHead/CupBG.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<CupHead>();
	_bg = make_shared<CupBG>();
	_bg->SetPosition(Vector2(CENTER.x, 100.0f));
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();
	_bg->Update();

	_bg->GetCollider()->Block(_player->GetCollider());

}

void CupHeadScene::Render()
{
	_bg->Render();
	_player->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
}
