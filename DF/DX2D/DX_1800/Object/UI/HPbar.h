#pragma once
class HPbar
{
public:
	HPbar();
	~HPbar();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos) { _quadTransform->SetPosition(pos); }
	void SetEvent(CallBack fn) { _event = fn; }


private:
	shared_ptr<Transform> _quadTransform;
	shared_ptr<Quad> _quad;

	shared_ptr<HPbarBuffer> _buffer;

	CallBack _event;
};

