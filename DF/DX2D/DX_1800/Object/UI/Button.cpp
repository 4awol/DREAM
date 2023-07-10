#include "framework.h"
#include "Button.h"

Button::Button(wstring path, Vector2 size)
{
	_quad = make_shared<Quad>(path, size);
	_quad->SetPS(ADD_PS(L"Shader/ButtonPS.hlsl"));
	_quadTransform = make_shared<Transform>();

	_col = make_shared<RectCollider>(size);

	_quadTransform->SetParent(_col->GetTransform());

	_buttonBuffer = make_shared<ButtonBuffer>();
	_buttonBuffer->_data.hover = 0.2f;
	_buttonBuffer->_data.click = 0.5f;
}

Button::~Button()
{
}

void Button::Update()
{
	_col->Update();
	_quadTransform->Update();

	if (_col->IsCollision(S_MOUSE_POS))
	{
		_buttonBuffer->_data.state = 1;

		if (KEY_DOWN(VK_LBUTTON))
		{
			if (_event != nullptr)
				_event();
		}

		if (KEY_PRESS(VK_LBUTTON))
		{
			_buttonBuffer->_data.state = 2;
		}

		_col->SetColorRed();
	}
	else
	{
		_buttonBuffer->_data.state = 0;
		_col->SetColorGreen();
	}

	_buttonBuffer->Update_Resource();
}

void Button::PostRender()
{
	_quadTransform->SetWorldBuffer(0);
	_buttonBuffer->SetPS_Buffer(0);
	_quad->Render();
	_col->Render();
}
