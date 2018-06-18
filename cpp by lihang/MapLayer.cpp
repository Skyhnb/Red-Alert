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

	initSprite();

	setTouchEnabled(true);

	return true;
}

//初始化地图、精灵
void MyMap::initTiledmap()
{
	_tileMap = experimental::TMXTiledMap::create("map/Map1.tmx");
	this->addChild(_tileMap, 0, 1);

	_decoration = _tileMap->getLayer("decoration");
	_decoration->setVisible(true);
}

void MyMap::initSprite()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	_player = Sprite::create("ninja.png");
	_player->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	addChild(_player, 2, 200);
}

bool MyMap::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return false;
}

//drag the map
void MyMap::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto diff = touches[0]->getDelta();
	auto node = getChildByTag(200);
	auto currentPos = node->getPosition();
	Vec2 pointA = Vec2(visibleSize.width / 2, visibleSize.height / 2);

	node->setPosition(currentPos - diff);
	this->setViewpointCenter(_player->getPosition());
}

void MyMap::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");
	return;
}

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

//将ui坐标转化为瓦片坐标
//Vec2 MyMap::tileCoordFromPosition(Vec2 pos)
//{
//	int x = pos.x / _tileMap->getTileSize().width;
//	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
//	return Vec2(x, y);
//}
