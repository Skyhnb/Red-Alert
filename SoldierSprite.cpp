#include "SoldierSprite.h"
int Soldier::n = 0;//测试用
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
	this->isActive = false;
	n++;//测试用

	hp = 50;
	atk = 10;

	character = Sprite::create("soldier.png");
	character->setScale(0.5);
    character->setPosition(position);
	character->setPositionY(position.y + 80*n);//测试用
	this->addChild(character);//非选中状态图

	selected = Sprite::create("selected.png");
	auto characterSize = character->getContentSize();
	selected->setPosition(characterSize.width / 2, characterSize.height / 2);
	selected->setOpacity(0);
	character->addChild(selected);//选中状态图

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//触摸事件监听器
}

bool Soldier::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	this->isSelected = (
		point.x > position.x - character->getContentSize().width / 4 &&
		point.x<position.x + character->getContentSize().width / 4 &&
		point.y>position.y - character->getContentSize().height / 4 &&
		point.y < position.y + character->getContentSize().height / 4
		);      //改变活动状态，传递鼠标选中指针



	if (
		isSelected
		)
	{                           
		
		this->isActive = !isActive;
		if (this->isActive)
		{
			selected->setOpacity(255);
		}
		else
		{
			selected->setOpacity(0);
		}
	}
	
	return false;

}








