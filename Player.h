#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "cocos2d.h"
#include<list>
#include"SoldierSprite.h"
USING_NS_CC;
class Player :public  cocos2d::Node
{
public:
	static Player* createPlayer();
	void initPlayer();

	static std::list<Soldier*> playerSoldier;/*建立一个list来存储所有的小兵方便player中遍历小兵方位，确定鼠标落点的区域*/
	std::list<Soldier*>::iterator iter;

	EventListenerTouchOneByOne* listener;
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
	bool nonSelected;
	CREATE_FUNC(Player);
};

class SoldierMenu : public cocos2d::Layer
{
public:
	static SoldierMenu* createSoldierMenu(Point position, Point SoldierPosition);/*在position（point型参数）处创建一个出兵按钮,出兵位置为SoldierPosition*/
	void initSoldierMenu(Point position, Point SoldierPosition);
	Sprite* soldiermenu;
	EventListenerTouchOneByOne* listener;
	int cost;
	CREATE_FUNC(SoldierMenu);
	bool onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, Point SoldierPosition);
};
#endif

