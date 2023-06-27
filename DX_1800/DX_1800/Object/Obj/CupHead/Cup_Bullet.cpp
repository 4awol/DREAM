#include "framework.h"
#include "Cup_Bullet.h"

Cup_Bullet::Cup_Bullet()
{
	CreateAction("Bullet_Loop");
	_action->Play();

	Vector2 size = _sprite->GetClipSize();

	_col = make_shared<CircleCollider>(10.0f);
	_transform = make_shared<Transform>();

	_transform->SetParent(_col->GetTransform());
	_transform->SetAngle(- PI * 0.5f);
	_transform->SetPosition(Vector2(-80.0f,0.0f));

	_col->GetTransform()->SetPosition(Vector2(-WIN_WIDTH * 5, -WIN_HEIGHT * 5));
	_isActive = false;

	_col->Update();
	_transform->Update();
}

Cup_Bullet::~Cup_Bullet()
{
}

void Cup_Bullet::Update()
{
	if(_isActive == false)
		return;

	_col->Update();
	_transform->Update();

	_action->Update();
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Update();

	_col->GetTransform()->AddVector2(_direction * _speed * DELTA_TIME);
}

void Cup_Bullet::Render()
{
	if(_isActive == false)
		return;

	_transform->SetWorldBuffer(0);
	_sprite->Render();
	_col->Render();
}

void Cup_Bullet::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/CupHead/" + wName + L".png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	string xmlPath = "Resource/CupHead/" + name + ".xml";
	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector<Action::Clip> clips;
	float averageW = 0;
	float averageH = 0;
	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;

		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		averageW += w;
		averageH += h;
		count++;

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	_action = make_shared<Action>(clips, name, type, speed);
	_action->SetEndEvent(callBack);

	_sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
}
