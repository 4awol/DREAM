#pragma once
class InvenScene : public Scene
{
private:
	InvenScene();
	~InvenScene();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InvenScene();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	
	static InvenScene& Instance()
	{
		static InvenScene _instance;
			return _instance;
	}

	virtual void Update() override;
	virtual void Render() override;

	bool _inven_OnAir = false;

private:
	
	static InvenScene* _instance;

	shared_ptr<Transform> _trans;
	vector<vector<shared_ptr<RectCollider>>> _rectCol;

	shared_ptr<Transform> _listTrans;
	shared_ptr<RectCollider> _listCol;

	shared_ptr<RectCollider> _playerwearCol;
	shared_ptr<RectCollider> _headCol;
	shared_ptr<RectCollider> _armorCol;

	shared_ptr<Transform> _weaponTrans;
	shared_ptr<RectCollider> _weaponCol;
	shared_ptr<Quad> _weaponQuad;

	shared_ptr<RectCollider> _bootsCol;

	shared_ptr<Transform> _nextButtonTrans;
	shared_ptr<Quad> _nextButtonQuad;

};

