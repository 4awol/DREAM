#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circleCollider = make_shared<CircleCollider>(50);
	_circleColliderMouse = make_shared<CircleCollider>(100);
	_rectColliderKeyBoard = make_shared<RectCollider>(Vector2(90,150));
	_rectCollider2  = make_shared<RectCollider>(Vector2(200,120));

	_circleCollider->GetTransform()->SetPosition(CENTER);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	// 충돌처리
	if (_isActive)
	{
		if (_circleColliderMouse->IsCollision(_circleCollider))
		{
			_isActive = false;
			_circleCollider->SetColorRed();
		}
		else
		{
			_circleCollider->SetColorGreen();
		}
	}

	if (KEY_DOWN(VK_SPACE))
	{
		_isActive = true;
		_circleColliderMouse->GetTransform()->SetPosition(Vector2(0,0));
		_dir = MOUSE_POS - Vector2(0,0);
		_dir.Normalize();
	}

	_circleColliderMouse->GetTransform()->AddVector2(_dir * 300.0f * DELTA_TIME);

	_circleCollider->Update();

	if(_isActive)
		_circleColliderMouse->Update();
}

void ColliderScene::Render()
{
	_circleCollider->Render();
	if (_isActive)
		_circleColliderMouse->Render();
}

void ColliderScene::PostRender()
{
}
