#include "Construction.h"


Construction* Construction::createConstruction(Point position, cons_type construction_type, Layer* layer)
{
	Construction* construction = Construction::create();
	if (construction)
	{
		construction->initConstruction(position,construction_type,layer);
		return construction;
	}
	CC_SAFE_DELETE(construction);
	return NULL;
}
void Construction::initConstruction(Point position, cons_type construction_type, Layer* layer)
{

	switch (construction_type)
	{
	case(power):
	  {
		  character = Sprite::create("power.png");
		  hp = 500;
		  produce_power = 200;
		  cost_power = 0;
	  } break;
	case(miner):
	  {
		character = Sprite::create("miner.png");
		  hp = 500;
		  produce_power = 0;
		  cost_power = 50;
 	  }break;
	case(base):
	  {
		  character = Sprite::create("base.png");
		  hp = 1000;
		  produce_power =0;
	  	  cost_power = 0;
	  }break;
	case(armycamp):
	  {
		  character = Sprite::create("armycamp.png");
		  hp = 300;
		  produce_power = 0;
		  cost_power = 50;
	  }break;
	case(tankfac):
	  {
		  character = Sprite::create("tankfac.png");
		  hp = 500;
		  produce_power = 0;
		  cost_power = 200;
	  }break;
	}

	attackers = std::list<Soldier*>();
	_layer = layer;
	this_type = construction_type;

	character->setScale(1);
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
	std::list<Soldier*>::iterator tem_attacker;
	for (attacker = attackers.begin(); attacker != attackers.end();)
	{
		auto target_point = _layer->convertToNodeSpace(character->getPosition());
		auto attacker_point = _layer->convertToNodeSpace((*attacker)->character->getPosition());
		if (((*attacker)->speed != 3 && (*attacker)->speed != 5 && (*attacker)->speed != 8) || ((*attacker)->hp>200 || (*attacker)->hp<-200))
		{
			tem_attacker = attacker;
			attacker++;
			attackers.erase(tem_attacker);
		}
		else if (((attacker_point.x - target_point.x)*(attacker_point.x - target_point.x) + (attacker_point.y - target_point.y)*(attacker_point.y - target_point.y))
		>((*attacker)->range)*((*attacker)->range))
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
}//更新状态


void Construction::push_back_attacker(Soldier*attack)
{
	if (produce_power != 0 &&produce_power!= 200)
	{
		return;
	}
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
	auto _point = _layer->convertToNodeSpace(pTouch->getLocation());
	auto position = this->character->getPosition();
	this->isSelected = (
		_point.x > position.x - character->getContentSize().width / 2 &&
		_point.x<position.x + character->getContentSize().width / 2 &&
		_point.y>position.y - character->getContentSize().height / 2 &&
		_point.y < position.y + character->getContentSize().height / 2
		);      //改变活动状态，传递鼠标选中指针
	return false;

}