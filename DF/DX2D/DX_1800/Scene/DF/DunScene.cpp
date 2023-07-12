#include "framework.h"
#include "DunScene.h"

#include "../../Object/Obj/Player/Gunner_p.h"
#include "MainScene.h"
#include "stage_1.h"
#include "InvenScene.h"

DunScene::DunScene()
{

	_button = make_shared<class Button>(L"Resource/UI/Button.png", Vector2(100, 30));
	_button->SetEvent(std::bind(&DunScene::CameraShake, this));
	_button->SetPosition(Vector2(-580.0f, -300.0f));

	_main = make_shared<class MainScene>();


	_st1 = make_shared<class stage_1>();
}

DunScene::~DunScene()
{
}

void DunScene::Update()
{
	if (_main->_main_OnAir == true)
		_main->Update();
	if (_main->_main_OnAir == false)
	{
		_st1->_st1_OnAir = true;
		_st1->Update();
	}
	if (InvenScene::Instance()._inven_OnAir == true)
		InvenScene::Instance().Update();

	//_button->Update();
}

void DunScene::Render()
{
	if(_main->_main_OnAir == true)
		_main->Render();

	if (_st1->_st1_OnAir == true)
		_st1->Render();

	if(InvenScene::Instance()._inven_OnAir==true)
		InvenScene::Instance().Render();
	
}

void DunScene::PostRender()
{
	if(_main->_main_OnAir == true)
		_main->PostRender();

	if (_st1->_st1_OnAir == true)
		_st1->PostRender();

	_button->PostRender();


}

void DunScene::CameraShake()
{
	CAMERA->ShakeStart(5.0f, 1.0f);
}
