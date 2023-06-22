#pragma once
class Action
{
public:
	struct Clip // Clip 스프라이트의 하나하나 장면 스타트포스와 한칸의 크기를 담아놓는다.
 	{
		Vector2 startPos;
		Vector2 size;
		weak_ptr<SRV> srv;

		Clip(float x, float y, float w, float h, shared_ptr<SRV> srv)
			: startPos(x,y)
			, size(w,h)
			, srv(srv)
		{

		}
	};

	enum Type
	{
		END, // 한번만 실행
		LOOP, // 끝에서 처음으로
		PINGPONG // 왼오 왼오
	};
	
	Action(vector<Clip> clips, string name = "", Type type = Type::LOOP, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	Clip GetCurClip() { return _clips[_curClipIndex]; }

	void SetEndEvent(CallBack event_) //  event_ = &SpriteScene::EndEvent,this
	{
		_endEvent = event_;
	}

	void SetEndEventNumber(CallBackInt event2)
	{
		_endEventNumber = event2;
	}

private:
	string _name;
	vector<Clip> _clips;

	Type _repeatType;
	bool _isPlay = false;

	UINT _curClipIndex = 0;

	float _time = 0.0f;
	float _speed = 0.0f;

	bool _isReverse = false;


	// 리스너 패턴, 옵저버 패턴
	// =>  Delegate
	CallBack _endEvent = nullptr;
	CallBackInt _endEventNumber = 0;

	//class SpriteScene;
	//typedef void(SpriteScene::* FN)(void);
	//
	//FN _spriteSceneFN;
};

