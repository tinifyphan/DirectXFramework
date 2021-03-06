#pragma once
#include"Item.h"
#include"Score.h"
#include"Animation.h"
class CrystalBall : public Item
{
public:
	CrystalBall(GVector2 startPosition, eItemID id = eItemID::CRYSTALBALL);
	~CrystalBall();
	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	virtual float checkCollision(BaseObject* object, float dt);
	virtual void pickedUp() override;
private:
	Animation* _animation;
	GVector2 _endPosition;
	bool _stop;
};

