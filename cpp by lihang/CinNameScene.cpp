#include "CinNameScene.h"
#include <cocos2d.h>
#include <iostream>
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

	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	auto Name_Editbox = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("menu/NAMEButtonNormal.png"));
	Name_Editbox->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 2));
	Name_Editbox->setFontColor(Color3B(255, 0, 0));//设置字体颜色
	Name_Editbox->setPlaceHolder("Name:");//设置预置文本 
	Name_Editbox->setMaxLength(30);//设置最大长度
	Name_Editbox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
	Name_Editbox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位
	Name_Editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//设置返回类型
	Name_Editbox->setPlaceholderFontName("Arial");//设置字体
	this->addChild(Name_Editbox);

	auto okMenuItem = MenuItemImage::create(
		"menu/NAMEButtonSelected.png", 
		"menu/NAMEButtonSelected.png",
		CC_CALLBACK_1(CinName::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(475,750)));

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

void CinName::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {}

void CinName::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {}

void CinName::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	/*myname = text;*/
}

void CinName::editBoxReturn(cocos2d::extension::EditBox *editBox) {}

