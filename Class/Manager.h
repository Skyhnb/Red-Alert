#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "cocos2d.h"
#include"Player.h"
#include <vector>
USING_NS_CC;


class Manager :public  cocos2d::Node
{
public:
	static Manager* createManager();
	void initManager();

	std::vector<class Player*> players;
	std::vector<class Player*>::iterator player;
	std::list<Soldier*>::iterator soldier;
	void push_back(Player *);

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	CREATE_FUNC(Manager);


};

#endif

