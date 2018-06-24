#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <cocos2d.h>
#include "RoomScene.hpp"

USING_NS_CC;

#define CLIENT_MODE 1
#define SERVER_MODE 2

static int      roomMode;
static Client*  client = nullptr;

Scene* RoomScene::createScene(Client* c, int mode, std::string _playerName)
{
    // create a scene object, which is auto-realeased by the pool
    auto scene = Scene::create();
    client = c;
    roomMode = mode;
    player_name = _playerName;
    
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
    
    Sprite *bg = Sprite::create("redalertbg.png");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    this->addChild(bg,0);
    
    addMenuItem();
    
    return true;
}

void RoomScene::addMenuItem()
{
    auto createItem = MenuItemImage::create("room.png", "roomselected.png", CC_CALLBACK_1(RoomScene::menuGoToRoomScene, this));
    auto enterItem = MenuItemImage::create("enterroom.png", "enterroomselected.png", CC_CALLBACK_1(RoomScene::menuGoToFindScene, this));
    createItem->setPosition(Vec2(origin.x + visibleSize.width / 4,
                                 origin.y + visibleSize.height / 4));
    enterItem->setPosition(Vec2( origin.x + visibleSize.width / 4,
                                origin.y + visibleSize.height / 4));
    
    auto menu = Menu::create(createItem, NULL);
    menu->setPosition(Director::getInstance()->convertToGL(Vec2(300, 300)));
    this->addChild(menu,1);
    auto menu2= Menu::create(enterItem,NULL);
    menu->setPosition(Director::getInstance()->convertToGL(Vec2(300, 500)));
    this->addChild(menu2,2);
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


