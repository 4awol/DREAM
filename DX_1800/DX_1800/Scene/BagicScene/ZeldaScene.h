#pragma once
class ZeldaScene : public Scene
{
public:
	ZeldaScene();
	virtual ~ZeldaScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<class Zelda> _zelda;
};

