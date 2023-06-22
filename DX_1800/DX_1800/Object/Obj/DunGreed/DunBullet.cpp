#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet()
{
	_col = make_shared<CircleCollider>(15.0f);
	_quad = make_shared<Quad>(L"Resource/Texture/Bullet.png", Vector2(100,100));
	_trans = make_shared<Transform>();

	_trans->SetParent(_col->GetTransform());
}

DunBullet::~DunBullet()
{
}

void DunBullet::Update()
{
	if(_isActive == false)
		return;

	_curTime += DELTA_TIME;

	if (_curTime > _lifeTime)
	{
		_isActive = false;
		_curTime = 0.0f;
	}

	_col->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);

	_col->Update();
	_trans->Update();
	_quad->Update();
}

void DunBullet::Render()
{
	if(_isActive == false)
		return;

	_col->Render();
	_trans->SetWorldBuffer(0);
	_quad->Render();
}

void DunBullet::Fire(Vector2 startPos, Vector2 dir)
{
	_isActive = true;
	_direction = dir;

	_col->GetTransform()->SetAngle(dir.Angle());
	_col->GetTransform()->SetPosition(startPos);
}
