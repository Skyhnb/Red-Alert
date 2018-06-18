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

	virtual bool init();
	void initTiledmap();
	void initSprite();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);

	//Vec2 tileCoordFromPosition(Vec2 pos);
	void setViewpointCenter(cocos2d::Vec2 position);

	CREATE_FUNC(MyMap);
};
#endif