#pragma once
class PaintScene : public Scene
{
public:
	PaintScene();
	virtual ~PaintScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Collider> _mouseCircle;
	shared_ptr<Collider> _circle;

	shared_ptr<Collider> _mouseRect;
	shared_ptr<Collider> _rect;
};

