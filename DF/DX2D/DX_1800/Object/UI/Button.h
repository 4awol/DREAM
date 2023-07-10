#pragma once
class Button
{
public:
	Button(wstring path, Vector2 size);
	~Button();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _col->GetTransform()->SetPosition(pos); }
	void SetEvent(CallBack fn) { _event = fn; }

private:
	shared_ptr<RectCollider> _col;
	shared_ptr<Transform> _quadTransform;
	shared_ptr<Quad> _quad;

	CallBack _event;

	shared_ptr<ButtonBuffer> _buttonBuffer;
};

