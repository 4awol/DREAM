#pragma once
class BattleField
{
public:
	BattleField();
	~BattleField();

	void Update();
	void Render();

	shared_ptr<RectCollider> GetBottomCollider() { return _colBottom; }
	shared_ptr<RectCollider> GetRightCollider() { return _colRight; }
	shared_ptr<RectCollider> GetLeftCollider() { return _colLeft; }


private:
	shared_ptr<RectCollider> _colBottom;
	shared_ptr<Transform> _transformBottom;

	shared_ptr<RectCollider> _colRight;
	shared_ptr<Transform> _transformRight;

	shared_ptr<RectCollider> _colLeft;
	shared_ptr<Transform> _transformLeft;

	shared_ptr<Transform> _battleFieldTrans;
	shared_ptr<Quad> _battleFieldQuad;

};

