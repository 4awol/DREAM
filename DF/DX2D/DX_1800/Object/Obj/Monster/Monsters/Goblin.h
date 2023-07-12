#pragma once
#include "../Monster.h"

#include "framework.h"

class Goblin : public Monster
{
public:
	Goblin();
	~Goblin();

	void Update();
	void Render();
	void PostRender();

	shared_ptr<RectCollider> GetCollider() { return _col; }

	int GetHp() { return _hp; }
	void Mhp() { _hp -= 0.1; }
	

private:
	shared_ptr<class RectCollider> _col;
	shared_ptr<class Transform> _trans;

	int _hp=2;
};
