#pragma once
class Knight
{
	enum State
	{
		IDLE,
		ATTACK,
		FALL
	};
public:

	Knight();
	~Knight();

	void Update();
	void Render();

	void SetAction(State state);

	void SetPosition(Vector2 pos);
	void Grounded();
	void Attack();

	shared_ptr<CircleCollider> GetCollider() { return _col; }

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	shared_ptr<Transform> _trans;
	shared_ptr<CircleCollider> _col;

	CallBack callback;

	
};

