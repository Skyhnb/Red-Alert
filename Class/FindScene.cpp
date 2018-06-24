#include <stdio.h>
#include "ui/CocosGUI.h"
#include"FindScene.h"
#include"OrderCode.h"
#include"cocos2d.h"
#include "createroom.h"


USING_NS_CC;
using namespace ui;

int timeloop; //计时器，每100f发送一次查询房间信息
static Client*  client = nullptr;  //指向client，传输数据
static std::string  _static_player_name; //玩家名字
std::vector<std::string> room_owner; //房主名称

Scene* FindScene::createScene(Client* cl, std::string name)
{
	client = cl;
	_static_player_name = name;

	auto scene = Scene::create();
	auto layer = FindScene::create();

	scene->addChild(layer);

	return scene;

}

bool FindScene::init()
{
	_player_name = _static_player_name;

	if (!Layer::init)
	{
		return false;
	}

	this->addChild(client);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto RoomListBg = Sprite::create();
	RoomListBg->setPosition(origin / 2 + visibleSize / 2);
	_room_list_bg = RoomListBg;
	this->addChild(RoomListBg, 1);

	auto bg = Sprite::create("roombg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	this->scheduleUpdate();

	return true;

}

void FindScene::update(float delta)
{
	if (client->_is_searched)
	{
		timeloop++;

		if (timeloop / 100 > 1)
		{
			timeloop = 0;
			client->send_message(FIND_FOR_ROOM, "|||||||||||");
		}

		std::string temp = client->pullorder();

		if (temp != "no")
		{
			if (temp[0] == ANSWER_FOR_ROOM[0])
			{
				std::string owner_name = temp.substr(1, temp.size() - 1);

				bool have_it = false;
				for (int i = 0; i < room_owner.size(); i++)
				{
					if (owner_name == room_owner.at(i))
					{
						have_it = true;
					}
				}

				if (!have_it)
				{
					room_owner.push_back(owner_name);

					auto space = Button::create("PlayerBar.png", "PlayerBar.png");
					auto enter_in = Button::create("RoomList_connect.png");
					space->addChild(enter_in);

					enter_in->setPosition(Vec2(space->getContentSize().width / 6 * 5, space->getContentSize().height / 2));
					space->setScale(0.8f, 0.7f);

					room_list.push_back(enter_in);
					std::string button_owner_name = owner_name;
					enter_in->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) 
					{
						if (type == Widget::TouchEventType::ENDED)
						{
							client->_filter_mode = true;
							client->order_type = button_owner_name;

							auto transition= TransitionSlideInL::create(1.0f,  CreateRoom::createScene(client, 1, _player_name));
							Director::getInstance()->pushScene(transition);
						}
					});
					space->setTitleText(owner_name);
					space->setTitleFontSize(36);
					_room_list_bg->addChild(space);

					space->setPosition(Vec2(
						_room_list_bg->getContentSize().width / 2,
						(_room_list_bg->getContentSize().height - 90) / 5 * (5 - room_owner.size())));

				}
			}
		}
	}
}