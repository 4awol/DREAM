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
	document->LoadFile(xmlPath.c_str()); // .c_str()  첫번째 위치주소를 const char로 변환한것

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement(); // document의 첫번째 자식의 주소로 받는다.
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	vector < Action::Clip> clips;

	while (true)
	{
		if (row == nullptr)
			return;

		int x = row->FindAttribute("x")->IntValue(); //row의 요소 "x"를 int값으로 만들어주겠다.
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("y")->IntValue();
		int h = row->FindAttribute("h")->IntValue();

		Action::Clip clip = Action::Clip(x, y, w, h , srv);
		clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	// 액션 만들기

	shared_ptr<Action> action = make_shared<Action>();

}
