#pragma once
class CircleCollider : public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider() { CreatePens(); }
	CircleCollider(float radius, Vector2 center);
	~CircleCollider();

	void Update();
	void Render(HDC hdc);

	void SetCenter(Vector2 pos) { _center = pos; }
	const Vector2& GetCenter() { return _center; }

	void SetRadius(float radius) { _radius = radius; }
	float GetRadius() { return _radius; }

	bool IsCollision(Vector2 pos);
	bool IsCollision(shared_ptr<CircleCollider> other);
	bool IsCollision(shared_ptr<class RectCollider> other);

	void SetGreen() { _curPenIdex = 0; }
	void SetRed() { _curPenIdex = 1; }

private:
	void CreatePens();

	int _curPenIdex;
	vector<HPEN> _pens;

	float _radius = 0.0f;
	Vector2 _center = {0.0f,0.0f};
};

