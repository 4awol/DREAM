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
	CreateAction("Gunner_Walk", 0.2f, Action::LOOP);
	CreateAction("Gunner_Jump", 0.05f, Action::END);
	CreateAction("Gunner_JumpAttack", 0.1f, Action::END);
	CreateAction("Gunner_Attack", 0.050f, Action::END);
	CreateAction("Gunner_Dash");
	CreateAction("Gunner_AttackCombo", 0.050f, Action::END);
	CreateAction("Gunner_Sliding", 0.5f, Action::END);

	_trans->SetParent(_col->GetTransform());

	SetPosition();


	_actions[State::IDLE]->Play();
	_actions[State::WALK]->Play();
	_actions[State::JUMP]->Play();
	_actions[State::JUMPATTACK]->Play();
	_actions[State::ATTACK]->Play();
	_actions[State::RUN]->Play();
	_actions[State::SLIDING]->Play();

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
	if (_howLook == true)
		_sprites[_curState]->SetLeft();
	else
		_sprites[_curState]->SetRight();

	{
		Input();
		Jump();
		
		_col->Update();
		_trans->Update();

		_actions[_curState]->Update();
		_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
		_sprites[_curState]->Update();

		if (!CanMove)
		{
			static float elapsedTime = 0.0f;
			elapsedTime += DELTA_TIME;

			if (elapsedTime >= 0.3f)
			{
				CanMove = true;
				elapsedTime = 0.0f;
			}
		}

		if (_dashTime > 0.2f && _curState == IDLE)
		{
			_dashTime = 0.0f;
			_canDash = false;
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

		if (_isSliding==true)
		{
			_slideTime += DELTA_TIME;
			
			if (_slideTime >= 0.60f)
			{
				SetAction(State::IDLE);
				_slideTime = 0.0f;
				_isSliding = false;
			}
			else
			{
				float t = _slideTime / 5.0f; 

				Vector2 currentPosition = _col->GetTransform()->GetPos();
				float moveSpeed = 400.0f; 
				if (_howLook == false)
				{
					Vector2 newPosition = MoveToward(currentPosition, Vector2(currentPosition.x + 400, currentPosition.y), moveSpeed * DELTA_TIME);
					_col->GetTransform()->SetPosition(newPosition);
					_isDash = true;
				}
				if (_howLook == true)
				{
					Vector2 newPosition = MoveToward(currentPosition, Vector2(currentPosition.x - 400, currentPosition.y), moveSpeed * DELTA_TIME);
					_col->GetTransform()->SetPosition(newPosition);
					_isDash = true;
				}
			}
		}

		

		for (auto& bullet : _bullets)
		{
			if (bullet == nullptr)
				return;
			if (IsFalling() == false)
				bullet->GetTrans()->SetAngle(45);
			bullet->Update();
		}

	}
}

void Gunner_p::Render()
{

	_trans->SetWorldBuffer(0);
	_sprites[_curState]->Render();



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
			_dashTime += DELTA_TIME;
			if (_isDash == false)
			{
				SetAction(State::WALK);
				if (GoRight == true)
				{
					_col->GetTransform()->AddVector2(RIGHT_VECTOR * DELTA_TIME * _speed);
					_howLook = false;
				}
			}
		}
	
		if (KEY_UP(VK_RIGHT) && _isSliding==false)
		{
			_canDash = true;
			SetAction(State::IDLE);
			_sprites[_curState]->SetRight();
		}

		if (KEY_PRESS(VK_LEFT))
		{
			_sprites[_curState]->SetLeft();
			_dashTime += DELTA_TIME;

			if (_isDash == false)
			{
				SetAction(State::WALK);
				if (GoLeft == true)
				{
					_col->GetTransform()->AddVector2(-RIGHT_VECTOR * DELTA_TIME * _speed);
					_howLook = true;
				}
			}
		}
		if (KEY_UP(VK_LEFT) && _isSliding == false)
		{
			_canDash = true;
			SetAction(State::IDLE);
			_sprites[_curState]->SetLeft();
		}
	
	}
	if (KEY_DOWN('1'))
	{
		if (_isActive_Knight == true)
			return;
		_isActive_Knight = true;
		if (_howLook == false)
			_knight->SetPosition(_trans->GetWorldPos() + Vector2(50, 0));
		else
			_knight->SetPosition(_trans->GetWorldPos() + Vector2(-50, 0));
	}
	Run();
	Attack();
}

