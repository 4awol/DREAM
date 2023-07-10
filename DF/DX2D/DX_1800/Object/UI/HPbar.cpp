#include "framework.h"
#include "HPbar.h"

HPbar::HPbar()
{
	_quadTransform = make_shared<Transform>();
	_quad = make_shared <Quad>( L"Resource/UI/Button.png", Vector2(100,30));

	_buffer = make_shared<HPbarBuffer>();
	_buffer->_data.ratio = 1;
}

HPbar::~HPbar()
{
}

void HPbar::Update()
{
	_quadTransform->Update();

	_buffer->Update_Resource();
}

void HPbar::PostRender()
{
	_quadTransform->SetWorldBuffer(0);
	_quad->Render();

	//_buffer->SetPS_Buffer()
}
