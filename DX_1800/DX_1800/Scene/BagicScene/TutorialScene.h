#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Transform> _trans;
	shared_ptr<Quad> _quad;

	shared_ptr<FilterBuffer> _filterBuffer;
};

