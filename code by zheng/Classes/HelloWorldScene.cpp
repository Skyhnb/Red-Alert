#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Player* localPlayer = Player::createPlayer();
	Manager* manager = Manager::createManager();
	manager->push_back(localPlayer);

	auto* menu1 = SoldierMenu::createSoldierMenu(Point(600, 200), Point(200, 100),american);
	auto* menu4= SoldierMenu::createSoldierMenu(Point(700, 200), Point(200, 150),dog);
	auto* menu2 = ConstructionMenu::createConstructionMenu(Point(800, 200),power);
	auto* menu3= ConstructionMenu::createConstructionMenu(Point(700, 300), miner);
	addChild(menu1,10);
	addChild(menu2, 10);
	addChild(menu3, 10);
	addChild(menu4, 10);
	addChild(localPlayer, 9);
	addChild(manager,5);//注意优先级不能变
	return true;
}
