﻿#include "Texture.h"

_USING_FRAMEWORK

Texture::Texture()
{
	_color = C_WHITE;
	_texture = nullptr;
}

Texture::~Texture()
{}


void Texture::release()
{
	this->_texture->Release();
}

HRESULT Texture::loadFromFile(LPD3DXSPRITE spriteHandle, LPWSTR filePath, D3DXCOLOR color, D3DXCOLOR colorkey) 
{
	HRESULT	result;

	result = D3DXGetImageInfoFromFile(filePath, &this->_imageInfo);
	if (result != D3D_OK)
	{
		return result;
	}

	LPDIRECT3DDEVICE9 _device = DeviceManager::getInstance()->getDevice();
	spriteHandle->GetDevice(&_device);

	result = D3DXCreateTextureFromFileEx(
		_device,
		filePath,
		this->_imageInfo.Width,
		this->_imageInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorkey,
		&this->_imageInfo,
		nullptr,
		&this->_texture);

	_color = color;

	return result;
}

void Texture::render(LPD3DXSPRITE spriteHandle, const RECT* rect, const GVector3* center, const GVector3* position)
{
	spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);
	spriteHandle->Draw(
		this->_texture,
		rect,
		center,
		position,
		_color
	);
	spriteHandle->End();
}

void Texture::render(LPD3DXSPRITE spriteHandle, RECT* srcRect, Viewport viewport, GVector2 position,
	GVector2 scale, float rotate, GVector2 origin, float zIndex)
{
	GVector3 positionViewport;
	positionViewport = viewport.getPositionInViewport(&GVector3(position.x, position.y, zIndex));
	//ép kiêu về int. để tránh trường hợp bị hụt pixel 
	render(spriteHandle, srcRect, GVector2((int)positionViewport.x, (int)positionViewport.y), scale, rotate, origin, positionViewport.z);
}

void Texture::render(LPD3DXSPRITE spriteHandle, RECT* srcRect, GVector2 position,
	GVector2 scale, float rotate, GVector2 origin, float zIndex)
{
	D3DXMATRIX matFinal;
	D3DXMATRIX matTransformed;
	D3DXMATRIX matOld;

	//origin postion
	GVector3 center = GVector3(abs(srcRect->right - srcRect->left) * origin.x, abs(srcRect->top - srcRect->bottom)
		* (1 - origin.y), zIndex);
	//get matrix texture
	spriteHandle->GetTransform(&matOld);

	D3DXMatrixTransformation2D(
		&matTransformed,
		&position,
		0.0f,
		&scale,
		&position,
		D3DXToRadian(rotate),
		0
		);

	matFinal = matTransformed * matOld;

	//set matrix transform
	spriteHandle->SetTransform(&matFinal);

	//Vẽ
	spriteHandle->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DONOTSAVESTATE);

	spriteHandle->Draw(
		this->_texture,
		srcRect,
		&center,
		&GVector3(position.x, position.y, zIndex),
		_color);

	spriteHandle->SetTransform(&matOld);

	spriteHandle->End();
}

void Texture::setColor(D3DXCOLOR color)
{
	this->_color = color;
}

D3DXCOLOR Texture::getColor()
{
	return _color;
}


int Texture::getWidth()
{
	return this->_imageInfo.Width;
}

int Texture::getHeight()
{
	return this->_imageInfo.Height;
}