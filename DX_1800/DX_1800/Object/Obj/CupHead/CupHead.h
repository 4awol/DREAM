#pragma once
class CupHead
{
	enum State
	{
		IDLE,
		RUN,
		JUMP,
		ATTACK
	};

public:
	CupHead();
	~CupHead();

	void Update();
	void Render();
	void PostRender();

	void SetLeft()
	{
		for(auto sprite : _sprites)
			sprite->SetLeft();
	}
	void SetRight()
	{
		for(auto sprite : _sprites)
			sprite->SetRight();
	}

	void Input();
	void Jump();
	void Attack();
	void SetAction(State state);

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool IsFalling() { return _isFalling; }
	void SetIsFalling(bool value) { _isFalling = value; }
	void Grounded() { _isFalling = false; }
	void AttackEnd();

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);
	
	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	bool _isFalling;
	bool _isAttack = false;

	float _jumpPower = 0.0f;
	float _maxFalling = 800.0f;

	float _speed = 300.0f;

	bool _LR = false;

	// Bullet
	vector<shared_ptr<class Cup_Bullet>> _bullets;
};

