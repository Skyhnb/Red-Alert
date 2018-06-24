#pragma once
#ifndef __SOLDIERSPRITE_H__
#define __SOLDIERSPRITE_H__
#include "cocos2d.h"
#include<list>
USING_NS_CC;
enum sol_type
{
	american,dog
};
class Soldier : public cocos2d::Sprite
{
public:
	static Soldier* createSoldier(Point position,sol_type soldier_type);/*在position（point型参数）处创建一个小兵*/
	void initSoldier(Point position, sol_type soldier_type);
	CREATE_FUNC(Soldier);
	
	void update(float dt);
	void updateattack(float dt);
	std::list<Soldier*> attackers;
	std::list<Soldier*>::iterator attacker;
	void push_back_attacker(Soldier*);

	Sprite* character;
	Sprite* selected;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	bool isSelected;
	bool isActive;

	static int n;//测试用
	int atk ;
	int range;
	int hp ;
};


#endif