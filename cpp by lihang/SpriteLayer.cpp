#include "SpriteLayer.h"
#include "PauseLayer.h"

USING_NS_CC;

bool MySprite::init()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	initSpritebg();

	this->schedule(schedule_selector(MySprite::updateTime),1.0f, kRepeatForever,0);
	this->schedule(schedule_selector(MySprite::updateMoney), 1.0f, kRepeatForever, 0);
	updatePower();

	auto pauseItem = MenuItemImage::create(
		"menu/pause.png",
		"menu/pauserelease.png",
		CC_CALLBACK_1(MySprite::menuCloseCallback, this));

	pauseItem->setPosition(Vec2(origin.x + visibleSize.width - pauseItem->getContentSize().width / 2,
		origin.y + visibleSize.height - pauseItem->getContentSize().height / 2));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void MySprite::menuCloseCallback(cocos2d::Ref* pSender)
{
	//得到窗口的大小  
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。  
	//这里类似截图。  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面  
	Director::sharedDirector()->pushScene(GamePause::scene(renderTexture));
}

void MySprite::initSpritebg()
{
	_money = Sprite::create("money.png");
	_money->setPosition(Vec2(1106, 937));
	addChild(_money);
	_power = Sprite::create("power.png");
	_power->setPosition(Vec2(911, 932));
	addChild(_power);
	_time = Sprite::create("time.png");
	_time->setPosition(Vec2(100, 932));
	addChild(_time);
}

void MySprite::updateMoney(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	money += 15;
	Node *n = this->getChildByTag(GameMoney);
	if (n)
	{
		this->removeChildByTag(GameMoney);
	}
	__String *money=__String::createWithFormat("%d", this->money);
	auto moneylable = Label::createWithTTF(money->getCString(),
		"fonts/Marker Felt.ttf", 18);
	moneylable->setPosition(Vec2(1126, 932));
	this->addChild(moneylable, 5, GameMoney);
}

void MySprite::updatePower()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Node *n = this->getChildByTag(GamePower);
	if (n)
	{
		this->removeChildByTag(GamePower);
	}
	__String *power = __String::createWithFormat("%d / %d", this->usedpower, this->power);
	auto powerlable = Label::createWithTTF(power->getCString(),
		"fonts/Marker Felt.ttf", 18);
	powerlable->setPosition(Vec2(926, 932));
	this->addChild(powerlable, 5, GamePower);
}

void MySprite::updateTime(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	nSecond++;
	money += 5;
	if (nSecond == 60) {
		nSecond = 0;
		nMinute++;
		if (nMinute == 60) {
			nMinute = 0;
			nHour++;
			if (nHour == 24) {
				nHour = 0;
			}
		}
	}
	Node *n = this->getChildByTag(GameTime);
	if (n)
	{
		this->removeChildByTag(GameTime);
	}
	__String *time = __String::createWithFormat("%d/ %d/ %d", this->nHour, this->nMinute, this->nSecond);
	auto timelable = Label::createWithTTF(time->getCString(),
		"fonts/Marker Felt.ttf", 18);
	timelable->setPosition(Vec2(100, 932));
	this->addChild(timelable, 5, GameTime);
}
