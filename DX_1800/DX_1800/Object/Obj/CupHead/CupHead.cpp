#include "framework.h"
#include "CupHead.h"

//#include "../../../Framework/Utility/tinyxml2.h"

CupHead::CupHead()
{
	_transform = make_shared<Transform>();
	_col = make_shared<CircleCollider>(50);
}

CupHead::~CupHead()
{
}

void CupHead::Update()
{
}

void CupHead::Render()
{
}

void CupHead::PostRender()
{
}

void CupHead::CreateAction(string name, float speed, Action::Type type, CallBack callBack)
{
	string xmlPath = "Resource/CupHead" + name + "xml";
	wstring wName = wstring(name.begin(), name.end());
	wstring srvPath = L"Resource/CupHead" + wName + L"png";
	shared_ptr<SRV> srv = ADD_SRV(wName);

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str()); // .c_str()  ù��° ��ġ�ּҸ� const char�� ��ȯ�Ѱ�

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement(); // document�� ù��° �ڽ��� �ּҷ� �޴´�.
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector < Action::Clip> clips;

	while (true)
	{
		if (row == nullptr)
			return;

		int x = row->FindAttribute("x")->IntValue(); //row�� ��� "x"�� int������ ������ְڴ�.
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("y")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h , srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	// �׼� �����

	shared_ptr<Action> action = make_shared<Action>();

}
