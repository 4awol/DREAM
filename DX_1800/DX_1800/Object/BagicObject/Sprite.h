#pragma once
class Sprite : public Quad
{
protected:
	Sprite(wstring path); // Frame  별로 잘 나눠어져있을 때
	Sprite(wstring path, Vector2 size);  // Action을 이용하여 클립으로 세팅할 때
	virtual ~Sprite();

public:

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;
	virtual void CreateData(wstring path) override;

protected:
	shared_ptr<ActionBuffer> _actionBuffer;
};

