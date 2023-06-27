#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	_quad = make_shared<Quad>(L"Resource/Texture/Winter.png");
	_trans = make_shared<Transform>();
	_quad->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));

	_trans->SetPosition(CENTER);
	_trans->SetScale(Vector2(0.5f, 0.5f));

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->_data.imageSize = _quad->GetImageSize();
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
	_trans->Update();
	_quad->Update();
	_filterBuffer->Update_Resource();
}

void TutorialScene::Render()
{
	_trans->SetWorldBuffer(0);
	_filterBuffer->SetPS_Buffer(0);
	_quad->Render();
}

void TutorialScene::PostRender()
{
	ImGui::SliderInt("selected", &_filterBuffer->_data.selected, 0, 5);
	ImGui::SliderInt("value1", &_filterBuffer->_data.value1, 0, 300);
	ImGui::SliderInt("value2", &_filterBuffer->_data.value2, 0, 300);
	ImGui::SliderInt("value3", &_filterBuffer->_data.value3, 0, 300);
}
