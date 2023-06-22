#pragma once
class DunBullet
{
public:
	DunBullet();
	~DunBullet();

	void Update();
	void Render();

	void Fire(Vector2 startPos, Vector2 dir);

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive = false;
private:
	shared_ptr<CircleCollider> _col;

	shared_ptr<Transform> _trans;
	shared_ptr<Quad> _quad;

	Vector2 _direction;
	float _speed = 500.0f;

	float _curTime = 0.0f;
	float _lifeTime = 3.0f;
};

