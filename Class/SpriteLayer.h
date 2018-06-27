#ifndef __SPRITE_SCENE_H__
#define __SPRITE_SCENE_H__
#define GameMoney 100
#define GamePower 101
#define GameTime 102

#include "cocos2d.h"
#include "SoldierSprite.h"
#include "Player.h"
#include "Manager.h"
#include "MapLayer.h"

class MySprite : public cocos2d::Layer
{
public:
	virtual bool init();

	int nHour = 0;
	int nMinute = 0;
	int nSecond = 0;
	int power1 = 0;
	int usedpower = 0;
	int money = 0;

	cocos2d::Sprite *_money;
	cocos2d::Sprite *_power;
	cocos2d::Sprite *_time;
	MyMap* maplayer;

	void menuPauseCallback(cocos2d::Ref* pSender);
	void initSpritebg();
	void updateMoney(float dt);
	void updatePower(float dt);
	void updateTime(float dt);
	void mousemove(Event* event);

	CREATE_FUNC(MySprite);
};

#endif 