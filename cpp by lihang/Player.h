#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include<list>
#include"SoldierSprite.h"
#include"Construction.h"
USING_NS_CC;
class Player :public  cocos2d::Node
{
public:
	static Player* createPlayer();
	void initPlayer();
	void update(float dt);//初始化

	static std::list<Soldier*> playerSoldier;/*建立一个list来存储所有的小兵方便player中遍历小兵方位，确定鼠标落点的区域*/
	std::list<Soldier*>::iterator iter;

	static std::list<Construction*> playerConstruction;/*建立一个list来存储所有的小兵方便player中遍历小兵方位，确定鼠标落点的区域*/
	std::list<Construction*>::iterator iter2;

	static int money;
	static int power_max;
	static int power_cost;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	bool no_soldier_Selected;
	bool no_construction_Selected;
	bool non_object_Selected;

	Soldier*getSelectedSoldier();//获取被选中小兵
	Construction* getSelectedConstruction();//获取被选中建筑

	CREATE_FUNC(Player);
};

class SoldierMenu : public cocos2d::Layer
{
public:
	static SoldierMenu* createSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type);/*在position（point型参数）处创建一个出兵按钮,出兵位置为SoldierPosition*/
	void initSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type);
	CREATE_FUNC(SoldierMenu);

	Sprite* soldier_menu;

	int cost;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, Point SoldierPosition, sol_type soldier_type);
};
class ConstructionMenu : public cocos2d::Layer
{
public:
	static  ConstructionMenu* createConstructionMenu(Point position, cons_type construct_type);/*在position（point型参数）处创建一个建筑按钮,方式为拖动*/
	void initConstructionMenu(Point position, cons_type construct_type);

	Sprite* construction_menu;
	Sprite* construction;

	int _power_cost;

	bool create_begin;
	CREATE_FUNC(ConstructionMenu);

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
	void onTouchMoved(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
	void onTouchEnded(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
};
#endif

