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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MyMap *_map = MyMap::create();
	MySprite *_mysprite = MySprite::create();

	addChild(_map, 10);
	addChild(_mysprite, 12);

	menubg = Sprite::create("menubg.png");
	menubg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + menubg->getContentSize().height / 2));
	addChild(menubg, 11);

	//通过指针访问另一个层
	_mysprite->maplayer = _map;

	Player* localPlayer = Player::createPlayer();
	Manager* manager = Manager::createManager(_map,_mysprite);
	manager->push_back(localPlayer);
	auto* menu1 = SoldierMenu::createSoldierMenu(Point(818, 120), Point(200, 100), american,_map);
	auto* menu2 = SoldierMenu::createSoldierMenu(Point(872, 120), Point(200, 100), dog,_map);
	auto* menu3 = SoldierMenu::createSoldierMenu(Point(1164, 120), Point(200, 100), tank, _map);
	auto* menu4 = ConstructionMenu::createConstructionMenu(Point(300, 120), power,_map);
	auto* menu5 = ConstructionMenu::createConstructionMenu(Point(500, 120), miner,_map);
	auto* menu6 = ConstructionMenu::createConstructionMenu(Point(700, 120), armycamp, _map);
	auto* menu7 = ConstructionMenu::createConstructionMenu(Point(1000, 120), tankfac, _map);
	auto* menu8 = ConstructionMenu::createConstructionMenu(Point(100, 120), base, _map);
	addChild(menu1, 10);
	addChild(menu2, 10);
	addChild(menu3, 10);
	addChild(menu4, 10);
	addChild(menu5, 10);
	addChild(menu6, 10);
	addChild(menu7, 10);
	addChild(menu8, 10);
	_map->addChild(localPlayer, 9);
	_map->addChild(manager, 5);//注意优先级不能变

	return true;
}


