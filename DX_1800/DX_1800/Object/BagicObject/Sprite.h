#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring path, Vector2 maxFrame); // Frame  별로 잘 나눠어져있을 때
	Sprite(wstring path, Vector2 maxFrame, Vector2 size);  // Action을 이용하여 클립으로 세팅할 때
	virtual ~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;
	virtual void CreateData(wstring path) override;

	void SetCurClip(Vector2 frame);
	void SetCurClip(Action::Clip clip);

private:
	shared_ptr<ActionBuffer> _actionBuffer;

	Vector2 _maxFrame;
};

