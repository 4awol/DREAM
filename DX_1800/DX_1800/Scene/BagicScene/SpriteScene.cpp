#include "framework.h"
#include "SpriteScene.h"

SpriteScene::SpriteScene()
{
	CreateAction();
	_sprite = make_shared<Sprite_Clip>(L"Resource/Texture/zelda.png", Vector2(200,200));
	_transform = make_shared<Transform>();
	_transform->SetPosition(CENTER);
}

SpriteScene::~SpriteScene()
{
}

void SpriteScene::Update()
{
	_transform->Update();
	_action->Update();
	_sprite->SetCurClip(_action->GetCurClip());
	_sprite->Update();
}

void SpriteScene::Render()
{
	_transform->SetWorldBuffer(0);
	_sprite->Render();
}

void SpriteScene::PostRender()
{
	ImGui::SliderFloat2("CurFrame", (float*)&_curFrame.x, 0, 10, "%.0f");
	ImGui::Text(_event.c_str());
	ImGui::Text("EventNumber : %d", _eventNumber);

	//_sprite->SetCurFrame(_curFrame);
}

void SpriteScene::CreateAction()
{
	vector<Action::Clip> clips;
	shared_ptr<SRV> srv = ADD_SRV(L"Resource/Texture/zelda.png");
	Vector2 imageSize = srv->GetImageSize();
	Vector2 maxFrame = Vector2(10,8);
	Vector2 size;
	size.x = imageSize.x / maxFrame.x;
	size.y = imageSize.y / maxFrame.y;

	// ¶Ù´Â ¸ð¼Ç 1
	for(int i = 0; i < 10; i++)
	{
		Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x , imageSize.y * 4.0f / maxFrame.y);
		Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
		clips.push_back(clip);
	}

	_action = make_shared<Action>(clips, "F_RUN", Action::END);
	_action->Play();
	_action->SetEndEvent(std::bind([this]()->void { this->_event = "END!!!"; }));
}
