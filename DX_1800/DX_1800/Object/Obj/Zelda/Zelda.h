#pragma once
class Zelda
{
public:
	enum State
	{
		IDLE_F,
		IDLE_L,
		IDLE_B,
		IDLE_R,

		RUN_F,
		RUN_L,
		RUN_B,
		RUN_R
	};

	Zelda();
	~Zelda();

	void Update();
	void Render();

	void Input();


private:
	void CreateActions();

	State _state = State::IDLE_F;

	shared_ptr<Transform> _transform;
	shared_ptr<Sprite_Clip> _sprite;

	vector<shared_ptr<Action>> _actions;
};

