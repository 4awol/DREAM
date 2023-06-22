#include "framework.h"
#include "Cannon.h"

Cannon::Cannon()
{
	_body = make_shared<CircleCollider>(50, _pos);
	Vector2 barrelEnd = _body->GetCenter() + Vector2(_barrelLength, 0.0f);
	_barrel = make_shared<Line>(_body->GetCenter(), barrelEnd);
	_direction = (_barrel->_endPos - _barrel->_startPos).NorMalVector2();

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Bullet> bullet = make_shared<Bullet>();
		bullet->SetActive(false);
		_bullets.push_back(bullet);
	}
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if(IsDead())
		return;

	if (_isControll)
	{
		MoveByInput();
		Fire();
	}

	_body->SetCenter(_pos);
	_barrel->_startPos = _pos;
	_barrel->_endPos = _pos + _direction * _barrelLength;

	_body->Update();
	_barrel->Update();

	for (auto bullet : _bullets)
	{
		bullet->Update();
	}
}

void Cannon::Render(HDC hdc)
{
	if (IsDead())
		return;

	_barrel->Render(hdc);
	_body->Render(hdc);

	for (auto bullet : _bullets)
	{
		bullet->Render(hdc);
	}
}

void Cannon::MoveByInput()
{
	if (GetAsyncKeyState('A'))
	{
		_pos.x -= _speed;
	}
	if (GetAsyncKeyState('D'))
	{
		_pos.x += _speed;
	}
	if (GetAsyncKeyState('W'))
	{
		_angle -= 0.1f;
	}
	if (GetAsyncKeyState('S'))
	{
		_angle += 0.1f;
	}

	_direction.x = cos(_angle);
	_direction.y = sin(_angle);
}

void Cannon::Fire()
{
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
	{
		_spacePress = true;
		_spaceUp = false;
	}
	else
	{
		_spaceUp = true;
	}

	if (_spacePress == true && _spaceUp == true)
	{
		Vector2 muzzle = _barrel->_endPos;

		shared_ptr<Bullet> curBullet = SetBullet();

		if (curBullet == nullptr)
			return;

		curBullet->SetPos(muzzle);
		curBullet->SetDirection(_direction);
		curBullet->SetActive(true);

		_spacePress = false;
		_spaceUp = false;
	}
}

shared_ptr<Bullet> Cannon::SetBullet()
{
	for (auto bullet : _bullets)
	{
		if(bullet->IsActive() == false)
			return bullet;
	}

	return nullptr;
}
