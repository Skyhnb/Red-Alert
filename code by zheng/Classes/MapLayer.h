#pragma once
#ifndef __MAP_SCENE_H__
#define __MAP_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class MyMap : public cocos2d::Layer
{
public:
	cocos2d::experimental::TMXTiledMap* _tileMap;
	cocos2d::experimental::TMXLayer* _decoration;
	cocos2d::Sprite* _player;
	cocos2d::Sprite* _money;
	cocos2d::Sprite* _base;

	virtual bool init();
	void initTiledmap();
	void initBase();

	void rollLeft(float dt);
	void rollRight(float dt);
	void rollUp(float dt);
	void rollDown(float dt);

	void setViewpointCenter(cocos2d::Vec2 position);

	CREATE_FUNC(MyMap);
};
#endif