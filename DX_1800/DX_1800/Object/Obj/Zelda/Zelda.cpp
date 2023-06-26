#include "framework.h"
#include "Zelda.h"

Zelda::Zelda()
{
	_transform = make_shared<Transform>();
	_sprite= make_shared<Sprite_Clip>(L"Resource/Texture/zelda.png", Vector2(50,50));

	_transform->SetPosition(Vector2(50,50));

	CreateActions();
	_actions[State::IDLE_F]->Play();
}

Zelda::~Zelda()
{
}

void Zelda::Update()
{
	for(auto action : _actions)
		action->Update();

	_transform->Update();
	_sprite->SetCurClip(_actions[_state]->GetCurClip());
	_sprite->Update();
}

void Zelda::Render()
{
	_transform->SetWorldBuffer(0);
	_sprite->Render();
}

void Zelda::Input()
{
}

void Zelda::CreateActions()
{
	shared_ptr<SRV> srv = ADD_SRV(L"Resource/Texture/zelda.png");
	Vector2 imageSize = srv->GetImageSize();
	Vector2 maxFrame = Vector2(10, 8);
	Vector2 size;
	size.x = imageSize.x / maxFrame.x;
	size.y = imageSize.y / maxFrame.y;


	// IDLE_F
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 3; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 0.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "IDLE_F", Action::LOOP);
		_actions.push_back(action);
	}

	// IDLE_L
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 3; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 1.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "IDLE_L", Action::LOOP);
		_actions.push_back(action);
	}

	// IDLE_B
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 1; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 2.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "IDLE_B", Action::LOOP);
		_actions.push_back(action);
	}

	// IDLE_R
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 3; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 3.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "IDLE_R", Action::LOOP);
		_actions.push_back(action);
	}

	// RUN_F
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 10; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 4.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "RUN_F", Action::LOOP);
		_actions.push_back(action);
	}

	// RUN_L
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 10; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 5.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "RUN_L", Action::LOOP);
		_actions.push_back(action);
	}

	// RUN_B
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 10; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 6.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "RUN_B", Action::LOOP);
		_actions.push_back(action);
	}

	// RUN_R
	{
		vector<Action::Clip> clips;
		for (int i = 0; i < 10; i++)
		{
			Vector2 startPos = Vector2((i * imageSize.x) / maxFrame.x, imageSize.y * 7.0f / maxFrame.y);
			Action::Clip clip = Action::Clip(startPos.x, startPos.y, size.x, size.y, srv);
			clips.push_back(clip);
		}

		shared_ptr<Action> action = make_shared<Action>(clips, "RUN_R", Action::LOOP);
		_actions.push_back(action);
	}
}
