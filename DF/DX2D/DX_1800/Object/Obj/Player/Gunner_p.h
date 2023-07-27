#pragma once
#include "framework.h"

#include "Bullets/Bullets.h"
#include "Helper/Knight.h"

class Gunner_p
{
	enum State
	{
		IDLE,
		WALK,
		JUMP,
		JUMPATTACK,
		ATTACK,
		RUN,
		ATTACKCOMBO,
		SLIDING
	};
private:
	Gunner_p();
	~Gunner_p();
public:
	static Gunner_p& Instance()
	{
		static Gunner_p instance;
		return instance;
	}

	Gunner_p(const Gunner_p&) = delete;
	Gunner_p& operator=(const Gunner_p&) = delete;

	void Update();
	void Render();
	void PostRender();

	void Input();
	void Jump();
	void Attack();
	void Run();

	void SetAction(State state);

	bool GoLeft = true;
	void CanGoLeft() { GoLeft = false; }
	void CantGoLeft() { GoLeft = true; }

	bool GoRight = true;
	void CanGoRight() { GoRight = false; }
	void CantGoRight() { GoRight = true; }

	RectCollider& GetCol() { return *_col; }
	shared_ptr<RectCollider> GetCollider() { return _col; }
	Vector2 GetPos() { return _trans->GetWorldPos(); }
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _trans;

	shared_ptr<class Bullets> SetBullets();
	vector<shared_ptr<class Bullets>>& GetBullets() { return _bullets; }
	shared_ptr<class Knight>& GetKnight() { return _knight; }
	bool CanMove = true;
	bool _howLook; //true ¿ÞÂÊ false ¿À¸¥ÂÊ

	bool IsFalling() { return _isFalling; }
	void SetIsFalling(bool value) { _isFalling = value; }
	void Grounded() { _isFalling = false; }
	void AttackEnd();
	Vector2 MoveToward(const Vector2& current, const Vector2& target, float maxDistance);


	void MHp() { _hp -= 1; }
	int GetHp() {return _hp; }
	void SetHp() { _hp = 1; }

	void SetPosition();

	bool _isActive_Knight = false;

private:
	// player
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;


	Vector2 _pos;
	bool _canMove = false;
	float _timer = 0.0f;
	float _speed = 120.0f;
	
	bool _isFalling;
	bool _isAttack = false;
	bool _canDash = false;
	bool _isDash = false;
	float _dashTime = 0.0f;
	bool _isSliding = false;
	float _slideTime = 0.0f;

	float _jumpPower = 0.0f;
	float _maxFalling = 800.0f;

	int _hp = 1;

	// knight
	shared_ptr<class Knight> _knight;

	// hpbar
	shared_ptr<class HPbar> _hpbar;

	// bullets
	vector<shared_ptr<class Bullets>> _bullets;

};
