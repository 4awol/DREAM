#include "framework.h"

#include "Scene/PaintScene.h"
#include "Scene/LineScene.h"

#include "Program.h"

Program::Program()
{
	// ¾À ¹Ù²Ù±â
	_scene = make_shared<LineScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render(HDC hdc)
{
	_scene->Render(hdc);
}
