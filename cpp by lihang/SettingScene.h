#pragma once
#ifndef __Setting_SCENE_H__
#define __Setting_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Setting : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	cocos2d::Sprite * bg;
	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(Setting);
};

#endif 