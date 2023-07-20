#include "framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	_trans = make_shared<Transform>();
	_quad = make_shared<Quad>(L"Resource/Main/mainScene.png");
	_trans->SetPosition(Vector2(0,0));

	_col = make_shared<RectCollider>(Vector2(110, 40));
	_col->GetTransform()->AddVector2(Vector2(10, -90));

}

MainScene::~MainScene()
{
}

void MainScene::Update()
{
	_trans->Update();
	_quad->Update();

	_col->Update();


	if (_col->IsCollision(S_MOUSE_POS))
	{
		_col->SetColorRed();

		if (KEY_DOWN(VK_LBUTTON))
		{
			_main_OnAir = 0;
		}
	}
	else
	{
		_col->SetColorGreen();
	}
}

void MainScene::Render()
{
	_trans->SetWorldBuffer(0);
	_quad->Render();

	_col->Render();

}

void MainScene::PostRender()
{
}
