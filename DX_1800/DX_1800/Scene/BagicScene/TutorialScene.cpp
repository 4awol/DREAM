#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Winter.png");
	_trans = make_shared<Transform>();

	_trans->SetPosition(CENTER);
	_trans->SetScale(Vector2(0.5f, 0.5f));
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_trans->Update();
	_quad->Update();
}

void TutorialScene::Render()
{
	_trans->SetWorldBuffer(0);
	_quad->Render();
}