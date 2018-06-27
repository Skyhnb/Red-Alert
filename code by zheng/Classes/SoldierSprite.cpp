#include "SoldierSprite.h"

Soldier* Soldier::createSoldier(Point position, sol_type soldier_type, Layer* layer)
{
	Soldier* soldier = Soldier::create();
	if (soldier)
	{
		soldier->initSoldier(position, soldier_type,layer);
		return soldier;
	}
	CC_SAFE_DELETE(soldier);
	return NULL;
}

void Soldier::initSoldier(Point position, sol_type soldier_type, Layer* layer)
{
	this->isActive = false;
	isStop = true;
	this_type = soldier_type;
	switch (this_type)
	{
	case(american):
	  {
		hp = 50;
		atk = 10; 
		range = 80;
		speed = 3;
		character = Sprite::create("soldier.png");
		selected = Sprite::create("selected.png");
	  }break;
	case(dog):
	  {
		hp = 20;
		atk = 15;
		range = 10;
		speed = 5;
		character = Sprite::create("dog.png");
		selected = Sprite::create("dog_selected.png");
	  }break;
	case(tank):
	  {
		hp = 200;
		atk = 50;
		range = 400;
		speed = 8;
		character = Sprite::create("tank.png");
		selected = Sprite::create("tank_selected.png");
	  }
	}
	

	attackers = std::list<Soldier*>();
	_layer = layer;

	character->setScale(1);
    character->setPosition(position);
	//character->setPositionY(position.y);//测试用
	this->addChild(character);//非选中状态图


	auto characterSize = character->getContentSize();
	selected->setPosition(characterSize.width / 2, characterSize.height / 2);
	selected->setOpacity(0);
	character->addChild(selected);//选中状态图

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Soldier::onTouchBegan, this);
	listener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//触摸事件监听器

	this->scheduleUpdate();//随时更新状态
	this->schedule(schedule_selector(Soldier::updateattack), 0.5f, kRepeatForever, 0);//执行攻击函数的刷新
}
void Soldier::update(float dt)
{
	std::list<Soldier*>::iterator tem_attacker;
	if (this->isActive)
	{
		selected->setOpacity(255);
		character->setOpacity(0);
	}
	else
	{
		selected->setOpacity(0);
		character->setOpacity(255);
	}//更新选中状态
	for (attacker = attackers.begin(); attacker != attackers.end();)
	{
		auto target_point = _layer->convertToNodeSpace(character->getPosition());
		auto attacker_point = _layer->convertToNodeSpace((*attacker)->character->getPosition());
		if (((*attacker)->speed != 3 && (*attacker)->speed!= 5&&(*attacker)->speed!=8)||((*attacker)->hp>200|| (*attacker)->hp<-200))
		{
			tem_attacker = attacker;
			attacker++;
			attackers.erase(tem_attacker);
		}
		else if (((attacker_point.x-target_point.x)*(attacker_point.x - target_point.x) + (attacker_point.y - target_point.y)*(attacker_point.y - target_point.y))
		>((*attacker)->range+10)*((*attacker)->range+10))
		{
			tem_attacker = attacker;
			attacker++;
			(*tem_attacker)->_attacking = false;
			attackers.erase(tem_attacker);
		}	
		else
		{
			attacker++;
		}
	}
	for (attacker = attackers.begin(); attacker != attackers.end();)
	{
		tem_attacker = attacker;
		attacker++;
		if ((*tem_attacker)->_attacking = false)
		{
			attackers.erase(tem_attacker);
		}
	}
	//更新攻击者信息
}

void Soldier::push_back_attacker(Soldier* attack)
{
	attackers.push_back(attack);
}//添加攻击者
void Soldier::updateattack(float dt)
{
	for (attacker = attackers.begin(); attacker != attackers.end(); attacker++)
	{
		hp -= (*attacker)->atk;
	}
}//执行攻击函数

bool Soldier::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto _point = _layer->convertToNodeSpace(pTouch->getLocation());
	auto position = this->character->getPosition();
	this->isSelected = (
		_point.x > position.x - character->getContentSize().width / 2 &&
		_point.x<position.x + character->getContentSize().width / 2 &&
		_point.y>position.y - character->getContentSize().height / 2 &&
		_point.y < position.y + character->getContentSize().height / 2
		);      //改变活动状态，传递鼠标选中指针


	if (isSelected)
	{                           
		this->isActive = !isActive;
	}
	

	return false;

}








