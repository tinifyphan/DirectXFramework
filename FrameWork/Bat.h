﻿#pragma once

#include "Animation.h"
#include "IComponent.h"
#include "BaseEnemy.h"
#include "StopWatch.h"

#define BAT_SPEED 50
#define BAT_HITPOINT 1
#define BAT_SCORE 100

class Bat : public BaseEnemy {
public:
	/*
	@status: HANGING,FLYING
	@pos: Vị trí
	@direction: hướng chạy, -1 là bên trái, 1 là bên phải
	@x, y: tọa độ của pos
	*/
	Bat(eStatus status, GVector2 pos, int direction);
	Bat(eStatus status, float x, float y, int direction);
	/* Contructor:
	* @pos: vị trí bắt đầu.
	* @hVeloc: vận tốc tuyến tính, tạo một phần chuyển động thăng.
	* @ampl: biên độ của chuyển động tuần hoàn.
	* @freq: tần số góc của chuyển động tuần hoàn.
	*/
	Bat(eStatus status,  int direction, GVector2 pos, GVector2 hVeloc, GVector2 ampl, float freq);
	~Bat();

	void init();
	void update(float);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();
	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);
	void die();
	void setPosition(GVector2);
	GVector2 getVelocity();
	IComponent* getComponent(string);

private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	BaseObject* prevObject;

	void changeDirection();

	// Init values
	GVector2	_beginPosition;
	GVector2	_horizontalVeloc;
	GVector2	_amplitude;
	float		_frequence;
	bool		_verticalflag;

	void checkIfOutOfScreen();
	void updateHanging();

};