#include "framework.h"
#include "Goblin.h"

#include "../Monster.h"
#include "../../Player/Gunner_p.h"

Goblin::Goblin()
{
	_col = make_shared<RectCollider>(Vector2(70, 100));
	_trans = make_shared<Transform>();
	_trans->SetPosition(Vector2(500, -230));
	_col->GetTransform()->SetParent(_trans);

	CreateAction("Monster_Idle");
	CreateAction("Goblin_Walk");
	CreateAction("Goblin_Attack", 0.3f, Action::END);
	SetAction(State::IDLE);

	_actions[State::IDLE]->Play();
	_actions[State::WALK]->Play();
	_actions[State::ATTACK]->Play();

}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	_actions[_curState]->Update();
	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();

	_trans->Update();
	_col->Update();

	ChasePlayer();

	if (_isAttack == true)
	{
		_attackTime += DELTA_TIME;
	
		if (_attackTime >= 2.0f)
		{
			_isAttack = false;
			_attackTime = 0.0f;
		}
	}
}

void Goblin::Render()
{
	_trans->SetWorldBuffer(0);
	_col->Render();

	_sprites[_curState]->Render();

}

void Goblin::PostRender()
{
	ImGui::Text("%d", _hp);
	ImGui::Text("%f", _timer);
}

void Goblin::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void Goblin::ChasePlayer()
{
	float distanceX = Gunner_p::Instance()._col->GetTransform()->GetPos().x - GetTrans()->GetPos().x;

	if (_isAttack == false)
	{
		if (distanceX > 120)
		{
			GetTrans()->AddVector2(RIGHT_VECTOR);
			_sprites[_curState]->SetRight();
			_sprites[State::ATTACK]->SetRight();
			SetAction(State::WALK);
		}
		else if (distanceX < -120)
		{
			GetTrans()->AddVector2(-RIGHT_VECTOR);
			_sprites[_curState]->SetLeft();
			_sprites[State::ATTACK]->SetLeft();
			SetAction(State::WALK);

		}
	}
	if (distanceX >= -120 && distanceX <= 120)
		{
			Attack();
		}
	else
	{
		_col->SetColorGreen();
		_timer = 0.0f;
		_isAttack == false;
	}
}

void Goblin::Attack()
{
	_col->SetColorRed();

	float distanceX = Gunner_p::Instance()._col->GetTransform()->GetPos().x - GetTrans()->GetPos().x;

	_isAttack = true;
	SetAction(State::ATTACK);

	_timer += DELTA_TIME;

	if (_timer >= 0.60f)
	{
		if (distanceX < 120 || distanceX < -120)
		{
			Gunner_p::Instance().MHp();
		}
		_timer = 0.0f;
	}
	_actions[State::ATTACK]->SetEndEvent(std::bind(&Goblin::AttackEnd, this));
}

void Goblin::AttackEnd()
{
	_isAttack = false;
}

void Goblin::SetPosition()
{
	_trans->SetPosition(Vector2(500, -230));
}

void Goblin::DropWeapon()
{
}

void Goblin::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Monster/Goblin/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Monster/Goblin/" + name + ".xml";
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;
	float averageW = 0;
	float averageH = 0;
	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		averageW += w;
		averageH += h;
		count++;

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, name, type, speed);
	action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	_sprites.push_back(sprite);

}


