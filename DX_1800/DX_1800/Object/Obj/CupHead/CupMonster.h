#pragma once
class CupMonster
{
public:
	enum State
	{
		IDLE,
		LOOP,
		END,
		DEAD
	};
	CupMonster();
	~CupMonster();

	void Update();
	void Render();

	void SetLeft()
	{
		for (auto sprite : _sprites)
			sprite->SetLeft();
	}

	void SetRight()
	{
		for (auto sprite : _sprites)
			sprite->SetRight();
	}

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }

	void Collider(RectCollider _col);
private:
	void CreateAction(string name, float speed, Action::Type type, CallBack callBack);

	shared_ptr<RectCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;
};

