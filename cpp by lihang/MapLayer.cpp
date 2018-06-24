#include "MapLayer.h"

USING_NS_CC;

bool MyMap::init()
{
	if (!Layer::init())
	{
		return false;
	}

	log("Setting init");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initTiledmap();

	initBase();

	setTouchEnabled(true);

	return true;
}

//初始化地图
void MyMap::initTiledmap()
{
	_tileMap = experimental::TMXTiledMap::create("map/Map1.tmx");
	this->addChild(_tileMap, 0, 1);

	_decoration = _tileMap->getLayer("decoration");
	_decoration->setVisible(true);
}

//初始化主基地
void MyMap::initBase()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_base = Sprite::create("base.png");
	_base->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height / 3));
	_base->setScale(1.5);
	addChild(_base, 2, 200);
}

//使位于视野中心
void MyMap::setViewpointCenter(Vec2 position)
{
	log("setViewpointCenter");

	log("position (%f ,%f) ", position.x, position.y);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//可以防止，视图左边超出屏幕之外。
	int x = MAX(position.x, visibleSize.width / 2);
	int y = MAX(position.y, visibleSize.height / 2);

	//可以防止，视图右边超出屏幕之外。
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
		- visibleSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
		- visibleSize.height / 2);

	//屏幕中心点
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	//使精灵处于屏幕中心，移动地图目标位置
	Vec2 pointB = Vec2(x, y);
	log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量
	Vec2 offset = pointA - pointB;
	log("offset (%f ,%f) ", offset.x, offset.y);
	this->setPosition(offset);
}

//地图左移，视野右移
void MyMap::rollRight(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.x <= 0 && pos.x >= -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1080)
	{
		pos.x -= 1;
		if (pos.x <= 0 && pos.x >= -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1080)
		{
		    this->setPosition(pos);
		}
	}
}

//地图右移，视野左移
void MyMap::rollLeft(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.x <= 0 && pos.x >=  -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1080)
	{
		pos.x += 1;
		if (pos.x <= 0 && pos.x >=  -_tileMap->getMapSize().width * (_tileMap->getTileSize().width - 1)+1080)
		{
			this->setPosition(pos);
		}
	}
}

//地图上移，视野下移
void MyMap::rollDown(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+810)
	{
		pos.y += 1;
		if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+810)
		{
			this->setPosition(pos);
		}
	}
}

//地图下移，视野上移
void MyMap::rollUp(float dt)
{
	Vec2 pos = this->getPosition();
	if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+810)
	{
		pos.y -= 1;
		if (pos.y <= 0 && pos.y >= -_tileMap->getMapSize().height * (_tileMap->getTileSize().height - 1)+810)
		{
			this->setPosition(pos);
		}
	}
}