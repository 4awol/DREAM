#pragma once
class Planet
{
public:
	Planet(wstring name);
	~Planet();

	void Update();
	void Render();

	void SetRotation(float speed) { _rotationSpeed = speed; }
	void SetScale(Vector2 scale) { _trans->SetScale(scale); _orbit->SetScale(scale); }
	void SetPosition(Vector2 pos);

	void SetParent(shared_ptr<Transform> trans) { _trans->SetParent(trans); _orbit->SetParent(trans); }

	shared_ptr<Transform> GetTransform() { return _trans; }
	shared_ptr<Transform> GetOrbit() { return _orbit; }

private:
	float _rotationSpeed = 0.0001f;

	shared_ptr<Transform> _orbit;

	shared_ptr<Transform> _trans;
	shared_ptr<Quad> _quad;
};

