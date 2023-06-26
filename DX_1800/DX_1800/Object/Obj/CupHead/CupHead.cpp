#include "framework.h"
#include "CupHead.h"

CupHead::CupHead()
{
	_col = make_shared<CircleCollider>(50);
	_transform = make_shared<Transform>();

	CreateAction("Idle");
	CreateAction("Run");
	CreateAction("Jump");

	_col->GetTransform()->SetPosition(CENTER);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0,20));

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
	Jump();

	_col->Update();
	_transform->Update();

	_actions[_curState]->Update();

	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void CupHead::Render()
{
	_transform->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_col->Render();
}

void CupHead::PostRender()
{
}

void CupHead::Input()
{
	if (KEY_PRESS('A'))
	{
		_col->GetTransform()->AddVector2(-RIGHT_VECTOR * _speed * DELTA_TIME);
		
		SetLeft();
	}
	
	if (KEY_PRESS('D'))
	{
		_col->GetTransform()->AddVector2(RIGHT_VECTOR * _speed * DELTA_TIME);

		SetRight();
	}

	if(_curState == State::JUMP)
		return;

	if(KEY_PRESS('A') || KEY_PRESS('D'))
		SetAction(State::RUN);
	else if(_curState == State::RUN)
		SetAction(State::IDLE);
}

void CupHead::Jump()
{
	if(_isFalling == true)
		SetAction(State::JUMP);
	else if(_curState == JUMP && _isFalling == false)
		SetAction(State::IDLE);

	_jumpPower -= GRAVITY * 9;

	if(_jumpPower < -_maxFalling)
		_jumpPower = -_maxFalling;

	_col->GetTransform()->AddVector2(Vector2(0.0f,_jumpPower * DELTA_TIME));

	if (KEY_DOWN(VK_SPACE))
	{
		_jumpPower = 1500.0f;
		_isFalling = true;
	}
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
		if(row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		averageW += w;
		averageH += h;
		count++;

		Action::Clip clip = Action::Clip(x,y,w,h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Action> action = make_shared<Action>(clips, name, type, speed);
	action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW/count, averageH/count));
	_sprites.push_back(sprite);
}

void CupHead::SetAction(State state)
{
	if(_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}
