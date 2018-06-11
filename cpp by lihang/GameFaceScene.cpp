#include "GameFaceScene.h"

USING_NS_CC;

Scene* GameFace::createScene()
{
	auto scene = Scene::create();
	auto layer = GameFace::create();
	scene->addChild(layer);
	return scene;
}

bool GameFace::init()
{
	if (!Layer::init())
	{
		return false;
	}

	log("Setting init");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*initTiledmap();
	initSprite();*/

	_tileMap = TMXTiledMap::create("map/LargeMap.tmx");
	this->addChild(_tileMap,0);

	_decoration = _tileMap->getLayer("decoration");
	_decoration->setVisible(true);

	_collidable = _tileMap->getLayer("collidable");
	_collidable->setVisible(false);

	TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
	ValueMap spawnPoint = group->getObject("ninja");

	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	_player = Sprite::create("ninja.png");
	_player->setPosition(Vec2(x, y));
	addChild(_player, 2); 

	setViewpointCenter(_player->getPosition());

	setTouchEnabled(true);

	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//can't to add a menu
	//Sprite *closenommal = Sprite::create("CloseNormal.png");
	//Sprite *closeselected = Sprite::create("CloseSelected.png");
	//auto back_to_mainmenu = MenuItemSprite::create(
	//	closenommal,
	//	closeselected,
	//	CC_CALLBACK_1(GameFaceScene::GamecloseCallback, this));

	//back_to_mainmenu->setPosition(Vec2(origin.x + visibleSize.width - back_to_mainmenu->getContentSize().width / 2,
	//	origin.y + visibleSize.height - back_to_mainmenu->getContentSize().height / 2));

	//Menu* menu_1 = Menu::create(back_to_mainmenu, NULL);
	//menu_1->setPosition(Vec2::ZERO);
	//this->addChild(back_to_mainmenu,1);

	return true;
}


void GameFace::initTiledmap()
{

}
bool GameFace::onTouchBegan(Touch* touch, Event* event)
{
	log("onTouchBegan");
	return true;
}

void GameFace::onTouchMoved(Touch *touch, Event *event)
{
	log("onTouchMoved");
}

void GameFace::onTouchEnded(Touch *touch, Event *event)
{
	log("onTouchEnded");

	//get OpenGL coord
	Vec2 touchLocation = touch->getLocation();

	//convert to this layer model coord system
	touchLocation = this->convertToNodeSpace(touchLocation);

	log("touchLocation (%f ,%f) ", touchLocation.x, touchLocation.y);

	Vec2 playerPos = _player->getPosition();
	Vec2 diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(false));
		}
		else {
			playerPos.x -= _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(true));
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height;
		}
		else {
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}
	log("playerPos (%f ,%f) ", playerPos.x, playerPos.y);

	this->setPlayerPosition(playerPos);
}

void GameFace::setPlayerPosition(Vec2 position)
{
	//从像素点坐标转化为瓦片坐标
	Vec2 tileCoord = this->tileCoordFromPosition(position);

	//获得瓦片的GID
	int tileGid = _collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0) {
		Value prop = _tileMap->getPropertiesForGID(tileGid);
		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();

		if (collision == "true") { // test ture
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return;
		}
	}

	//move the sprite
	_player->setPosition(position);

	//roll the map
	this->setViewpointCenter(_player->getPosition());
}

Vec2 GameFace::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x, y);
}

void GameFace::setViewpointCenter(Vec2 position)
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

//void GameFaceScene::GamecloseCallback(cocos2d::Ref* pSender)
//{
//	Director::getInstance()->popScene();
//}
