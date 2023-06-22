#pragma once
class DunGreedScene : public Scene
{
public:
	DunGreedScene();
	virtual ~DunGreedScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class DunPlayer> _player;
	shared_ptr<class DunMonster> _monster;
};

