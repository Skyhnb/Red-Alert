#include "Player.h"
#include"SoldierSprite.h"

std::list<Soldier*> Player::playerSoldier = std::list<Soldier*>();
std::list<Construction*> Player::playerConstruction= std::list<Construction*>();
int Player::power_max=0;
int Player::power_cost = 0;
int Player::money = 0;
bool Player::construction_commit=false;
bool Player::tank_commit = false;
bool Player::soldier_commit = false;
Point Player::soldier_create_position = Point(1,1);
Point Player::tank_create_position = Point(1, 1);
Point Player::gather_position= Point(1, 1);
Player* Player::createPlayer()
{
	Player* player = Player::create();
	if (player)
	{
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}
void Player::initPlayer()
{
	construction_commit = false;
	soldier_commit=false;
	tank_commit = false;

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
	listener->setSwallowTouches(true);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
}
void Player::update(float dt)
{
	int temp_power = 0;
	int temp_power_cost = 0;
	std::list<Soldier*>::iterator tem_iter;
	std::list<Construction*>::iterator tem_iter2;
	for (iter = playerSoldier.begin(); iter != playerSoldier.end(); )
	{
		if ((*iter)->hp <= 0)
		{
			tem_iter = iter;
			iter++;
			(*tem_iter)->removeFromParent();
		    playerSoldier.erase(tem_iter);
		}
		else 
		{
			iter++;
		}
	}
	for (iter2 = playerConstruction.begin(); iter2 != playerConstruction.end(); )
	{
		if ((*iter2)->hp <= 0)
		{
			tem_iter2 = iter2;
			iter2++;
			(*tem_iter2)->removeFromParent();
			playerConstruction.erase(tem_iter2);
		}
		else
		{
			iter2++;
		}
	}
	for (iter2 = playerConstruction.begin(); iter2 != playerConstruction.end(); iter2++)
	{
		if ((*iter2)->this_type == armycamp)
		{
			soldier_commit = true;
			soldier_create_position = Point(((*iter2)->character->getPositionX() + (*iter2)->character->getContentSize().width/2+3), ((*iter2)->character->getPositionY()));
		}
		if ((*iter2)->this_type == tankfac)
		{
			tank_commit = true;
			tank_create_position = Point(((*iter2)->character->getPositionX() + (*iter2)->character->getContentSize().width/2+3), ((*iter2)->character->getPositionY()));
		}
		if ((*iter2)->this_type == base)
		{
			gather_position = Point(((*iter2)->character->getPositionX() + (*iter2)->character->getContentSize().width / 2+10), ((*iter2)->character->getPositionY()));
		}
		temp_power+=(*iter2)->produce_power;
		temp_power_cost+=(*iter2)->cost_power;
		if ((*iter2)->this_type == miner)
		{
			money += 2;
		}
	}
	power_max = temp_power;
	power_cost = temp_power_cost;
}
bool Player::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	non_object_Selected = true;

	no_soldier_Selected = true;
	for (iter = playerSoldier.begin(); iter != playerSoldier.end(); iter++)
	{
		no_soldier_Selected = no_soldier_Selected && !((*iter)->isSelected);
		non_object_Selected = non_object_Selected&&no_soldier_Selected;
	}

	no_construction_Selected = true;
	for (iter2 = playerConstruction.begin(); iter2 != playerConstruction.end(); iter2++)
	{
		no_construction_Selected = no_construction_Selected && !((*iter2)->isSelected);
		non_object_Selected = non_object_Selected&& no_construction_Selected;
	}
	return false;
}

Soldier*Player::getSelectedSoldier()
{
	for (iter = playerSoldier.begin(); iter != playerSoldier.end(); iter++)
	{
		if ((*iter)->isSelected)
		{
			return (*iter);
		}
	}
}
Construction* Player::getSelectedConstruction()
{
	for (iter2 = playerConstruction.begin(); iter2 != playerConstruction.end(); iter2++)
	{
		if ((*iter2)->isSelected)
		{
			return (*iter2);
		}
	}
}

