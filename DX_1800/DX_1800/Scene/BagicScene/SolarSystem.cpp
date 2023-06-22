#include "framework.h"
#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	_sun = make_shared<Planet>(L"sun");
	_sun->SetScale({0.3f, 0.3f});

	_earth = make_shared<Planet>(L"earth");
	_earth->SetScale({0.3f, 0.3f});
	_earth->SetRotation(0.0002f);

	_moon = make_shared<Planet>(L"moon");
	_moon->SetScale({0.3f,0.3f});
	_moon->SetRotation(0.0003f);

	_earth->SetPosition(Vector2(800.0f,0.0f));
	_moon->SetPosition(Vector2(800.0f, 0.0f));

	_sun->SetPosition(CENTER);

	_earth->SetParent(_sun->GetOrbit());
	_moon->SetParent(_earth->GetOrbit());
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::Update()
{
	if(KEY_PRESS('A'))
		_sun->SetPosition(MOUSE_POS);

	if (KEY_PRESS('D'))
	{
		Vector2 start = _sun->GetTransform()->GetWorldPos();
		Vector2 end = MOUSE_POS;

		_sun->SetPosition(LERP(start,end, 0.001f));
	}
		

	_sun->Update();
	_earth->Update();
	_moon->Update();
}

void SolarSystem::Render()
{
	_earth->Render();
	_sun->Render();
	_moon->Render();
}
