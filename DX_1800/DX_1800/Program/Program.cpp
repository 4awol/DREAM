#include "framework.h"
#include "Program.h"

#include "../Scene/BagicScene/TutorialScene.h"
#include "../Scene/BagicScene/SolarSystem.h"
#include "../Scene/BagicScene/DunGreedScene.h"
#include "../Scene/BagicScene/ColliderScene.h"
#include "../Scene/BagicScene/SpriteScene.h"
#include "../Scene/BagicScene/ZeldaScene.h"
#include "../Scene/BagicScene/CupHeadScene.h"

Program::Program()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	_curScene = make_shared<CupHeadScene>();

	_view = make_shared<MatrixBuffer>();
	_proj = make_shared<MatrixBuffer>();

	_view->Update_Resource();

	XMMATRIX temp = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);

	_proj->SetData(temp);
	_proj->Update_Resource();

	Timer::GetInstance()->LockFPS(60);
}

Program::~Program()
{
}

void Program::Update()
{
	Timer::GetInstance()->Update();
	InputManager::GetInstance()->Update();
	_curScene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear();

	_view->SetVS_Buffer(1);
	_proj->SetVS_Buffer(2);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA->SetState();
	_curScene->Render();

	ImGui::Text("FPS : %d", FPS);
	ImGui::Text("DeltaTime : %1f", DELTA_TIME);
	ImGui::Text("RunTime : %1f", RUN_TIME);
	_curScene->PostRender();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::GetInstance()->Present();
}