SoldierMenu* SoldierMenu::createSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type,Layer* layer)
{
	SoldierMenu* menu = SoldierMenu::create();
	if (menu)
	{
		menu->initSoldierMenu(position, SoldierPosition,soldier_type,layer);
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return NULL;
}
void SoldierMenu::initSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type,Layer* layer)
{
	this_type = soldier_type;
	switch (this_type)
	{
	case(american):
	{
		soldier_menu = Sprite::create("soldiermenu.png");
		cost = 500;
	}break;
	case(dog):
	{
		soldier_menu = Sprite::create("dogmenu.png");
		cost = 300;
	}break;
	case(tank):
	{
		soldier_menu = Sprite::create("tankmenu.png");
		cost = 2000;
	}break;
	}
	
	cd_time = 300;
	waiting_soldier = 0;
	_layer = layer;
	soldier_Position = SoldierPosition;

	soldier_menu->setScale(1.0);
	soldier_menu->setPosition(position);
	this->addChild(soldier_menu);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SoldierMenu::onTouchBegan, this, soldier_type);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();

}
bool SoldierMenu::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, sol_type soldier_type)
{
	auto point = pTouch->getLocation();
	auto position = this->soldier_menu->getPosition();
	if (!Player::soldier_commit&&this_type!=tank)
	{
		return false;
	}
	if (this_type == tank && !Player::tank_commit)
	{
		return false;
	}
	if (
		point.x > position.x - soldier_menu->getContentSize().width / 2 &&
		point.x<position.x + soldier_menu->getContentSize().width / 2 &&
		point.y>position.y - soldier_menu->getContentSize().height / 2 &&
		point.y < position.y + soldier_menu->getContentSize().height / 2
		)
	{
		if (cost > Player::money)
		{
			return false;
		}
		waiting_soldier++;

		Player::money -= cost;
	}

	return false;

}
void SoldierMenu::update(float dt)
{
	cd_time++;
	if (waiting_soldier > 0 && cd_time > 300)
	{
		create_Soldier();
		waiting_soldier--;
		cd_time = 0;
	}
}
void SoldierMenu::create_Soldier()
{
	Point create_position;
	if (this_type == tank)
	{
		create_position=Player::tank_create_position;
	}
	else
	{
		create_position = Player::soldier_create_position;
	}
	Soldier* soldier = Soldier::createSoldier(create_position, this_type, _layer);
	_layer->addChild(soldier,10);
	Player::playerSoldier.push_back(soldier);
	soldier->isStop = false;
	MyMoveto* moveto = MyMoveto::create(20.0f, Player::gather_position, soldier->speed);
	soldier->runAction(moveto);
}

