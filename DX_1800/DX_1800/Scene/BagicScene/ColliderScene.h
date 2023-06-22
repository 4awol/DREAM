#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	virtual ~ColliderScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<CircleCollider> _circleColliderMouse;
	shared_ptr<CircleCollider> _circleCollider;
	shared_ptr<RectCollider> _rectColliderKeyBoard;
	shared_ptr<RectCollider> _rectCollider2;

	Vector2 _dir;
	bool _isActive = false;
};

