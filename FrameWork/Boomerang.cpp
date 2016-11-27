#include "Boomerang.h"


Boomerang::Boomerang(GVector2 startPosition, eItemType type, eDirection dir) : Weapon(startPosition, type, dir, eItemID::BOORMERANG)
{
}


Boomerang::~Boomerang()
{
}


void Boomerang::init()
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::ITEM);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::ITEM, "boomerang_flying"));

	if (_type == eItemType::PICKED_UP)
		HeartCounter::plusHeart(-1);

	Weapon::initCommonComponent();

	initWeaponComponent();
}


void Boomerang::update(float deltatime)
{
	Weapon::update(deltatime);
	if (!_isFliedBack)
	{
		if (abs(this->getPositionX() - this->_startPosition.x) > BOORMERANG_DISTANCE.x)
		{
			GVector2 veloc = GVector2(-this->getVelocity().x,this->getVelocity().y);

			auto move = (Movement*)this->_componentList["Movement"];
			move->setVelocity(veloc);

			this->_startPosition = this->getPosition();

			_isFliedBack = true;
		}
	}
	else
	{
		if (abs(this->getPositionX() - this->_startPosition.x) > BOORMERANG_DISTANCE.x)
			this->setStatus(eStatus::DESTROY);
	}
}

void Boomerang::draw(LPD3DXSPRITE spriteHandler, Viewport* viewport)
{
	Weapon::draw(spriteHandler, viewport);
}

void Boomerang::release()
{

}

void Boomerang::initWeaponComponent()
{
	if (_type != eItemType::PICKED_UP) return;

	GVector2 veloc = this->initVeloc(BOORMERANG_SPEED);

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(veloc);

	auto gravity = (Gravity*)this->_componentList["Gravity"];
	gravity->setStatus(eGravityStatus::SHALLOWED);
	gravity->setGravity(GVector2Zero);

	RotateMovement* rotateMovement = new RotateMovement(_sprite);
	_componentList["RotateMovement"] = rotateMovement;
}

float Boomerang::checkCollision(BaseObject* otherObject, float dt)
{
	if (_type == eItemType::DROP)
	{
		Weapon::checkCollision(otherObject, dt);
	}
	return 0.0f;
}