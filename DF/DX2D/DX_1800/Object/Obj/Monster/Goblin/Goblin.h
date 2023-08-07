#pragma once
#include "../Monster.h"

#include "framework.h"
#include "../../Player/Gunner_p.h"

class Goblin : public Monster
{
	enum State
	{
		IDLE,
		WALK,
		ATTACK
	};
public:
	Goblin();
	~Goblin();

	void Update() override;
	void Render() override;
	void PostRender() override;

	void SetAction(State state);


	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTrans() { return _trans; }
	int GetHp() { return _hp; }
	void Mhp() { _hp -= 5; }
	void SetHp() { _hp = 75; }

	void ChasePlayer();
	void Attack();
	void AttackEnd();

	void SetPosition();
	
	void DropWeapon();

private:
	void CreateAction(string name, float speed = 0.1f, Action::Type type = Action::Type::LOOP, CallBack callBack = nullptr);

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite_Clip>> _sprites;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	shared_ptr<class RectCollider> _col;
	shared_ptr<class Transform> _trans;

	bool _isAttack = false;

	float _timer = 0.0f;
	int _hp = 2000;

	float _attackTime = 0.0f;
};
