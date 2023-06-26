#pragma once
class SpriteScene : public Scene
{
public:
	SpriteScene();
	virtual ~SpriteScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateAction();

	void EndEvent() { _event = "END!!!"; }
	// 액션이 끝나면 _eventNumber는 5로 만들고 싶다.
	void EndEventNumber(int num) { _eventNumber = num; }

private:
	string _event = "Not End";
	int _eventNumber = 0;

	shared_ptr<Transform> _transform;
	shared_ptr<Sprite_Clip> _sprite;
	shared_ptr<Action> _action;

	Vector2 _curFrame;
};

