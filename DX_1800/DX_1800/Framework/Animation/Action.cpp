#include "framework.h"
#include "Action.h"

Action::Action(vector<Clip> clips, string name, Type type, float speed)
	: _clips(clips)
	, _repeatType(type)
	, _name(name)
	, _speed(speed)
{

}

Action::~Action()
{
}

void Action::Update()
{
	if(_isPlay == false)
		return;

	_time += DELTA_TIME;

	if (_time > _speed)
	{
		_time = 0.0f;

		switch (_repeatType) // __repeat
		{
		case Action::END:
		{
			_curClipIndex++;
			if (_curClipIndex >= _clips.size())
				Stop();
		}
			break;
		case Action::LOOP:
		{
			_curClipIndex++;
			_curClipIndex %= _clips.size(); // ���� _curClipSize�� _clip �� ����� �Ѿ�� �ٽ� 1���� �����ϱ� ������ �������� ���� ����
		}
			break;
		case Action::PINGPONG:
		{
			if (_isReverse) // ���� _isReverse�� true���?
			{
				_curClipIndex--;
				if (_curClipIndex <= 0)
					_isReverse = false;
			}
			else
			{
				_curClipIndex++;
				if (_curClipIndex >= _clips.size() - 1)
					_isReverse = true;
			}
		}
			break;
		default:
			break;
		}
	}
}

void Action::Play()
{
	_isPlay = true;
	_isReverse = false; //bool _isReverse = false;
	_time = 0.0f;

}

void Action::Pause()
{
	_isPlay = true;
}

void Action::Stop()
{
	_isPlay = false;
	_time = 0.0f;
	_curClipIndex = 0;

	if (_endEvent != nullptr)
		_endEvent();
	if (_endEventNumber != nullptr)
		_endEventNumber(5);
	//if (_spriteSceneFN != nullptr)
	//	_spriteSceneFN();
}

void Action::Reset()
{
	_isPlay = false;
	_curClipIndex = 0;
	_time = 0.0f;
}
