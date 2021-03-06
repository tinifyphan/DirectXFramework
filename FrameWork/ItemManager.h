﻿#pragma once
#include"BaseObject.h"
#include"Item.h"
#include"define.h"
#include<list>

/*
*	ItemManager:
*			Là class dùng để quản lý các items trong game
*
*			Hàm update: gọi từng thành phần để update
*			Hàm draw: gọi từng thành phần để draw
*			Hàm checkcolision: gọi từng thành phần để check
*			Hàm release: giải phóng những đối tượng hết hiệu lực.
*
*	Cách sử dụng:
*		Được khởi tạo trong playscene, được gọi update, checkcollision, draw trong playscnee.
*		Khi enemy chết rớt ra thì gọi hàm :
*
*		ItemManger::insertItem(new Item(...));
*		và không cần thiết thực hiện bất kì câu lệnh nào khác.
*
*	Note:
*		Để xử lý va chạm với simon thì sử lý trên item
*/
class ItemManager : public BaseObject
{
public:
	ItemManager();
	~ItemManager();
	static void insertItem(Item* item);


	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();
	RECT getBounding();
	float checkCollision(BaseObject * object, float dt);
	static list<Item*> getListItem();
	static void generateItem(eItemID id, GVector2 pos,eItemType type = eItemType::DROP);
	static void generateWeapon(eItemID id, GVector2 pos, eDirection dir, eItemType type = eItemType::PICKED_UP);
private:
	static list<Item*> _listItem;
};

