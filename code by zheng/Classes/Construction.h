#ifndef __CONSTRUCTION_H__
#define __CONSTRUCTION_H__
#include "cocos2d.h"
#include"SoldierSprite.h"
#include<list>
USING_NS_CC;
enum cons_type
{
	power, miner, base, armycamp, tankfac
};
class Construction :public cocos2d::Sprite
{
public:
	static Construction* createConstruction(Point position, cons_type construction_type, Layer* layer);/*在position（point型参数）处创建一个小兵*/
	void initConstruction(Point position, cons_type construction_type, Layer* layer);
	CREATE_FUNC(Construction);

	void update(float dt);
	void updateattack(float dt);
	std::list<Soldier*> attackers;
	std::list<Soldier*>::iterator attacker;
	void push_back_attacker(Soldier*);

	Sprite* character;
	Layer* _layer;
	cons_type this_type;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);

	bool isSelected;

	int cost_power;
	int produce_power;
	int hp;
};

#endif

