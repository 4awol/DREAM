#include "framework.h"
#include "SpriteScene.h"

SpriteScene::SpriteScene()
{
	CreateAction();
	_sprite = make_shared<Sprite>(L"Resource/Texture/zelda.png", Vector2(10,8), Vector2(200,200));
	_transform = make_shared<Transform>();
	_transform->SetPosition(CENTER);

	_sprite->SetCurFrame(Vector2(0,1));
}

SpriteScene::~SpriteScene()
{
}

void SpriteScene::Update()
{
	_transform->Update();
	_sprite->Update();
	_sprite->SetCurFrame(_action->GetCurClip());
	_action->Update();
}

void SpriteScene::Render()
{
	_transform->SetWorldBuffer(0);
	_sprite->Render();
}

void SpriteScene::PostRender()
{
	ImGui::SliderFloat2("CurFrame", (float*)&_curFrame.x, 0, 10, "%.0f");
	ImGui::Text(_event.c_str()); // 애니매이션이 끝날때 EndEvent가 출력될 수 있도록! ->  CALLBACK 함수
	ImGui::Text("EventNumber: %d", _eventNumber);
	//_sprite->SetCurFrame(_curFrame);
}

void SpriteScene::CreateAction()
{
	vector<Action::Clip> clips;
	shared_ptr<SRV> srv = ADD_SRV(L"Resource/Texture/zelda.png");
	Vector2 imageSize = srv->GetImageSize(); // 스프라이트가 포진되어있는 하나의 큰 이미지의 사이즈 
										// 0,0 에서부터 사이즈가 됨 최대크기를 가지고 있음
	Vector2 maxFrame = Vector2(10, 8);
	Vector2 size;
	size.x = imageSize.x / maxFrame.x;
	size.y = imageSize.y / maxFrame.y;

	// 뛰는 모션 1
	for (int i = 0; i < maxFrame.x; i++)
	{
		Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 4.0f / maxFrame.y);
		Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
		clips.push_back(clip);
	}

	_action = make_shared<Action>(clips, "F_RUN", Action::END);
	_action->Play();
	_action->SetEndEvent(std::bind(&SpriteScene::EndEvent, this)); // Action.cpp 의 CallBack _endEvent가 nullptr이 아니게 된다.
									// 액션이  SpriteScene 에 있는 EndEvent  를 호출하는 거임

	_action->SetEndEvent(std::bind([this]()->void {this->_event = "END!!"; })); // 람다 함수

	_action->SetEndEventNumber(std::bind(&SpriteScene::EndEventNumber, this, std::placeholders::_1));
}
	