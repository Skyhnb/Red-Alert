//
//  RoomScene.cpp
//  gameover
//
//  Created by anonym_co on 2018/6/21.
//

#include "RoomScene.hpp"
#include "GameFaceScene.h"
#include "cocos2d.h"

Scene* CreateRoom::createScene()
{
    auto scene=Scene::create();
    auto layer=CreateRoom::create();
    scene->addChild(layer);
    return scene;
}
bool CreateRoom::init()
{
    if(!Scene::init())
    {
        return false;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *bg = Sprite::create("background.jpg");
    bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
                         origin.y + visibleSize.height / 2));
    this->addChild(bg);
    
    auto Name_Editbox = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("menu/NAMEButtonNormal.png"));
    
    Name_Editbox->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 2));
    Name_Editbox->setFontColor(Color3B(200, 0, 0));//设置字体颜色
    Name_Editbox->setPlaceHolder("Room Name:");//设置预置文本
    Name_Editbox->setMaxLength(30);//设置最大长度
    Name_Editbox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
    Name_Editbox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);
    Name_Editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);
    Name_Editbox->setPlaceholderFontName("fonts/Marker Felt.ttf");
    this->addChild(Name_Editbox);

	auto okMenuItem = MenuItemImage::create(
		"menu/NAMEButtonSelected.png",
		"menu/NAMEButtonSelected.png",
		CC_CALLBACK_1(CreateRoom::menuOkCallback, this));

	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(475, 750)));

	// create menu, it's an autorelease object
	auto menu = Menu::create(okMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
    
    return true;
}

void CreateRoom::menuOkCallback(cocos2d::Ref* pSender)
{
	auto sc = GameFace::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}
void CreateRoom::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {}
void CreateRoom::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {}
void CreateRoom::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
    auto editbox = (EditBox*)editBox;
}
void CreateRoom::editBoxReturn(cocos2d::extension::EditBox *editBox){}
