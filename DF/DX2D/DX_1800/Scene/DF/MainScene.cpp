#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_col = make_shared<RectCollider>(Vector2(100, 100));
	_trans = make_shared<Transform>();

	_col->GetTransform()->SetParent(_trans);
	_trans->SetPosition(Vector2(0,0));
}

MainScene::~MainScene()
{
}

void MainScene::Update()
{
	_trans->Update();
	_col->Update();


}

void MainScene::Render()
{
	_trans->SetWorldBuffer(0);
	_col->Render();
}

void MainScene::PostRender()
{
	ImGui::Text("press X to start");
}
