#ifndef FindScene_h
#define FindScene_h

#include <iostream>
#include "cocos2d.h"
#include"Server.h"
#include "Client.h"


USING_NS_CC;

/*房间搜索界面，显示房间列表，选择加入某个房间*/

class FindScene : public cocos2d:: Layer
{
private:

	Sprite * _room_list_bg;   //列表背景
	std::string _player_name; //玩家姓名
	std::vector<Button*>   room_list;  //储存房间对象

public:

	/*创建房间列表场景*/
	static cocos2d::Scene* createScene(Client* c, std::string name);

	/*初始化函数*/
	virtual bool init();

	/*更新函数，定时调用*/

	void update(float delta);

	CREATE_FUNC(FindScene);

};

#endif /*FindScene_h*/
