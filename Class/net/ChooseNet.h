#ifndef  _CHOOSENET_H
#define  _CHOOSENET_H
#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Server.h"
#include "Client.h"
#include "RoomScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

/*网络选择界面，暂时只有局域网功能*/
class NetMenu :public cocos2d::Layer
{
protected:
	std::string _player_name;  // 玩家名称

	Button* _nameStartButton;  //指向输入框的指针
	Button* _pleaseStartButton; //指向确认输入的指针

public:
	static cocos2d::Scene* createScene();

	virtual bool init();


};

#endif // ! _CHOOSENET_H
