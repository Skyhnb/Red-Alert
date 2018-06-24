#include "Player.h"
#include"SoldierSprite.h"

std::list<Soldier*> Player::playerSoldier = std::list<Soldier*>();
std::list<Construction*> Player::playerConstruction= std::list<Construction*>();
int Player::power_max=0;
int Player::power_cost = 0;
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
	for (iter = playerSoldier.begin(); iter != playerSoldier.end(); iter++)
	{
		if ((*iter)->hp <= 0)
		{
			(*iter)->removeFromParent();
		    playerSoldier.erase(iter);
		}
	}
	for (iter2 = playerConstruction.begin(); iter2 != playerConstruction.end(); iter2++)
	{
		if ((*iter2)->hp <= 0)
		{
			(*iter2)->removeFromParent();
			playerConstruction.erase(iter2);
		}
	}
	for (iter2 = playerConstruction.begin(); iter2 != playerConstruction.end(); iter2++)
	{
		temp_power+=(*iter2)->produce_power;
		temp_power_cost+=(*iter2)->cost_power;
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

SoldierMenu* SoldierMenu::createSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type)
{
	SoldierMenu* menu = SoldierMenu::create();
	if (menu)
	{
		menu->initSoldierMenu(position, SoldierPosition,soldier_type);
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return NULL;
}

void SoldierMenu::initSoldierMenu(Point position, Point SoldierPosition, sol_type soldier_type)
{
	switch (soldier_type)
	{
	case(american):
	{
		soldier_menu = Sprite::create("soldiermenu.jpg");
	}break;
	case(dog):
	{
		soldier_menu = Sprite::create("dogmenu.png");
	}break;
	}
	
	soldier_menu->setScale(1.0);
	soldier_menu->setPosition(position);
	this->addChild(soldier_menu);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SoldierMenu::onTouchBegan, this, SoldierPosition,soldier_type);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool SoldierMenu::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, Point SoldierPosition ,sol_type soldier_type)
{
	auto point = pTouch->getLocation();
	auto position = this->soldier_menu->getPosition();
	if (
		point.x > position.x - soldier_menu->getContentSize().width / 2 &&
		point.x<position.x + soldier_menu->getContentSize().width / 2 &&
		point.y>position.y - soldier_menu->getContentSize().height / 2 &&
		point.y < position.y + soldier_menu->getContentSize().height / 2
		)
	{
		Soldier* soldier = Soldier::createSoldier(SoldierPosition,soldier_type);
		this->addChild(soldier);
		Player::playerSoldier.push_back(soldier);
	}

	return false;

}

ConstructionMenu* ConstructionMenu::createConstructionMenu(Point position, cons_type construct_type)
{
	ConstructionMenu* menu = ConstructionMenu::create();
	if (menu)
	{
		menu->initConstructionMenu(position,construct_type);
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return NULL;
}
void ConstructionMenu::initConstructionMenu(Point position, cons_type construct_type)
{
	create_begin = false;

	switch (construct_type)
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
}
bool ConstructionMenu::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent,cons_type construct_type)
{
	auto point = pTouch->getLocation();
	auto position = this->construction_menu->getPosition();
	if (
		point.x > position.x - construction_menu->getContentSize().width / 2 &&
		point.x<position.x + construction_menu->getContentSize().width / 2 &&
		point.y>position.y - construction_menu->getContentSize().height / 2 &&
		point.y < position.y + construction_menu->getContentSize().height / 2
		)
	{
		if (Player::power_cost + _power_cost > Player::power_max)
		{
			return false;
		}
		construction->setPosition(point);
		construction->setOpacity(255);
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
		construction->setOpacity(0);
		Construction* construction = Construction::createConstruction(point,construct_type);
		this->addChild(construction);
		Player::playerConstruction.push_back(construction);
		create_begin = false;
	}
}

