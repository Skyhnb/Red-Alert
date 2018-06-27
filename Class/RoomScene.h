#ifndef _RoomScene_h_
#define _RoomScene_h_

#include <iostream>
#include "cocos2d.h"
#include"Server.h"
#include"Client.h"
#include"ui/CocosGUI.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;


class RoomScene :public cocos2d::Layer
{
protected:
	Vector<Sprite*>     _exist_player;             //目前房间里的Player
	Sprite*             _room_ptr;                 //房间背景
	std::string         _owner_player_name;        //房主的姓名
	Button*             _start_game_button;        //开始游戏按钮
	std::string         _chatString;               //聊天信息
	TextField*          _chatWindow;               //聊天输入框
public:
	static cocos2d::Scene* createScene(Client* c, int mode, std::string _playerName);

	virtual bool init();

	void textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type);

	void menuNextCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(RoomScene);
};

#endif/*_RoomScene_h_*/