#pragma once
#include "../../../../DX_1800/framework.h"
class CupHead
{
	enum State
	{
		IDLE,
		RUN
	};
public:
	CupHead();
	~CupHead();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(string name, float speed =0.1f, Action::Type type= Action::Type::LOOP, CallBack callBack = nullptr);

private:
	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _transform;
	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprite;

	State state = State::IDLE;
};

