#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_circle = make_shared<CircleCollider>(10, Vector2(-100,-100));
	_pos = _circle->GetCenter();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if(_isActive == false)
		return;

	_pos += _direction * _speed;
	//_direction.y += GRAVITY;

	_circle->SetCenter(_pos);
	_circle->Update();

	if(_pos.x > WIN_WIDTH || _pos.x < 0)
		_direction.x = -_direction.x;
	if(_pos.y > WIN_HEIGHT || _pos.y < 0)
		_direction.y = -_direction.y;
}

void Bullet::Render(HDC hdc)
{
	if(_isActive == false)
		return;

	_circle->Render(hdc);
}

bool Bullet::AttackCannon(shared_ptr<Cannon> cannon)
{
	if (_circle->IsCollision(cannon->GetCol()) && cannon->IsDead() == false)
	{
		_isActive = false;
		return true;
	}

	return false;
}
