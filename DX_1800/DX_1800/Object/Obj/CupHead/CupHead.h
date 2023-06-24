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

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _state = State::IDLE;
};

