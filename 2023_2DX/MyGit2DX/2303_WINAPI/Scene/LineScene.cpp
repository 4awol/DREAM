#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_floorLine = make_shared<Line>(Vector2(100,600), Vector2(1300, 600));
	_mouseLine = make_shared<Line>(Vector2(100,300), Vector2(1000, 700));
	_shadowLine = make_shared<Line>(Vector2(100,500), Vector2(110, 500));
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_mouseLine->_endPos = mousePos;

}

void LineScene::Render(HDC hdc)
{
	_floorLine->Render(hdc);
	_mouseLine->Render(hdc);
	_shadowLine->Render(hdc);
}
