#include "SoldierSprite.h"
int Soldier::n = 0;
Soldier* Soldier::createSoldier(Point position)
{
	Soldier* soldier = Soldier::create();
	if (soldier)
	{
		soldier->initSoldier(position);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return NULL;
}

void Soldier::initSoldier(Point position)
{
	this->isSlected = false;
	n++;
	character = Sprite::create("soldier.png");
	character->setScale(0.2);
	character->setPosition(position);
	character->setPositionY(position.y + 10*n);
	this->addChild(character);
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Soldier::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	if (
		point.x > position.x - character->getContentSize().width / 2 &&
		point.x<position.x + character->getContentSize().width / 2 &&
		point.y>position.y - character->getContentSize().height / 2 &&
		point.y < position.y + character->getContentSize().height / 2
		)
	{
		this->isSlected = !isSlected;
	}
	else if (this->isSlected)
	{
		character->setPosition(point);
		n--;
	}
	return false;

}

SoldierMenu* SoldierMenu::createSoldierMenu(Point position)
{
	SoldierMenu* menu = SoldierMenu::create();
	if (menu)
	{
		menu->initSoldierMenu(position);
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return NULL;
}

void SoldierMenu::initSoldierMenu(Point position)
{
	soldiermenu= Sprite::create("soldiermenu.png");
	soldiermenu->setScale(0.5);
	soldiermenu->setPosition(position);
	this->addChild(soldiermenu);
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SoldierMenu::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool SoldierMenu::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->soldiermenu->getPosition();
	if (
		point.x > position.x - soldiermenu->getContentSize().width / 2 &&
		point.x<position.x + soldiermenu->getContentSize().width / 2 &&
		point.y>position.y - soldiermenu->getContentSize().height / 2 &&
		point.y < position.y + soldiermenu->getContentSize().height / 2
		)
	{
		auto* soldier = Soldier::createSoldier(Point(200, 300));/*在这里修改出兵的位置*/
		this->addChild(soldier);
	}
	
	return false;

}






