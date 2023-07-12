#pragma once
class DunScene : public Scene
{
public:
	DunScene();
	~DunScene();
	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CameraShake();

	

private:
	shared_ptr<class Button> _button;

	shared_ptr<class MainScene> _main;


	shared_ptr<class stage_1> _st1;
};

