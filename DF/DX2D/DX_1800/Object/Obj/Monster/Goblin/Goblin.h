#pragma once
#include "../Monster.h"

#include "framework.h"
#include "../../Player/Gunner_p.h"

class Goblin : public Monster
{
public:
	Goblin();
	~Goblin();

	void Update() override;
	void Render() override;
	void PostRender() override;

	shared_ptr<RectCollider> GetCollider() { return _col; }
	shared_ptr<Transform> GetTrans() { return _trans; }
	int GetHp() { return _hp; }
	void Mhp() { _hp -= 0.1; }
	void SetHp() { _hp = 2; }

	void ChasePlayer();
	void Attack();

	void SetPosition();
	
	void DropWeapon();

private:
	shared_ptr<class RectCollider> _col;
	shared_ptr<class Transform> _trans;

	float _timer = 0.0f;
	
	int _hp=10000;
};
