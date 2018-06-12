#ifndef __GAMEFACE_SCENE_H__
#define __GAMEFACE_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class Game : public cocos2d::Layer
{
public:

	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::TMXLayer* _decoration;
	cocos2d::TMXLayer* _collidable;
	cocos2d::Sprite* _player;

	virtual bool init();
	static cocos2d::Scene* createScene(); 
	void initTiledmap();
	void initSprite();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	void setViewpointCenter(cocos2d::Vec2 position);
	//void GamecloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(Game);
};
#endif