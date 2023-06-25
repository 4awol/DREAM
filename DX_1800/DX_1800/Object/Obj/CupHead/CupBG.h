#pragma once
class CupBG
{
public:
	CupBG();
	~CupBG();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	shared_ptr<class RectCollider> GetCollider() { return _col; }


private:
	shared_ptr<class RectCollider> _col;
	shared_ptr<class Transform> _transform;
	shared_ptr<class Quad> _quad;
};

