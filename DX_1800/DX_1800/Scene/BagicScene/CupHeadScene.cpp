#include "framework.h"
#include "CupHeadScene.h"

#include "../../Object/Obj/CupHead/CupHead.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<CupHead>();
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();

}

void CupHeadScene::Render()
{
	_player->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
}
