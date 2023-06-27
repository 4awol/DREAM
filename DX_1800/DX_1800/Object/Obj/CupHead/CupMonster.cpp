#include "framework.h"
#include "CupMonster.h"

CupMonster::CupMonster()
{
	_col = make_shared<RectCollider>(Vector2(300, 700));
	_transform = make_shared<Transform>();

	CreateAction("mons", 0.1f, Action::Type::PINGPONG, nullptr);

	_col->GetTransform()->SetPosition(Vector2(1000, 400));

	_transform->SetParent(_col->GetTransform());

	_actions[State::IDLE]->Play();


}

CupMonster::~CupMonster()
{
}

void CupMonster::Update()
{
	_col->Update();
	_transform->Update();
	_actions[_curState]->Update();
	_sprites[_curState]->SetCurClip(_actions[_curState]->GetCurClip());
	_sprites[_curState]->Update();
}

void CupMonster::Render()
{
	_transform->SetWorldBuffer(0);
	_sprites[_curState]->Render();

	_col->Render();
}

void CupMonster::Collider(RectCollider _col)
{

}

void CupMonster::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
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

	shared_ptr<Action> action = make_shared<Action>(clips, name, type, speed);
	action->SetEndEvent(callBack);

	_actions.push_back(action);

	shared_ptr<Sprite_Clip> sprite = make_shared<Sprite_Clip>(srvPath, Vector2(averageW / count, averageH / count));
	_sprites.push_back(sprite);
}
