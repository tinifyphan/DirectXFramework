﻿#include "Game.h"
using namespace std;
_USING_FRAMEWORK

int Game::isExit = 0;
Graphics* Game::hWindow = NULL;
Graphics* Game::getWindow()
{
	return hWindow;
}

void Game::exit()
{
	isExit = 1;
}
Game::Game()
{

}


Game::~Game()
{//dùng release
}


Game::Game(HINSTANCE hInstance, LPWSTR name, int width , int height,int fps, int isFullScreen)
{
	hWindow = new Graphics(hInstance,name,width,height,fps,isFullScreen);
	_gameTime = GameTime::getInstance();
	_deviceManager = DeviceManager::getInstance();
	_input = InputController::getInstance();
	_spriteHandler = NULL;
}
//init your objects
void Game::init()
{
	if (hWindow == NULL)
		throw;
	hWindow->InitWindow();
	_gameTime->init();
	_deviceManager->Init(*hWindow);
	_input->init(hWindow->getWnd(), hWindow->gethInstance());
	this->_frameRate = 1000.0f / hWindow->getFrameRate();//1000/30 = 33 milisecond

	HRESULT result = D3DXCreateSprite(_deviceManager->getDevice(), &this->_spriteHandler);
	if (result != D3D_OK)
	{
		MessageBox(hWindow->getWnd(), L"Error",L"Error",NULL);
	}
	//override in inheritance game class
	this->loadResource();

	//lấy
	_oldTime = _gameTime->getTotalGameTime();
	_deltaTime = 0.0f;
}

void Game::run()
{
	MSG msg;
	while (isExit == 0)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isExit = 1;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//Tăng thời gian của game chạy lên
		_gameTime->updateGameTime();
		//_deltaTime được tính theo milisecond
		//_frameRate là 33.3 milisecond
		_deltaTime = _gameTime->getTotalGameTime() - _oldTime;

		//Nếu _deltaTime >= _frameRate
		if (_deltaTime >= _frameRate)
		{
			_oldTime += _frameRate;
			_input->update();
			this->render();
		}
		else
			Sleep(_frameRate - _deltaTime);
	}
}

void Game::render()
{
	//kiểm tra cửa sổ đang focus
	if (GetActiveWindow() != hWindow->getWnd())
		return;
	auto device = _deviceManager->getInstance();
	float time = _gameTime->getElapsedGameTime();

	//để xử lý kéo cửa sổ không bị dồn frame
	//vì chỉ là thủ thuật set cứng thời gian
	//nên bất kỳ đối tượng nào không update theo thời gian thì khi kéo cửa sổ sẽ bị dồn frame
	if (time > this->_frameRate * 2)
	{
		time = _frameRate;
	}

	device->getDevice()->BeginScene();

	device->clearScreen();

	updateInput(time);
	update(time);
	draw();

	device->getDevice()->EndScene();
	device->present();

}

void Game::release()
{
	_deviceManager->release();
	_gameTime->release();
	//_input->release();
}

void Game::draw()
{
	//để lớp con implement
}		

void Game::loadResource()
{
	//để lớp con implement
}

void Game::updateInput(float deltaTime)
{
	//để lớp con implement
}

void Game::update(float deltaTime)
{
	//để lớp con implement
}



