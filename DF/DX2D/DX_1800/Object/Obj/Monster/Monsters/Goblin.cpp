#include "framework.h"
#include "Goblin.h"

#include "../Monster.h"
#include "../../Player/Gunner_p.h"

Goblin::Goblin()
{
	_col = make_shared<RectCollider>(Vector2(150, 150));
	_trans = make_shared<Transform>();

	_trans->SetPosition(Vector2(500, -180));

	_col->GetTransform()->SetParent(_trans);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	_trans->Update();
	_col->Update();

	ChasePlayer();
}

void Goblin::Render()
{

	_trans->SetWorldBuffer(0);
	_col->Render();
}

void Goblin::PostRender()
{
	ImGui::Text("%d", _hp);
}

void Goblin::ChasePlayer()
{
	float distanceX = Gunner_p::Instance()._col->GetTransform()->GetPos().x - GetTrans()->GetPos().x;

	if (distanceX > 120)
	{
		GetTrans()->AddVector2(RIGHT_VECTOR);
	}
	else if (distanceX < -120)
	{
		GetTrans()->AddVector2(-RIGHT_VECTOR);
	}

	if (distanceX >= -120 && distanceX <= 120)
	{
		Attack();
	}
	else
	{
		_col->SetColorGreen();
	}
}

void Goblin::Attack()
{
	_col->SetColorRed();

	float distanceX = Gunner_p::Instance()._col->GetTransform()->GetPos().x - GetTrans()->GetPos().x;

	
		_timer += DELTA_TIME;

		if (_timer >= 1.0f)
		{
			if (distanceX < 120)
			{
				Gunner_p::Instance().MHp();
			}
			else if (distanceX < -120)
			{
				Gunner_p::Instance().MHp();
			}

			_timer = 0.0f;
		}
	}

void Goblin::SetPosition()
{
	_trans->SetPosition(Vector2(500, -180));
}




