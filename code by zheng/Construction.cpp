#include "Construction.h"


Construction* Construction::createConstruction(Point position, cons_type construction_type)
{
	Construction* construction = Construction::create();
	if (construction)
	{
		construction->initConstruction(position,construction_type);
		return construction;
	}
	CC_SAFE_DELETE(construction);
	return NULL;
}
void Construction::initConstruction(Point position, cons_type construction_type)
{

	switch (construction_type)
	{
	case(power):
	  {
		  character = Sprite::create("power.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
		  cost_money=100;
	  } break;
	case(miner):
	  {
		character = Sprite::create("miner.png");
		  hp = 500;
		  produce_power = 0;
		  cost_power = 50;
		  cost_money = 100;
 	  }break;
	case(base):
	  {
		  character = Sprite::create("base.png");
		  hp = 500;
		  produce_power = 200;
	  	  cost_power = 0;
		  cost_money = 100;
	  }break;
	case(armycamp):
	  {
		  character = Sprite::create("armycamp.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
		  cost_money = 100;
	  }break;
	case(tankfac):
	  {
		  character = Sprite::create("tankfac.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
		  cost_money = 100;
	  }break;
	}

	attackers = std::list<Soldier*>();


	character->setScale(0.5);
	character->setPosition(position);
	this->addChild(character);//非选中状态图

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Construction::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//触摸事件监听器

	this->scheduleUpdate();//随时更新状态
	this->schedule(schedule_selector(Construction::updateattack), 1.0f, kRepeatForever, 0);//执行攻击函数的刷新
}

void Construction::update(float dt)
{
	
}//更新状态


void Construction::push_back_attacker(Soldier*attack)
{
	attackers.push_back(attack);
}//添加攻击者
void Construction::updateattack(float dt)
{
	for (attacker = attackers.begin(); attacker != attackers.end(); attacker++)
	{
		hp -= (*attacker)->atk;
	}
}//执行攻击函数


bool Construction::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	auto position = this->character->getPosition();
	this->isSelected = (
		point.x > position.x - character->getContentSize().width / 4 &&
		point.x<position.x + character->getContentSize().width / 4 &&
		point.y>position.y - character->getContentSize().height / 4 &&
		point.y < position.y + character->getContentSize().height / 4
		);      //改变活动状态，传递鼠标选中指针
	return false;

}