#include "GameFaceScene.h"
#include "SpriteLayer.h"

USING_NS_CC;

Scene* GameFace::createScene()
{
	//将两个层放在一个场景中
	GameFace* scene = new GameFace();
	scene->init();
	return scene;
}

bool GameFace::init()
{
	if (!Scene::init())
	{
		return false;
	}

	MyMap *_map = MyMap::create();
	MySprite *_mysprite = MySprite::create();
	
	//通过指针访问另一个层
	/*_map->spritelayer = _mysprite;*/

	addChild(_map, 0);
	addChild(_mysprite, 1);
	return true;
}


