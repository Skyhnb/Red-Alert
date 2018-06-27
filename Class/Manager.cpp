#include "Manager.h"
bool Manager::attack_mode = false;
Manager* Manager::createManager(Layer*_map, Layer* _sprite)
{
	Manager* manager = Manager::create();
	if (manager)
	{
		manager->initManager(_map, _sprite);
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}

void Manager::initManager(Layer*_map, Layer* _sprite)
{
	_mapLayer = _map;
	_sprite = _sprite;

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Manager::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//创立鼠标监听事件

	key_listener = EventListenerKeyboard::create();
	key_listener->onKeyReleased = CC_CALLBACK_2(Manager::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(key_listener, this);
}

bool Manager::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	auto point = pTouch->getLocation();
	auto _point = _mapLayer->convertToNodeSpace(pTouch->getLocation());
	non_player_Selected = true;

	for (player = players.begin(); player != players.end(); player++)
	{
		if (!(*player)->non_object_Selected)
		{
			non_player_Selected = false;//加入网络库时将攻击敌人函数写在这里
		}
	}//遍历确定是否无玩家的建筑、兵种被选中（即是否点中的是空地）


	if (non_player_Selected)
	{
		for (soldier = players[0]->playerSoldier.begin(); soldier != players[0]->playerSoldier.end(); soldier++)
		{
			if ((*soldier)->isActive)
			{
				(*soldier)->stopAllActions();
			}
		}
		for (soldier = (players[0]->playerSoldier).begin(); soldier!=(players[0]->playerSoldier).end(); soldier++)
		{
			if ((*soldier)->isActive)
			{
				(*soldier)->isStop = false;
				MyMoveto* moveto = MyMoveto::create(20.0f, _point, (*soldier)->speed);
				(*soldier)->runAction(moveto);
				(*soldier)->_attacking = false;
			}
		}
	}
	else if (attack_mode==true)
	{
		for (soldier = (players[0]->playerSoldier).begin(); soldier != (players[0]->playerSoldier).end(); soldier++)
		{
			if ((*soldier)->isActive&&!players[0]->no_soldier_Selected)
			{
				if ((*soldier) != players[0]->getSelectedSoldier())
				{
					Soldier* _attacker = *soldier;
					(*soldier)->isStop = false;
					_attacker->_attacking = true;
					Soldier* _target = players[0]->getSelectedSoldier();
					Point target_position = _target->character->getPosition();
					Point attacker_position = _attacker->character->getPosition();
					Point attack_position= target_position-(target_position-attacker_position) * _attacker->range/sqrt((target_position.x - attacker_position.x)*(target_position.x - attacker_position.x)+ (target_position.y - attacker_position.y)*(target_position.y - attacker_position.y));
					float move_t = sqrt((attack_position.x - attacker_position.x)*(attack_position.x - attacker_position.x) + (attack_position.y - attacker_position.y)*(attack_position.y - attacker_position.y)) / (*soldier)->speed;
					MyMoveto* moveto = MyMoveto::create(move_t, attack_position, (*soldier)->speed);
					CallFunc* attack_func = CallFunc::create([this, _attacker, _target]() {
						attack(_attacker, _target);
					});
					Action * action = Sequence::create(moveto, attack_func, NULL);
					(*soldier)->runAction(action);
				}
			}
			else if ((*soldier)->isActive && !players[0]->no_construction_Selected)
			{
				attack((*soldier), players[0]->getSelectedConstruction());
				{		
					Soldier* _attacker = *soldier;
					(*soldier)->isStop = false;
					_attacker->_attacking = true;
					Construction* _target = players[0]->getSelectedConstruction();
					Point target_position = _target->character->getPosition();
					Point attacker_position = _attacker->character->getPosition();
					Point attack_position = target_position - (target_position - attacker_position) * _attacker->range / sqrt((target_position.x - attacker_position.x)*(target_position.x - attacker_position.x) + (target_position.y - attacker_position.y)*(target_position.y - attacker_position.y));
					float move_t = sqrt((attack_position.x - attacker_position.x)*(attack_position.x - attacker_position.x) + (attack_position.y - attacker_position.y)*(attack_position.y - attacker_position.y)) / (*soldier)->speed;
					MyMoveto* moveto = MyMoveto::create(move_t, attack_position, (*soldier)->speed);
					CallFunc* attack_func = CallFunc::create([this, _attacker, _target]() {
						attack(_attacker, _target);
					});
					Action * action = Sequence::create(moveto, attack_func, NULL);
					(*soldier)->runAction(action);
				}
			}
		}
		attack_mode = false;
	}
	return false;
}

bool Manager::onKeyReleased(EventKeyboard::KeyCode keycode, Event* pEvent)
{
	switch (keycode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
	   {
		   for (soldier = (players[0]->playerSoldier).begin(); soldier != (players[0]->playerSoldier).end(); soldier++)
		   {
				(*soldier)->isActive=true;
		   }
	   }  break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
	  {
		  for (soldier = (players[0]->playerSoldier).begin(); soldier != (players[0]->playerSoldier).end(); soldier++)
		  {
			  (*soldier)->isActive = false;
		  }
	  }    break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	  {
		  attack_mode = true;
	  }  break;
	}
	return false;
}



void Manager::attack(Soldier* attacker, Soldier* defender)
{
	attacker->_attacking = true;
	defender->push_back_attacker(attacker);
}
void Manager::attack(Soldier* attacker, Construction* defender)
{
	attacker->_attacking = true;
	defender->push_back_attacker(attacker);
}

void Manager::push_back(Player *player)
{
	players.push_back(player);
}//向管理层加入玩家对象