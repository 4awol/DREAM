#include "framework.h"
#include "InvenScene.h"

InvenScene::InvenScene()
{
	{ // 아이템 리스트
		_rectCol.resize(3, vector<shared_ptr<RectCollider>>(3));

		

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_rectCol[i][j] = make_shared<RectCollider>(Vector2(200, 200));
				_rectCol[i][j]->GetTransform()->SetPosition(Vector2(220 * i,700-( 220 * j)));
				_rectCol[i][j]->GetTransform()->AddVector2(Vector2(70, -470));
			}
		}
	}
	// 아이템 종류
	{
		_listTrans = make_shared<Transform>();
		_listCol = make_shared<RectCollider>(Vector2(700, 150));
		_listCol->GetTransform()->SetParent(_listTrans);
		_listTrans->AddVector2(Vector2(300, 430));
	}

	{
		_playerwearTrans = make_shared<Transform>();
		_playerwearQuad = make_shared<Quad>(L"", Vector2(100, 100));
		_playerwearCol = make_shared<RectCollider>(Vector2(700, 1000));
		_playerwearCol->GetTransform()->AddVector2(Vector2(-500, 0));
		_playerwearCol->GetTransform()->SetParent(_playerwearTrans);

		_headTrans = make_shared<Transform>();
		_headQuad = make_shared<Quad>(L"Resource/Inven/helmet_icon.png", Vector2(100, 100));
		_headCol = make_shared<RectCollider>(Vector2(100, 100));
		_headCol->GetTransform()->AddVector2(Vector2(-450, 400));
		_headTrans->SetParent(_headCol->GetTransform());

		_armorTrans = make_shared<Transform>();
		_armorQuad = make_shared<Quad>(L"Resource/Inven/wear_icon.png",Vector2(100,100));
		_armorCol = make_shared<RectCollider>(Vector2(100, 100));
		_armorCol->GetTransform()->AddVector2(Vector2(-500, 100));
		_armorTrans->SetParent(_armorCol->GetTransform());

		_weaponTrans = make_shared<Transform>();
		_weaponQuad = make_shared<Quad>(L"Resource/Inven/weapon_icon.png", Vector2(100, 100));
		_weaponCol = make_shared<RectCollider>(Vector2(100, 100));
		_weaponCol->GetTransform()->AddVector2(Vector2(-720, -100));

		_bootsTrans = make_shared<Transform>();
		_bootsQuad = make_shared<Quad>(L"Resource/Inven/boots_icon.png", Vector2(100,100));
		_bootsCol = make_shared<RectCollider>(Vector2(100, 100));
		_bootsCol->GetTransform()->AddVector2(Vector2(-500, -350));
		_bootsTrans->SetParent(_bootsCol->GetTransform());
	}

	_nextButtonTrans = make_shared<Transform>();
	_nextButtonCol = make_shared<RectCollider>(Vector2(200, 100));
	_nextButtonCol->GetTransform()->SetParent(_nextButtonTrans);
	_nextButtonQuad = make_shared <Quad>(L"Resource/UI/Button.png", Vector2(200, 100));
	_nextButtonTrans->AddVector2(Vector2(500, -400));


	
}

InvenScene::~InvenScene()
{
	
}

void InvenScene::Update()
{
	for (auto Blocks : _rectCol)
	{
		for (auto Block : Blocks)
			Block->Update();
	}

	_listTrans->Update();
	_listCol->Update();

	_playerwearTrans->Update();
	_playerwearQuad->Update();
	_playerwearCol->Update();

	_headTrans->Update();
	_headQuad->Update();
	_headCol->Update();

	_armorTrans->Update();
	_armorQuad->Update();
	_armorCol->Update();

	_weaponTrans->Update();
	_weaponCol->Update();
	_weaponQuad->Update();

	_bootsTrans->Update();
	_bootsQuad->Update();
	_bootsCol->Update();

	_nextButtonTrans->Update();
	_nextButtonCol->Update();
	
	if (_nextButtonCol->IsCollision(S_MOUSE_POS))
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			_inven_OnAir = false;
		}
	}
	
	
}

void InvenScene::Render()
{
	for (auto Blocks : _rectCol)
	{
		for (auto Block : Blocks)
		{
			Block->Render();
		}
	}

	_listTrans->SetWorldBuffer(0);
	_listCol->Render();

	_playerwearTrans->SetWorldBuffer(0);
	_playerwearCol->Render();
	_playerwearQuad->Render();

	_headTrans->SetWorldBuffer(0);
	_headQuad->Render();
	_headCol->Render();

	_armorTrans->SetWorldBuffer(0);
	_armorQuad->Render();
	_armorCol->Render();

	_weaponTrans->SetWorldBuffer(0);
	_weaponCol->Render();
	_weaponQuad->Render();

	_bootsTrans->SetWorldBuffer(0);
	_bootsQuad->Render();
	_bootsCol->Render();

	_nextButtonTrans->SetWorldBuffer(0);
	_nextButtonQuad->Render();

}
