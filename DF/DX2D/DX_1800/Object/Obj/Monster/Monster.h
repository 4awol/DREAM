#pragma once
class Monster
{
public:
	Monster() {}
	virtual ~Monster() {}

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PostRender() {}

private:
};

