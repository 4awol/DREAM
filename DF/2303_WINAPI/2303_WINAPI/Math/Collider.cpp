#include "framework.h"
#include "Collider.h"

Collider::Collider(Vector2 center)
: _center(center)
{
	CreatePens();
}

Collider::~Collider()
{
	for(auto pen : _pens)
		DeleteObject(pen);
}

void Collider::SetCenter(const Vector2& center)
{
	_center = center;
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
	switch (col->_type)
	{
	case Collider::Type::NONE:
		return false;
	case Collider::Type::CIRCLE:
		return IsCollision(dynamic_pointer_cast<CircleCollider>(col));
	case Collider::Type::RECT:
		return IsCollision(dynamic_pointer_cast<RectCollider>(col));
	default:
		return false;
	}
}

void Collider::CreatePens()
{
	_curPenIdex = 0;
	_pens.emplace_back(CreatePen(PS_SOLID, 3, GREEN)); // 0
	_pens.emplace_back(CreatePen(PS_SOLID, 3, RED));   // 1
}
