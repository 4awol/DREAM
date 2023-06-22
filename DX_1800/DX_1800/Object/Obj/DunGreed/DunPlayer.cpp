#include "framework.h"
#include "DunPlayer.h"
#include "DunBullet.h"

DunPlayer::DunPlayer()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Player.png");
	_quadTrans = make_shared<Transform>();

	_bowSlot = make_shared<Transform>();
	_bowSlot->SetParent(_quadTrans);

	_bowQuad = make_shared<Quad>(L"Resource/Texture/Bow.png");
	_bowTrans = make_shared<Transform>();
	_bowTrans->SetParent(_bowSlot);

	_bowTrans->SetPosition(Vector2(100.0f,0.0f));
	_bowTrans->SetAngle(-PI * 0.75f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<DunBullet> bullet = make_shared<DunBullet>();
		_bullets.push_back(bullet);
	}
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::Update()
{
	InPut();

	_quad->Update();
	_quadTrans->Update();

	_bowQuad->Update();
	_bowTrans->Update();

	_bowSlot->Update();

	Vector2 slotToMousePos = MOUSE_POS - _bowSlot->GetWorldPos();
	float angle = slotToMousePos.Angle();

	_bowSlot->SetAngle(angle);

	for(auto bullet : _bullets)
		bullet->Update();
}

void DunPlayer::Render()
{
	_quadTrans->SetWorldBuffer(0);
	_quad->Render();

	_bowTrans->SetWorldBuffer(0);
	_bowQuad->Render();

	for(auto bullet : _bullets)
		bullet->Render();
}

void DunPlayer::InPut()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 start = _bowTrans->GetWorldPos();
		Vector2 direction = (MOUSE_POS - start).NorMalVector2();

		auto iter = std::find_if(_bullets.begin(), _bullets.end(), [](shared_ptr<DunBullet> bullet)-> bool 
		{
			if(bullet->_isActive == false)
				return true;

			return false;
		});

		if(iter != _bullets.end())
			(*iter)->Fire(start, direction);
	}
}
