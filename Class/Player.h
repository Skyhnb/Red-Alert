#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include<list>
#include"SoldierSprite.h"
#include"Construction.h"
#include"MyMoveto.h"
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
	bool non_object_Selected;//传递选中信息

	static bool construction_commit;
	static bool tank_commit;
	static bool soldier_commit;//传递造兵，建筑许可

	static Point soldier_create_position;
	static Point tank_create_position;
	static Point gather_position;

	Soldier*getSelectedSoldier();//获取被选中小兵
	Construction* getSelectedConstruction();//获取被选中建筑

	CREATE_FUNC(Player);
};

class SoldierMenu : public cocos2d::Layer
{
public:
	static SoldierMenu* createSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type,Layer* layer);/*在position（point型参数）处创建一个出兵按钮,出兵位置为SoldierPosition*/
	void initSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type,Layer* layer);
	CREATE_FUNC(SoldierMenu);

	void update(float dt);

	Point soldier_Position;
	sol_type this_type;
	void create_Soldier();

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent,  sol_type soldier_type);

	Sprite* soldier_menu;

	Layer* _layer;

	int cost;
	int cd_time;
	int waiting_soldier;


};

class ConstructionMenu : public cocos2d::Layer
{
public:
	static  ConstructionMenu* createConstructionMenu(Point position, cons_type construct_type,Layer* layer);/*在position（point型参数）处创建一个建筑按钮,方式为拖动*/
	void initConstructionMenu(Point position, cons_type construct_type,Layer* layer);
	void update(float dt);

	Sprite* construction_menu;
	Sprite* construction;
	cons_type this_type;

	Layer* _layer;
	std::list<Construction*>::iterator iter2;

	int _power_cost;
	int cd_time;
	bool base_only;

	bool create_begin;
	CREATE_FUNC(ConstructionMenu);

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
	void onTouchMoved(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
	void onTouchEnded(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type);
};
#endif

