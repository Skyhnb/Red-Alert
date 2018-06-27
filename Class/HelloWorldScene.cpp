#include "HelloWorldScene.h"
#include "SettingScene.h"
#include "GameFaceScene.h"
#include "SimpleAudioEngine.h"
#include"InputNameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	log("HelloWorld init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("background.jpg");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	addMenuItem();

    return true;
}

//添加开始、设置菜单
void HelloWorld::addMenuItem()
{
	//start sprite
	Sprite *startSpriteNormal = Sprite::create("menu/startnormal.png");
	Sprite *startSpriteSelected = Sprite::create("menu/startdown.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal,
		startSpriteSelected,
		CC_CALLBACK_1(HelloWorld::menuItemStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 500)));

	// set image menu
	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"menu/settingsnormal.png",
		"menu/settingsdown.png",
		CC_CALLBACK_1(HelloWorld::menuItemSettingCallback, this));
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 621)));

	auto menu = Menu::create(startMenuItem, settingMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

//转到设置界面
void HelloWorld::menuItemSettingCallback(Ref* pSender)
{
	auto sc = Setting::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

//转到输入名字界面
void HelloWorld::menuItemStartCallback(Ref* pSender)
{
	auto sc = InputNameScene::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}
