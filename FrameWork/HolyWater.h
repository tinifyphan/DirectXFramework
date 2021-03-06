#pragma once
#include"Weapon.h"
#include"Animation.h"
#include"StopWatch.h"
#include"define.h"
#define HOLYWATER_SPEED GVector2(250,150)
class HolyWater : public Weapon
{
public:
	HolyWater(GVector2 startPosition, eItemType type, eDirection dir = eDirection::NONE);
	~HolyWater();

	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;

	virtual float checkCollisionWeapon(BaseObject* object, float dt) override;

	//virtual float checkCollision(BaseObject* object, float dt) override;
	virtual void initWeaponComponent() override;
protected:
	Animation*	_burstAnimation;
	Animation*	_throwAnimation;
	StopWatch*	_burstStopWatch;
};

