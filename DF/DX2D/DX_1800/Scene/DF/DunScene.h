#pragma once
class DunScene : public Scene
{
public:
	DunScene();
	~DunScene();
	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CameraShake();

	bool Main = true;
	bool Inven = false;
	bool St1 = false;

private:
	shared_ptr<class Button> _button;

	shared_ptr<class MainScene> _main;

	shared_ptr<class InvenScene> _inven;

	shared_ptr<class stage_1> _st1;
};

