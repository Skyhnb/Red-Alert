#include <stdio.h>
#include "ui/CocosGUI.h"
#include "RoomScene.h"
#include"OrderCode.h"

USING_NS_CC;
using namespace ui;

static int      roomMode;
static Client*  client = nullptr;
static std::string player_name;
#define CLIENT_MODE 1
#define SERVER_MODE 2

static int loop;
bool    finish_create;
int     player_count;
int     current_count;
int     loop_you_in;
bool    if_initial;
bool    if_self_joined;

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
	if (!Layer::init())
	{
		return false;
	}
	// get the visiblesize in opengl coordinate
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// get the origin's position in opengl coordinate
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto room = Sprite::create("roombg.png");
	this->addChild(room);
	room->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	_chatWindow = cocos2d::ui::TextField::create("input words here", "Arial", 30);
	_chatWindow->setMaxLengthEnabled(true);
	_chatWindow->setMaxLength(20);
	_chatWindow->setPosition(Point(_room_ptr->getContentSize().width / 3 * 1.2,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	_chatWindow->addEventListener(CC_CALLBACK_2(RoomScene::textFieldEvent, this));

	room->addChild(_chatWindow, 1);

	auto send_message_button = Button::create("button.png");
	room->addChild(send_message_button);
	send_message_button->cocos2d::Node::setScale(0.7);
	send_message_button->setPosition(Vec2(
		_room_ptr->getContentSize().width / 2 * 1.7,
		(_room_ptr->getContentSize().height - 90) / 6 * 1));
	send_message_button->setTitleText("send message");
	send_message_button->setTitleFontSize(20);
	send_message_button->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			std::string message = player_name +":" +_chatWindow->getString();
			client->send_message(CHAT_MES, message);
			_chatWindow->setString("");
		}
	});

	Sprite *startSpriteNormal = Sprite::create("startnormal.png");
	Sprite *startSpriteSelected = Sprite::create("startdown.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal,
		startSpriteSelected,
		CC_CALLBACK_1(RoomScene::menuNextCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(331, 450)));
	// create menu, it's an autorelease object
	auto menu = Menu::create( startMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;

}

void RoomScene::textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		Size screenSize = CCDirector::getInstance()->getWinSize();

		//_pleaseStartButton->setVisible(true);
	}
	break;

	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);

		// _playerName = textField->getString();
		// _pleaseStartButton->setVisible(true);
	}
	break;

	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		// _pleaseStartButton->setVisible(false);
		//_playerName = textField->getString();
		//_nameStartButton->setVisible(true);

	}
	break;

	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);

		// _playerName = textField->getString();
	}
	break;

	default:
		break;
	}
}

void RoomScene:: menuNextCallback(cocos2d::Ref* pSender)
{

}

