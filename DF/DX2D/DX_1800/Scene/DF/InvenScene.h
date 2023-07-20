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

	 vector<vector<shared_ptr<RectCollider>>>& GetRectCol()  
	{
		return _rectCol;
	}
private:
	
	static InvenScene* _instance;

	vector<vector<shared_ptr<RectCollider>>> _rectCol;

	shared_ptr<Transform> _listTrans;
	shared_ptr<RectCollider> _listCol;

	shared_ptr<Transform> _playerwearTrans;
	shared_ptr<RectCollider> _playerwearCol;
	shared_ptr<Quad> _playerwearQuad;

	shared_ptr<Transform> _headTrans;
	shared_ptr<RectCollider> _headCol;
	shared_ptr<Quad> _headQuad;

	shared_ptr<Transform> _armorTrans;
	shared_ptr<RectCollider> _armorCol;
	shared_ptr<Quad> _armorQuad;

	shared_ptr<Transform> _weaponTrans;
	shared_ptr<RectCollider> _weaponCol;
	shared_ptr<Quad> _weaponQuad;

	shared_ptr<Transform> _bootsTrans;
	shared_ptr<RectCollider> _bootsCol;
	shared_ptr<Quad> _bootsQuad;

	shared_ptr<Transform> _nextButtonTrans;
	shared_ptr<RectCollider> _nextButtonCol;
	shared_ptr<Quad> _nextButtonQuad;

};

