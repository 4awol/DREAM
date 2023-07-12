#pragma once
class Knight
{
public:
	Knight();
	~Knight();

	void Update();
	void Render();

	void SetPosition(Vector2 pos);

private:
	shared_ptr<Transform> _trans;
	shared_ptr<CircleCollider> _col;
};

