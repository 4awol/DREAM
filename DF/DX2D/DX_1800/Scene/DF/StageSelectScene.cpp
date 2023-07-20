#include "framework.h"
#include "StageSelectScene.h"

#include "InvenScene.h"

StageSelectScene::StageSelectScene()
{
	_st1_trans = make_shared<Transform>();
	_st1_col = make_shared<RectCollider>(Vector2(100, 100));
	_st1_col->GetTransform()->SetParent(_st1_trans);
	_st1_trans->AddVector2(Vector2(-700, 400));

	_callInvenTrans = make_shared<Transform>();
	_callInvenCol = make_shared<RectCollider>(Vector2(200, 80));
	_callInvenCol->GetTransform()->SetParent(_callInvenTrans);
	_callInvenQuad = make_shared<Quad>(L"Resource/UI/Button.png", Vector2(200, 100));
	_callInvenTrans->SetPosition(Vector2(600, -200));
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Update()
{
	if (_selectScene_OnAir == true)
	{
		_st1_trans->Update();
		_st1_col->Update();

		IsCollision();

		_callInvenTrans->Update();
		_callInvenQuad->Update();
		_callInvenCol->Update();
	}

	if (InvenScene::Instance()._inven_OnAir == true)
		InvenScene::Instance().Update();
}

void StageSelectScene::Render()
{
	if (_selectScene_OnAir == true)
	{
		_st1_trans->SetWorldBuffer(0);
		_st1_col->Render();

		_callInvenTrans->SetWorldBuffer(0);
		_callInvenCol->Render();
		_callInvenQuad->Render();
	}

	if (InvenScene::Instance()._inven_OnAir == true)
		InvenScene::Instance().Render();
}

void StageSelectScene::PostRender()
{
	ImGui::Text("StageSelectScene");
}

void StageSelectScene::IsCollision()
{
	// stage1
	if (_st1_col->IsCollision(S_MOUSE_POS))
	{
		_st1_col->SetColorRed();
		
		if (KEY_DOWN(VK_LBUTTON))
		{
			_selectScene_OnAir = false;
			SelectStage = 1;
		}
	}
	else
	{
		_st1_col->SetColorGreen();
	}

	// inven
	if (_callInvenCol->IsCollision(S_MOUSE_POS))
	{
		_callInvenCol->SetColorRed();

		if (KEY_DOWN(VK_LBUTTON))
		{
			_selectScene_OnAir = false;
			InvenScene::Instance()._inven_OnAir = true;
		}
	}
	else
	{
		_st1_col->SetColorGreen();
	}
}
