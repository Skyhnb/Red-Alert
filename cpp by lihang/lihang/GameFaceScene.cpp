#include "GameFaceScene.h"
#include "SpriteLayer.h"

USING_NS_CC;

Scene* GameFace::createScene()
{
	//将两个层放在一个场景中
	GameFace* scene = new GameFace();
	scene->init();
	return scene;
}

bool GameFace::init()
{
	if (!Scene::init())
	{
		return false;
	}

	MyMap *_map = MyMap::create();
	MySprite *_mysprite = MySprite::create();

	addChild(_map, 0);
	addChild(_mysprite, 1);

	//通过指针访问另一个层
	_mysprite->maplayer = _map;

	Player* localPlayer = Player::createPlayer();
	Manager* manager = Manager::createManager();
	manager->push_back(localPlayer);
	auto* menu1 = SoldierMenu::createSoldierMenu(Point(500, 120), Point(200, 100), american,_map);
	auto* menu4 = SoldierMenu::createSoldierMenu(Point(700, 120), Point(200, 100), dog,_map);
	auto* menu2 = ConstructionMenu::createConstructionMenu(Point(100, 120), power);
	auto* menu3 = ConstructionMenu::createConstructionMenu(Point(300, 120), miner);
	addChild(menu1, 10);
	addChild(menu2, 10);
	addChild(menu3, 10);
	addChild(menu4, 10);
	addChild(localPlayer, 9);
	addChild(manager, 5);//注意优先级不能变

	return true;
}


