#pragma once
class LineScene : public Scene
{
public:
	LineScene();
	virtual ~LineScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	shared_ptr<Line> _floorLine;
	shared_ptr<Line> _mouseLine;
	shared_ptr<Line> _shadowLine;
};

