#pragma once
#include "../Monster.h"

#include "framework.h"
#include "../../Player/Gunner_p.h"

class Goblin : public Monster
{
public:
	enum State
	{
		IDLE
	};
	Goblin();
	~Goblin();

	void Update();
	void Render();
	void PostRender();

	void SetAction(State state);

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTrans() { return _trans; }
	int GetHp() { return _hp; }
	void Mhp() { _hp -= 0.1; }
	void SetHp() { _hp = 2; }

	void ChasePlayer();
	void Attack();

	void SetPosition();
	
	void DropWeapon();

	struct 
	{

	};

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	shared_ptr<class RectCollider> _col;
	shared_ptr<class Transform> _trans;

	float _timer = 0.0f;
	
	int _hp=2;
};
