#include "CreateRoomScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include "RoomScene.hpp"

USING_NS_CC;

#define CLIENT_MODE 1
#define SERVER_MODE 2

static int roomMode;


Scene* RoomScene::createScene()
{
    // create a scene object, which is auto-realeased by the pool
    auto scene = Scene::create();
    
    // create a layer object, which is auto-realeased by the pool
    auto layer = RoomScene::create();
    
    // add layer as a child to the scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool RoomScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *bg = Sprite::create("background.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    this->addChild(bg,0);
    
    addMenuItem();
    
    return true;
}

void RoomScene::addMenuItem()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto createItem = MenuItemImage::create("room.png", "roomselected.png", CC_CALLBACK_1(RoomScene::menuGoToRoomScene, this));
    auto enterItem = MenuItemImage::create("enterroom.png", "enterroomselected.png", CC_CALLBACK_1(RoomScene::menuGoToFindScene, this));
    createItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                 origin.y + visibleSize.height / 3));
    enterItem->setPosition(Vec2( origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height / 3*2));
    
    auto menu = Menu::create(createItem, enterItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);
   
}

void RoomScene::menuGoToRoomScene(cocos2d::Ref *pSender)
{
    auto sc = CreateRoom::createScene();
    auto reScene = TransitionMoveInL::create(1.0f, sc);
    Director::getInstance()->pushScene(reScene);
};

void RoomScene::menuGoToFindScene(cocos2d::Ref *pSender)
{
    
}


