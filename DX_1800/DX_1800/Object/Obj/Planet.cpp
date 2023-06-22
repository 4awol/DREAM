#include "framework.h"
#include "Planet.h"

Planet::Planet(wstring name)
{
	wstring path = L"Resource/Texture/" + name + L".png";
	_quad = make_shared<Quad>(path);
	_trans = make_shared<Transform>();

	_orbit = make_shared<Transform>();
}

Planet::~Planet()
{
}

void Planet::Update()
{
	_trans->AddAngle(_rotationSpeed);
	_orbit->AddAngle(_rotationSpeed * 1.5f);

	_quad->Update();
	_trans->Update();
	_orbit->Update();
}

void Planet::Render()
{
	_trans->SetWorldBuffer(0);
	_quad->Render();
}

void Planet::SetPosition(Vector2 pos)
{
	_trans->SetPosition(pos);
	_orbit->SetPosition(pos);
}
