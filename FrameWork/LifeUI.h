#pragma once
#include"EmptyObject.h"
#include"Text.h"
#define GAP 3
#define MAX_LIFE_NUMBER 3
#define MAX_HP_NUMBER 16
class LifeUI : public EmptyObject
{
public:
	LifeUI(GVector2 position,string text,int lifeNumber,int HP = MAX_HP_NUMBER);
	~LifeUI();

	virtual void init();
	virtual void update(float deltatime);
	virtual void draw(LPD3DXSPRITE, Viewport*);
	virtual void release();

	void setLifeNumber(int number);
	int getLifeNumber();

	void setHPNumber(int HP);
	int getHPNumber();
private:
	Text* _text;
	vector<Sprite*> _listIcons;
	int _hp;
	int _life;
};

