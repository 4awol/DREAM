#pragma once
class DunMonster
{
public:
	DunMonster();
	~DunMonster();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void TakeDamage(int amount) { _hp -= amount; }

	shared_ptr<RectCollider> GetCollider() { return _col; }

	bool IsActive() { return _hp > 0; }
	int _hp = 10;

private:
	shared_ptr<RectCollider> _col;

	shared_ptr<Transform> _trans;
	shared_ptr<Quad> _quad;
};

