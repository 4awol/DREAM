#include "framework.h"
#include "Line.h"

Line::~Line()
{
	for (auto pen : _pens)
		DeleteObject(pen);
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	SelectObject(hdc,_pens[_curPenIdex]);

	MoveToEx(hdc, _startPos.x, _startPos.y, nullptr);
	LineTo(hdc, _endPos.x, _endPos.y);
}

HitResult Line::IsCollision(shared_ptr<Line> other)
{
	HitResult result;
	result.col = nullptr;
	result.contact = Vector2(-10000, -10000);
	result.isCollision = false;

	Vector2 a = _endPos - _startPos;
	Vector2 b = other->_endPos - other->_startPos;

	Vector2 aTobStart = other->_startPos - _startPos;
	Vector2 aTobEnd = other->_endPos - _startPos;

	Vector2 bToaStart = _startPos - other->_startPos;
	Vector2 bToaEnd = _endPos - other->_endPos;

	float leftTriangle = abs(a.Cross(aTobStart));
	float rightTriangle = abs(a.Cross(aTobEnd));

	float t = (leftTriangle / (leftTriangle + rightTriangle));

	Vector2 contact = other->_startPos + (other->_endPos - other->_startPos) * t;

	result.isCollision = a.IsBetween(aTobStart, aTobEnd) && b.IsBetween(bToaStart, bToaEnd);
	result.contact = contact;

	return result;
}

void Line::CreatePens()
{
	_curPenIdex = 0;
	_pens.emplace_back(CreatePen(PS_SOLID, 3, GREEN)); // 0
	_pens.emplace_back(CreatePen(PS_SOLID, 3, RED));   // 1
}
