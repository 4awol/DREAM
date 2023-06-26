#pragma once
class Sprite_Frame : public Sprite
{
public:
	// TODO: 분리하기
	Sprite_Frame(wstring path, Vector2 maxFrame);
	Sprite_Frame(wstring path, Vector2 maxFrame, Vector2 size);
	virtual ~Sprite_Frame();

	virtual void Update() override;
	virtual void Render() override;

	void SetCurClip(Vector2 frame);

private:
	Vector2 _maxFrame;
};