ConstructionMenu* ConstructionMenu::createConstructionMenu(Point position, cons_type construct_type,Layer* layer)
{
	ConstructionMenu* menu = ConstructionMenu::create();
	if (menu)
	{
		menu->initConstructionMenu(position,construct_type,layer);
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return NULL;
}
void ConstructionMenu::initConstructionMenu(Point position, cons_type construct_type,Layer* layer)
{
	create_begin = false;
	cd_time = 600;
	_layer = layer;
	this_type = construct_type;
	base_only = true;

	switch (this_type)
	{
	case(power):
	  {
		construction_menu = Sprite::create("powermenu.png");
		construction = Sprite::create("power.png");
		_power_cost = 0;
	  } break;
	case(miner):
	  {
		construction_menu = Sprite::create("minermenu.png");
	    construction = Sprite::create("miner.png");
		_power_cost = 50;
	  }break;
	case(base):
	  {
		construction_menu = Sprite::create("basemenu.png");
		construction = Sprite::create("base.png");
		_power_cost = 0;
	  }break;
	case(armycamp):
	  {
		construction_menu = Sprite::create("armycampmenu.png");
		construction = Sprite::create("armycamp.png");
		_power_cost = 100;
	  }break;
	case(tankfac):
	  {
		construction_menu = Sprite::create("tankfacmenu.png");
		construction = Sprite::create("tankfac.png");
		_power_cost = 200;
	  }break;
	}

	
	construction_menu->setScale(1.0);
	construction_menu->setPosition(position);
	this->addChild(construction_menu);

	
	construction->setScale(1.0);
	construction->setPosition(position);
	construction->setOpacity(0);
	this->addChild(construction);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(ConstructionMenu::onTouchBegan, this,construct_type);
	listener->onTouchMoved = CC_CALLBACK_2(ConstructionMenu::onTouchMoved, this,construct_type);
	listener->onTouchEnded = CC_CALLBACK_2(ConstructionMenu::onTouchEnded, this,construct_type);
	listener->setSwallowTouches(false);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
}
void ConstructionMenu::update(float dt)
{
	cd_time++;
	if (this_type != base && !Player::construction_commit)
	{
		construction_menu->setOpacity(100);
	}
	else if (Player::power_cost + _power_cost > Player::power_max || cd_time<600)
	{
		construction_menu->setOpacity(100);
	}
	else
	{
		construction_menu->setOpacity(255);
	}
	if (this_type == base && !base_only)
	{
		construction_menu->setOpacity(100);
	}
}
bool ConstructionMenu::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent,cons_type construct_type)
{
	auto point = pTouch->getLocation();
	auto position = this->construction_menu->getPosition();
	if (!(this_type == base || Player::construction_commit))
	{
		return false;
	}
	if (!base_only)
	{
		return false;
	}
	if (
		point.x > position.x - construction_menu->getContentSize().width / 2 &&
		point.x<position.x + construction_menu->getContentSize().width / 2 &&
		point.y>position.y - construction_menu->getContentSize().height / 2 &&
		point.y < position.y + construction_menu->getContentSize().height / 2
		)
	{
		if (Player::power_cost + _power_cost > Player::power_max||cd_time<600)
		{
			return false;
		}
		construction->setPosition(point);
		construction->setOpacity(128);
		create_begin = true;
	}

	return true;

}
void ConstructionMenu::onTouchMoved(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type)
{
	if (create_begin)
	{
		auto point = pTouch->getLocation();
		construction->setPosition(point);
	}

}
void ConstructionMenu::onTouchEnded(CCTouch* pTouch, CCEvent* pEvent, cons_type construct_type)
{
	if (create_begin)
	{
		auto point = pTouch->getLocation();
		auto _point = _layer->convertToNodeSpace(pTouch->getLocation());
		auto _point_menu= _layer->convertToNodeSpace(construction_menu->getPosition());
		construction->setOpacity(0);
		for (iter2 = Player::playerConstruction.begin(); iter2 != Player::playerConstruction.end(); iter2++)
		{
			if (
				(((_point.x - (*iter2)->character->getPositionX()) < ((*iter2)->character->getContentSize().width / 2 + construction->getContentSize().width / 2))
				&& ((_point.x - (*iter2)->character->getPositionX()) > (-(*iter2)->character->getContentSize().width / 2 - construction->getContentSize().width / 2))
				&& ((_point.y - (*iter2)->character->getPositionY()) < ((*iter2)->character->getContentSize().height / 2 + construction->getContentSize().height / 2))
				&& ((_point.y - (*iter2)->character->getPositionY()) > (-(*iter2)->character->getContentSize().height / 2 - construction->getContentSize().height / 2)))
				||
				((_point.x<_point_menu.x+ construction_menu->getContentSize().width / 2)
				&& (_point.x>_point_menu.x - construction_menu->getContentSize().width / 2)
				&& (_point.y<_point_menu.y + construction_menu->getContentSize().height / 2)
				&&(_point.y>_point_menu.y - construction_menu->getContentSize().height / 2))
				)
			{
				create_begin = false;
				return;
			}
		}
		if (this_type == base)
		{
			base_only = false;
			Player::construction_commit = true;
		}
		Construction* _construction = Construction::createConstruction(point,construct_type,_layer);
		_layer->addChild(_construction,10);//建筑，小兵的优先值相等
		_construction->character->setPosition(_point);
		Player::playerConstruction.push_back(_construction);
		create_begin = false;
		cd_time = 0;
	}
}

