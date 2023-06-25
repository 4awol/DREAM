#include "framework.h"
#include "CupHead.h"

//#include "../../../Framework/Utility/tinyxml2.h"

CupHead::CupHead()
{
	_col = make_shared<CircleCollider>(50);
	_transform = make_shared<Transform>();

	CreateAction("IDLE");
	CreateAction("RUN");
	

	_col->GetTransform()->SetPosition(CENTER);

	_transform->SetParent(_col->GetTransform());
	_transform->AddVector2(Vector2(0, 20));

	_actions[State::IDLE]->Play();
	_actions[State::RUN]->Play();

	_sprites[0]->SetLeft();
	_sprites[1]->SetLeft();

}

CupHead::~CupHead()
{
}

void CupHead::Update()
{
	Input();
	_col->Update();
	_transform->Update();

	_actions[_state]->Update();

	_sprites[_state]->SetCurClip(_actions[_state]->GetCurClip());
	_sprites[_state]->Update();
}

void CupHead::Render()
{
	_col->Render();

	_transform->SetWorldBuffer(0);

	_sprites[_state]->Render();

}

void CupHead::PostRender()
{
	ImGui::SliderInt("State", (int*)&_state, 0, 1);
}

void CupHead::Input()
{
	if (KEY_PRESS('A'))
	{
		_col->GetTransform()->AddVector2(-RIGHT_VECTOR*_speed*DELTA_TIME);
		SetLeft();
		SetAction(State::RUN);
	}
	else if (KEY_UP('A'))
	{
		SetAction(State::IDLE);
	}
	if (KEY_PRESS('D'))
	{
		_col->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);
		SetRight();
		SetAction(State::RUN);
	}
	else if (KEY_UP('D'))
	{
		SetAction(State::IDLE);
	}

}

void CupHead::SetAction(State state)
{
	if (_state == state)
		return;
	
	_actions[_state]->Reset();
	_actions[_state]->Pause();

	_state = state;
	_actions[_state]->Play();
}

void CupHead::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/CupHead/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/CupHead/" + name + ".xml";
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
