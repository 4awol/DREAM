#include "framework.h"
#include "Knight.h"

#include "../Gunner_p.h"
#include "../../Monster/Monster.h"
#include "../../Monster/Goblin/Goblin.h"

Knight::Knight()
{
	_trans = make_shared<Transform>();
	_col = make_shared<class CircleCollider>(50);
	_col->GetTransform()->SetParent(_trans);

	CreateAction("doll_idle");
	CreateAction("doll_attack",0.08f,Action::LOOP);

	_actions[State::IDLE]->Play();
	_actions[State::ATTACK]->Play();

}

Knight::~Knight()
{
}

void Knight::Update()
{
	if (Gunner_p::Instance()._isActive_Knight == true)
	{
		_trans->Update();
		_col->Update();

		Grounded();

		_actions[_curState]->Update();
		_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
		_sprites[_curState]->Update();
	}
}

void Knight::Render()
{
	if (Gunner_p::Instance()._isActive_Knight == true)
	{
		_trans->SetWorldBuffer(0);
		_col->Render();
		_sprites[_curState]->Render();
	}
}

void Knight::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

void Knight::SetPosition(Vector2 pos)
{
	_trans->SetPosition(pos);
	SetAction(State::IDLE);
}

void Knight::Grounded()
{
	if (_trans->GetPos().y > -250)
	{
		_trans->AddVector2(Vector2(0, -30));
		Attack();
	}
	std::bind(&Knight::SetPosition, this);
}

void Knight::Attack()
{
	if (_trans->GetPos().y > -300)
	{
		SetAction(State::ATTACK);

		if (Gunner_p::Instance()._howLook == false)
		{
			_sprites[_curState]->SetRight();
		}
		else
		{
			_sprites[_curState]->SetLeft();
		}
	}

	if (_col->IsCollision(_goblin->GetCollider()))
	{
		_goblin->Mhp();
	}
}

void Knight::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Helper/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Helper/" + name + ".xml";
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


