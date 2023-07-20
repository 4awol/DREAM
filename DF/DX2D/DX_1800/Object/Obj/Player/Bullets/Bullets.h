#pragma once
class Bullets
{
public:
	Bullets();
	~Bullets();

	void Update();
	void Render();

	void Postrender();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetDirection(Vector2 dir) { _direction = dir.NorMalVector2(); _col->GetTransform()->SetAngle(dir.Angle()); }

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive;  }

	shared_ptr<CircleCollider> GetCollider() { return _col; }

	bool _isActive = false;
	float _lifeTime = 0.0f;

	shared_ptr<Transform> &GetTrans() { return _trans; }

private:
	shared_ptr<CircleCollider> _col;
	shared_ptr<Transform> _trans;

	Vector2 _direction;
	float _speed = 1000.0f;


};

