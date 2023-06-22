#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring path, Vector2 maxFrame);
	Sprite(wstring path, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;
	virtual void CreateData(wstring path) override;

	void SetCurFrame(Vector2 frame) { _frameBuffer->_data.curFrame = frame; }
	void SetCurFrame(Action::Clip clip);

private:
	shared_ptr<FrameBuffer> _frameBuffer;

	Vector2 _maxFrame;
};

