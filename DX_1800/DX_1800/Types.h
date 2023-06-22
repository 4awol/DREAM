#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER			 Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)
#define UP_VECTOR		 Vector2(0.0f, 1.0f)
#define RIGHT_VECTOR	 Vector2(1.0f, 0.0f)

#define PI 3.141592

#define RED			{1.0f,0.0f,0.0f,1.0f}
#define GREEN		{0.0f,1.0f,0.0f,1.0f}
#define BLUE		{0.0f,0.0f,1.0f,1.0f}

#define DEVICE	Device::GetInstance()->GetDevice()
#define DC		Device::GetInstance()->GetDC()

#define ALPHA		StateManager::GetInstance()->GetAlpha()
#define ADDITIVE	StateManager::GetInstance()->GetAdditive()
#define BLEND		StateManager::GetInstance()->GetBlend()
#define SAMPLER		StateManager::GetInstance()->GetSampler()

#define ADD_SRV(k)		SRVManager::GetInstance()->AddSRV(k)

#define KEY_UP(k)			InputManager::GetInstance()->Up(k)
#define KEY_DOWN(k)			InputManager::GetInstance()->Down(k)
#define KEY_PRESS(k)		InputManager::GetInstance()->Press(k)
#define MOUSE_POS			InputManager::GetInstance()->GetMousePos()

#define DELTA_TIME			Timer::GetInstance()->GetDeltaTime()
#define RUN_TIME			Timer::GetInstance()->GetRunTime()
#define FPS					Timer::GetInstance()->GetFPS()

using CallBack = function<void()>; // 반환형식이 void이고 매개변수없는 얘들만 담을수 있음
using CallBackInt = function<void(int)>;

#define LERP(s,e,t)			 s + (e - s) * t