#include "framework.h"
#include "Gunner_p.h"

#include "Helper/Knight.h"
#include "Bullets/Bullets.h"

#include "../../../Scene/DF/StageSelectScene.h"


Gunner_p::Gunner_p()
{
	_col = make_shared<RectCollider>(Vector2(40, 80));
	_trans = make_shared<Transform>();
	
	CreateAction("Gunner_Idle", 0.2f, Action::PINGPONG);

	_trans->SetParent(_col->GetTransform());

	SetPosition();


	_actions[State::IDLE]->Play();
	_sprites[0]->SetRight();

	_knight = make_shared<class Knight>();

	_hpbar = make_shared<HPbar>();
	_hpbar->SetPosition(_col->GetTransform()->GetWorldPos());

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<class Bullets> bullet = make_shared<class Bullets>();
		bullet->_isActive = false;
		_bullets.push_back(bullet);
	}
}

Gunner_p::~Gunner_p()
{
}

void Gunner_p::Update()
{
	
	{
		Input();
		Jump();

		_trans->Update();
		_col->Update();

		_actions[_curState]->Update();
		_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
		_sprites[_curState]->Update();

		if (!CanMove)
		{
			// 일정 시간 (예: 3초)이 지나면 CanMove을 다시 true로 설정
			static float elapsedTime = 0.0f;
			elapsedTime += DELTA_TIME;

			if (elapsedTime >= 0.3f)
			{
				CanMove = true;
				elapsedTime = 0.0f;
			}
		}

		if (_isActive_Knight == true)
		{
			_timer += DELTA_TIME;

			_knight->Update();
			if (_timer >= 1.0f)
			{
				_isActive_Knight = false;
				_timer = 0.0f;
			}
		}

		for (auto bullet : _bullets)
			bullet->Update();

	}
}

void Gunner_p::Render()
{

	_trans->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_col->Render();


	for (auto bullet : _bullets)
		bullet->Render();

	if (_isActive_Knight == true)
	{
		_knight->Render();
	}

}

void Gunner_p::PostRender()
{
}

void Gunner_p::Input()
{
	if (CanMove == true)
	{
		if (KEY_PRESS(VK_RIGHT))
		{
			_sprites[_curState]->SetRight();
			if (GoRight == true)
			{
				_col->GetTransform()->AddVector2(RIGHT_VECTOR * DELTA_TIME * _speed);
				_howLook = false;
			}
		}

		if (KEY_PRESS(VK_LEFT))
		{
			_sprites[_curState]->SetLeft();
			if (GoLeft == true)
			{
				_col->GetTransform()->AddVector2(-RIGHT_VECTOR * DELTA_TIME * _speed);
				_howLook = true;
			}
		}
	}
	
	if (KEY_DOWN('1'))
	{
		if (_isActive_Knight == true)
			return;
		_isActive_Knight = true;
		_knight->SetPosition(_trans->GetWorldPos()+Vector2(50,0));
	}

	Attack();

}

void Gunner_p::Jump()
{
	{
		_jumpPower -= GRAVITY * 9;

		if (_jumpPower < -_maxFalling)
			_jumpPower = -_maxFalling;

		_col->GetTransform()->AddVector2(Vector2(0.0f, _jumpPower * DELTA_TIME));
		//_trans->AddVector2(Vector2(0.0f, _jumpPower * DELTA_TIME));

		if(Gunner_p::Instance()._col->GetTransform()->GetPos().y <-190)
		{
			if (KEY_DOWN('C')) // Spacebar를 누르고 현재 낙하 중이 아닐 때만 실행
			{
				_jumpPower = 1500.0f;
				_isFalling = true;
			}
		}
	}

}

void Gunner_p::Attack()
{
	if (KEY_DOWN('X'))
	{
		CanMove = false;

		shared_ptr<Bullets> curBullet = SetBullets();
		if (curBullet == nullptr)
			return;
		
		curBullet->_isActive = true;
		curBullet->SetPosition(_col->GetTransform()->GetWorldPos());
		if (_howLook == false)
		{
			curBullet->SetDirection(RIGHT_VECTOR);  // 오른쪽 방향으로 설정
		}
		else
		{
			curBullet->SetDirection(-RIGHT_VECTOR);  // 왼쪽 방향으로 설정
		}


	}
}

void Gunner_p::SetAction(State state)
{
	if (_curState == state)
		return;

	_curState = state;

	_actions[_oldState]->Reset();
	_actions[_oldState]->Pause();

	_actions[_curState]->Play();

	_oldState = _curState;
}

shared_ptr<Bullets> Gunner_p::SetBullets()
{
	for (auto bullet : _bullets)
	{
		if (bullet->IsActive() == false)
			return bullet;
	}

	return nullptr;
}

void Gunner_p::SetPosition()
{
	_col->GetTransform()->SetPosition(Vector2(-600, -100));
}

void Gunner_p::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/Player/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/Player/" + name + ".xml";
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



