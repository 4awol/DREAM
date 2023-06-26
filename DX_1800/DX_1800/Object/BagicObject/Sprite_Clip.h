#pragma once
class Sprite_Clip : public Sprite
{
public:
	Sprite_Clip(wstring path);
	Sprite_Clip(wstring path, Vector2 size);
	virtual ~Sprite_Clip();

	virtual void Update() override;
	virtual void Render() override;

	void SetCurClip(Action::Clip clip);

private:

};