void Gunner_p::Jump()
{
	if (_isFalling == true && _isAttack == false)
		SetAction(State::JUMP);
	else if (_curState == JUMP && _isFalling == false && _isAttack == false)
		SetAction(State::IDLE);

	_jumpPower -= GRAVITY * 9;

	if (_jumpPower < -_maxFalling)
		_jumpPower = -_maxFalling;
	
	_col->GetTransform()->AddVector2(Vector2(0.0f, _jumpPower * DELTA_TIME));

	if (Gunner_p::Instance()._col->GetTransform()->GetPos().y < -190)
	{
		if (KEY_DOWN('C') && _isAttack== false) // Spacebar를 누르고 현재 낙하 중이 아닐 때만 실행
		{
			
			if (_howLook == false)
			{
				_sprites[_curState]->SetRight();
				_jumpPower = 1500.0f;
				_isFalling = true;

			}
			else
			{
				_sprites[_curState]->SetLeft();
				_jumpPower = 1500.0f;
				_isFalling = true;
			}
		}
		
	}
}

void Gunner_p::Attack()
{
	if (KEY_DOWN('X') && _isDash==false)
	{
		if (_isAttack == true)
		{
			CanMove = false;
			_isAttack = true;
			SetAction(State::ATTACKCOMBO);

			shared_ptr<Bullets> curBullet = SetBullets();
			if (curBullet == nullptr)
				return;
			curBullet->_isActive = true;
			if (_howLook == true)
			{
				curBullet->SetPosition(_col->GetTransform()->GetWorldPos() + Vector2(-80, 20));
				curBullet->SetDirection(-RIGHT_VECTOR);  // 왼쪽 방향으로 설정
			}
			if (_howLook == false)
			{
				curBullet->SetPosition(_col->GetTransform()->GetWorldPos() + Vector2(80, 20));
				curBullet->SetDirection(RIGHT_VECTOR);  // 오른쪽 방향으로 설정
			}
			_actions[State::ATTACKCOMBO]->SetEndEvent(std::bind(&Gunner_p::AttackEnd, this));

			

		}
		else if (_isAttack == false)
		{

			CanMove = false;
			_isAttack = true;
			SetAction(State::ATTACK);

			shared_ptr<Bullets> curBullet = SetBullets();
			if (curBullet == nullptr)
				return;
			curBullet->_isActive = true;
			if (_howLook == true)
			{
				curBullet->SetPosition(_col->GetTransform()->GetWorldPos() + Vector2(-50, 20));
				curBullet->SetDirection(-RIGHT_VECTOR);  // 왼쪽 방향으로 설정
			}
			if (_howLook == false)
			{
				curBullet->SetPosition(_col->GetTransform()->GetWorldPos() + Vector2(50, 20));
				curBullet->SetDirection(RIGHT_VECTOR);  // 오른쪽 방향으로 설정
			}
			_actions[State::ATTACK]->SetEndEvent(std::bind(&Gunner_p::AttackEnd, this));

		}
	}
	if (KEY_DOWN('X') && _isDash == true && _col->GetTransform()->GetPos().y < -190)
	{
		_canDash = false;
		_isSliding = true;
		SetAction(State::SLIDING);

	}
}



void Gunner_p::Run()
{
	if (_canDash == true)
	{
		if (KEY_PRESS(VK_LEFT))
		{
			SetAction(State::RUN);
			_isDash = true;
			if(GoLeft == true)
			_col->GetTransform()->AddVector2(-RIGHT_VECTOR * DELTA_TIME * _speed * 4.0f);

		}
		if (KEY_PRESS(VK_RIGHT))
		{
			SetAction(State::RUN);
			_isDash = true;
			if(GoRight == true)
			_col->GetTransform()->AddVector2(RIGHT_VECTOR * DELTA_TIME * _speed * 4.0f);

		}
		if (KEY_UP(VK_LEFT) || KEY_UP(VK_RIGHT))
		{
			_isDash = false;
			SetAction(State::IDLE);
			
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

void Gunner_p::AttackEnd()
{
	_isAttack = false;
	SetAction(State::IDLE);
}

Vector2 Gunner_p::MoveToward(const Vector2& current, const Vector2& target, float maxDistance)
{
	Vector2 direction = target - current;
	float distance = direction.Length();
	if (distance <= maxDistance || distance == 0.0f)
		return target;
	return current + (direction / distance) * maxDistance;
}

void Gunner_p::SetPosition()
{
	_col->GetTransform()->SetPosition(Vector2(-600, -100));
	SetAction(State::IDLE);
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



