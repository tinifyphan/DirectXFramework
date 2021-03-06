#pragma once
#include"pugixml-1.7\src\pugixml.hpp"
#include"BaseObject.h"
#include"define.h"
#include"Land.h"
#include"Stair.h"
#include"Bat.h"
#include"MedusaHead.h"
#include"ObjectSpawner.h"
#include"SpearKnight.h"
#include"Door.h"
#include"FlyLand.h"
#include"Candle.h"
#include"Brick.h"
#include"Dragon.h"
#include"Spike.h"
#include"Ghost.h"
#include"Medusa.h"
#include"Fleaman.h"
#include"Skeleton.h"
#include"Raven.h"
#include"MummyMan.h"
class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static map<string, BaseObject*>* getMapObjectFromFile(const string path);
	static vector<BaseObject*>* getListObjectFromFile(const string path);
private:
	static BaseObject* getObjectById(xml_node node, eID id);
	static BaseObject* getLand(xml_node node);
	static BaseObject* getStair(xml_node node);

	static BaseObject* getBat(xml_node node);
	static BaseObject* getSpearKnight(xml_node node);
	static BaseObject* getMedusaHead(xml_node node);
	static BaseObject* getSpawner(xml_node node);
	static BaseObject* getSpike(xml_node node);
	static BaseObject* getGhost(xml_node node);
	static BaseObject* getMedusa(xml_node node);

	static BaseObject* getFleaman(xml_node node);
	static BaseObject* getSkeleton(xml_node node);
	static BaseObject* getRaven(xml_node node);

	static BaseObject* getMummyMan(xml_node node);

	static BaseObject* getDoor(xml_node node);
	static BaseObject* getFlyLand(xml_node node);
	static BaseObject* getCandle(xml_node node);
	static BaseObject* getBrick(xml_node node);
	static BaseObject* getDragon(xml_node node);

	static map<string, string> getObjectProperties(xml_node node);
};

