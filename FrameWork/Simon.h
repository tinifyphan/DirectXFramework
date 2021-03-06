﻿#pragma once
#include"define.h"
#include"Animation.h"
#include"InputController.h"
#include"BaseObject.h"
#include"IComponent.h"
#include"CollisionBody.h"
#include"Land.h"
#include"Stair.h"
#include"StopWatch.h"
#include"SceneManager.h"
#include"LifeUI.h"
#include"ActiveWeapon.h"
#include"Whip.h"
#include"SoundManager.h"
_NAMESPACE_FRAMEWORK_BEGIN
#define SIMON_MOVING_SPEED 120

#define GRAVITY 900
#define SIMON_JUMP_VELOCITY GVector2(85,380)
// Sửa phần lên cầu thang cho hết sida
#define SIMON_UPSTAIR_VELOCITY_X 46.8
#define SIMON_UPSTAIR_VELOCITY_Y 48
#define REVIVE_TIME 2000

[event_receiver(native)]
class Simon : public BaseObject,public IControlable
{
public:
	Simon();
	~Simon();
	//overiride IControlable method
	void updateInput(float dt);
	//overiride BaseObject methods
	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();

	/*
		Event for event_reciever
	*/
	void onKeyPressed(KeyEventArg* key_event);
	/*
		Event for event_reciever
	*/
	void onKeyReleased(KeyEventArg* key_event);

	void setStatus(eStatus status) override;

	/*
		Cập nhật lại trạng thái cho nhân vật
	*/
	void checkPosition();
	void updateStatus(float deltatime);
	/*
		CheckCollision
	*/
	float checkCollision(BaseObject* object, float dt);
	void onCollisionBegin(CollisionEventArg* collision_arg);
	void onCollisionEnd(CollisionEventArg* collision_arg);

	/*
		Cập nhật lại rect để vẽ 
	*/
	void updateCurrentAnimateIndex();

	// Character action.

	/*
		romve hết 2 trạng thái jump và falling của simon
		Nếu đứng trên cầu thang thì cho đứng
		ko thì remove luôn trạng thái đứng ở cầu thang
	*/
	void standing();
	void moveRight();
	void moveLeft();
	/*
		Trạng thái lúc object nhảy lên
	*/
	void jump();
	/*
		Trạng thái lúc objec rơi xuống
	*/
	void falling();
	void sit();
	void upstair();
	void downstair();
	void die();
	void revive();
	void hitting();
	void getWeapon();
	/*
		Hàm này được gọi khi enemy va chạm với simon
	*/
	void getHitted(int _dropHp = 1);
	//int getDamage();
	BaseObject* getWhip();
	void enableGravity(bool);

	float getMovingSpeed();

	RECT getBounding() override;
	
	eDirection getDirection();

	// Hàng để auto move
	void removeGravity();
	void forceMoveRight();
	void unforceMoveRight();
	void forceMoveLeft();
	void unforceMoveLeft();
	void forceJump();
	void unforceJump();
	void setFreeze(bool freeze);
	void protect(bool protect = true);
private:
	map<int, Animation*> _animations;
	map<string, IComponent*> _componentList;
	Whip* _whip;
	Animation* _whipAnimation;

	float _movingSpeed;

	bool _canJumpDown;
	bool _canOnStair;
	bool _canUpStair;
	//Nếu simon bị đóng băng thì ko cho phép bàn phím được hoạt động
	bool _isFreezed;
	//Sử dụng để animation hitting khi có stopwatch
	bool _isHitting;
	//Sử dụng để animation throwing khi có stopwatch
	bool _isThrowing;
	//Sử dụng để tạo flash lúc simon bị mất máu lên
	bool _isHitted;
	//Sử dụng để xem simon có được bảo vệ hay không
	bool _isProtected;
	//Hướng cầu thang đi lên qua phải hoặc đi lên qua trái
	eStairDirection _stairDirection;

	StopWatch* _stopWatch;
	StopWatch* _reviveStopWatch;
	StopWatch* _hittingStopWatch;
	StopWatch* _throwItemStopWatch;
	StopWatch* _isHittedStopWatch;
	StopWatch* _protectStopWatch;

	eStatus _currentAnimationIndex;

	GVector2 getVelocity();

	BaseObject* _preObject;
	// reset các thuộc tính lại giá trị ban đầu.
	void resetValues();
	void setPositionInStair(Stair* stair);
	void setPositionInLand(Land* land);
	void trackFlyLandPosition(float deltatime);
	BaseObject* _trackedFlyLand;

	void swapWeapon();
	void unhookInputEvent();
};
_NAMESPACE_FRAMEWORK_END

