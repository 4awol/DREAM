#include "framework.h"
#include "Bullets.h"

#include "../Gunner_p.h"
Bullets::Bullets()
{
	_col = make_shared<CircleCollider>(10.0f);
	_trans = make_shared<Transform>();

	_trans->SetParent(_col->GetTransform());
	_trans->SetAngle(-PI * 0.5f);
	_col->GetTransform()->SetPosition(Vector2(-WIN_WIDTH * 5, -WIN_HEIGHT * 5));
	_isActive = false;

	_col->Update();
	_trans->Update();


}

Bullets::~Bullets()
{
}

void Bullets::Update()
{
	if (_isActive == false)
		return;

	_col->Update();
	_trans->Update();

	_col->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);

	if (_col->GetTransform()->GetWorldPos().x > 1000 || _col->GetTransform()->GetWorldPos().x <-1000)
		SetActive(false);


}

void Bullets::Render()
{
	if (_isActive == false)
		return;

	_trans->SetWorldBuffer(0);
	_col->Render();
}

void Bullets::Postrender()
{
}


