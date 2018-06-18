#include "CinNameScene.h"
#include "HelloWorldScene.h"
#include "GameFaceScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CinName::createScene()
{
	auto scene = Scene::create();
	auto layer = CinName::create();
	scene->addChild(layer);
	return scene;
}

bool CinName::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("background.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	auto okMenuItem = MenuItemImage::create(
		"menu/ok-up.png",
		"menu/ok-down.png",
		CC_CALLBACK_1(CinName::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(600, 510)));

	// create menu, it's an autorelease object
	auto menu = Menu::create(okMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void CinName::menuOkCallback(cocos2d::Ref* pSender)
{
	auto sc = GameFace::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}

