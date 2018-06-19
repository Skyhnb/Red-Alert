#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* CreateRoom::createScene()
{
    auto scene=Scene::create();
    auto layer=CreateRoom::create();
    scene->addChild(layer);
    return scene;
}

bool CreateRoom::init()
{
    if(!Layer::init())
    {
        return false;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    MenuItemImage *pRoomItem = MenuItemImage::create("room.png","roomselected.png",this,menu_selector(CreateRoom::menuGoToMainScene));
    pRoomItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.35f));
    
    Menu* pMenuRoom=Menu::create(pRoomItem,NULL);
    pMenuRoom->setPosition(CCPointZero);
    this->addChild(pMenuRoom);
    return true;
}
void CreateRoom::menuGoToMainScene(CCObject* pSender)
{
    Director::getInstance()->replaceScene(CreateRoom::createScene());
}




