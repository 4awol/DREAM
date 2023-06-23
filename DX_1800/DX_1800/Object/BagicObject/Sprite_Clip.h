#pragma once
class Sprite_Clip : public Sprite
{
public:
	Sprite_Clip(wstring path); // Frame  별로 잘 나눠어져있을 때
	Sprite_Clip(wstring path, Vector2 size);  // Action을 이용하여 클립으로 세팅할 때
	virtual ~Sprite_Clip();

	virtual void Update() override;
	virtual void Render() override;

	void SetCurClip(Action::Clip clip);

private:
};

