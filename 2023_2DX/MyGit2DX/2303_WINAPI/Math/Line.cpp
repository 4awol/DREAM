#include "framework.h"
#include "Line.h"

Line::~Line()
{
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, _startPos.x, _startPos.y, nullptr);
	LineTo(hdc, _endPos.x, _endPos.y);
}
