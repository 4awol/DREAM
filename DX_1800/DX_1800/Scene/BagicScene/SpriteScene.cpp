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
	ImGui::Text(_event.c_str()); // �ִϸ��̼��� ������ EndEvent�� ��µ� �� �ֵ���! ->  CALLBACK �Լ�
	ImGui::Text("EventNumber: %d", _eventNumber);
	//_sprite->SetCurFrame(_curFrame);
}

void SpriteScene::CreateAction()
{
	vector<Action::Clip> clips;
	shared_ptr<SRV> srv = ADD_SRV(L"Resource/Texture/zelda.png");
	Vector2 imageSize = srv->GetImageSize(); // ��������Ʈ�� �����Ǿ��ִ� �ϳ��� ū �̹����� ������ 
										// 0,0 �������� ����� �� �ִ�ũ�⸦ ������ ����
	Vector2 maxFrame = Vector2(10, 8);
	Vector2 size;
	size.x = imageSize.x / maxFrame.x;
	size.y = imageSize.y / maxFrame.y;

	// �ٴ� ��� 1
	for (int i = 0; i < maxFrame.x; i++)
	{
		Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 4.0f / maxFrame.y);
		Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
		clips.push_back(clip);
	}

	_action = make_shared<Action>(clips, "F_RUN", Action::END);
	_action->Play();
	_action->SetEndEvent(std::bind(&SpriteScene::EndEvent, this)); // Action.cpp �� CallBack _endEvent�� nullptr�� �ƴϰ� �ȴ�.
									// �׼���  SpriteScene �� �ִ� EndEvent  �� ȣ���ϴ� ����

	_action->SetEndEvent(std::bind([this]()->void {this->_event = "END!!"; })); // ���� �Լ�

	_action->SetEndEventNumber(std::bind(&SpriteScene::EndEventNumber, this, std::placeholders::_1));
}
	