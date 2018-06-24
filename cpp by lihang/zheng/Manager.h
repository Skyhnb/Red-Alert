#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "cocos2d.h"
#include"Player.h"
#include"MyMoveto.h"
#include <vector>
USING_NS_CC;


class Manager :public  cocos2d::Node
{
public:
	static Manager* createManager();
	void initManager();//初始化


	std::vector<class Player*> players;
	std::vector<class Player*>::iterator player;
	std::list<Soldier*>::iterator soldier;
	std::list<Construction*>::iterator construction;
	void push_back(Player *);//收集玩家数据

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(Touch* pTouch, Event* pEvent);
	CREATE_FUNC(Manager);//鼠标监听

	EventListenerKeyboard* key_listener;
	bool onKeyReleased(EventKeyboard::KeyCode keycode, Event* pEvent);

	bool non_player_Selected;

	static bool attack_mode;
	void attack(Soldier* attacker,Soldier* defender);
	void attack(Soldier* attacker, Construction* defender);
};

union click_object
{
	Soldier* click_soldier;
	Construction* click_construction;
};

#endif

