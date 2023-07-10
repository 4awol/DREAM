#include "framework.h"
#include "DunScene.h"

#include "../../Object/Obj/Player/Gunner_p.h"
#include "../DF/stage_1.h"
#include "../DF/InvenScene.h"
#include "../DF/MainScene.h"

DunScene::DunScene()
{

	_button = make_shared<class Button>(L"Resource/UI/Button.png", Vector2(100, 30));
	_button->SetEvent(std::bind(&DunScene::CameraShake, this));
	_button->SetPosition(Vector2(-580.0f, -300.0f));

	_main = make_shared<class MainScene>();

	_inven = make_shared<class InvenScene>();

	_st1 = make_shared<class stage_1>();
}

DunScene::~DunScene()
{
}

void DunScene::Update()
{
	if(Main==true)
	{
		_main->Update();
		if (KEY_DOWN('X'))
		{
			Main = false;
			St1 = true;
		}
	}
	if (St1 == true)
		_st1->Update();

	_button->Update();
}

void DunScene::Render()
{
	if(Main==true)
		_main->Render();

	if (St1 == true)
		_st1->Render();
	
}

void DunScene::PostRender()
{
	if(Main==true)
		_main->PostRender();

	if (St1 == true)
		_st1->PostRender();

	_button->PostRender();


}

void DunScene::CameraShake()
{
	CAMERA->ShakeStart(5.0f, 1.0f);
}
