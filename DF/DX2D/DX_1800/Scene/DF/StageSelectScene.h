#pragma once
class StageSelectScene : public Scene
{
private:
	StageSelectScene();
	~StageSelectScene();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new StageSelectScene();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static StageSelectScene& Instance()
	{
		static StageSelectScene instance;
		return instance;
	}
	
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Get_st1_trans() { _st1_trans; }
	void Get_St1_col() { _st1_col; }

	bool _selectScene_OnAir = false;
	int SelectStage = 0;

	void IsCollision();

private:
	UINT _poolCount = 100;
	static StageSelectScene* _instance;

	shared_ptr<Transform> _st1_trans;
	shared_ptr<RectCollider> _st1_col;

	shared_ptr<Transform> _callInvenTrans;
	shared_ptr<RectCollider> _callInvenCol;
	shared_ptr<Quad> _callInvenQuad;

	shared_ptr<ButtonBuffer> _buttonBuffer;

	
};

