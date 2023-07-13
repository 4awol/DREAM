#pragma once

class stage_1
{
public:
	stage_1();
	~stage_1();

	void Update();
	void Render();
	void PostRender();

	void Attack();
	void IsCollision();

	bool _st1_OnAir = false;


private:
	shared_ptr<class Goblin> _goblin;
	shared_ptr<class BattleField> _bg;

	Vector2 _collisionPos;
};

