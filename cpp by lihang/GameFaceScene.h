#ifndef __GAMEFACE_SCENE_H__
#define __GAMEFACE_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SpriteLayer.h"
#include "MapLayer.h"

class GameFace : public cocos2d::Scene
{
public:

	virtual bool init();
	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameFace);
};
#endif