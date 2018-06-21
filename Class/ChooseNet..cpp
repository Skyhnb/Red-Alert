#include <stdio.h>
#include "ChooseNet.h"
#include "FindScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace ui;

Scene* NetMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = NetMenu::create();
	scene->addChild(layer);

	return scene;
}

bool NetMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	system("ping -c 1 255.255.255.255");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("roombg.png");
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));


  auto pageView = PageView::create();
    pageView->setContentSize(Size(680.0f, 680.0f));
    
    pageView->setPosition(Vec2((visibleSize.width - pageView->getContentSize().width) / 2.0f,
                               (visibleSize.height - pageView->getContentSize().height)*0.6));

	auto thisObject = this;

	//===================local network button============================

	auto local_button = Button::create("LocalFight.png");

	local_button->setScale(1.0);

	local_button->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5 * 2));

	local_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			Color4B black = Color4B(0, 0, 0, 100);
			auto role_layer = LayerColor::create(black, 680, 680);
			role_layer->setPosition(Vec2(origin.x, origin.y));

			thisObject->addChild(role_layer, 2);
			local_button->setVisible(false);

			auto role_selector = Sprite::create("BlankBoard.png");
			role_selector->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
			role_layer->addChild(role_selector);

			auto create_button = Button::create("button.png");
			auto join_button = Button::create("button.png");

			role_selector->addChild(create_button);
			role_selector->addChild(join_button);

			create_button->setTitleText("create room");
			create_button->setTitleFontSize(20);
			join_button->setTitleText("join room");
			join_button->setTitleFontSize(20);

			float widthMargin = visibleSize.width / 2 - role_selector->getContentSize().width / 2;
			float heightMargin = visibleSize.height / 2 - role_selector->getContentSize().height / 2;

			create_button->setPosition(Vec2(role_selector->getContentSize().width / 2, role_selector->getContentSize().height / 3 * 2));

			join_button->setPosition(Vec2(role_selector->getContentSize().width / 2, role_selector->getContentSize().height / 3));

			join_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
				if (type == Widget::TouchEventType::ENDED) {
					auto client = Client::create(2);
					client->_with_server = false;
					auto transition = TransitionSlideInL::create(0.5, FindScene::createScene(client, _player_name));

					Director::getInstance()->pushScene(transition);
				}
			});

			create_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
				if (type == Widget::TouchEventType::ENDED) {

					auto server = LocalServer::create();
					this->addChild(server);
					auto client = Client::create(2);
					this->addChild(client);
					client->_filter_mode = true;
					client->order_type = _player_name;
					client->_with_server = true;

					auto transition = TransitionSlideInL::create(0.5,RoomScene::createScene(client, 2, _player_name));
					Director::getInstance()->pushScene(transition);

				}
			});
		}

	});
}