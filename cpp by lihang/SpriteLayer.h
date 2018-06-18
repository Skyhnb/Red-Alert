#ifndef __SPRITE_SCENE_H__
#define __SPRITE_SCENE_H__
#define GameMoney 100
#define GamePower 101
#define GameTime 102

#include "cocos2d.h"

class MySprite : public cocos2d::Layer
{
public:
	virtual bool init();

	int nHour = 0;
	int nMinute = 0;
	int nSecond = 0;
	int power = 0;
	int usedpower = 0;
	int money = 0;

	cocos2d::Sprite *_money;
	cocos2d::Sprite *_power;
	cocos2d::Sprite *_time;

	void menuCloseCallback(cocos2d::Ref* pSender);
	void initSpritebg();
	void updateMoney(float dt);
	void updatePower();
	void updateTime(float dt);

	CREATE_FUNC(MySprite);
};

#endif 