#include "Manager.h"

Manager* Manager::createManager()
{
	Manager* manager = Manager::create();
	if (manager)
	{
		manager->initManager();
		return manager;
	}
	CC_SAFE_DELETE(manager);
	return NULL;
}

void Manager::initManager()
{
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Manager::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Manager::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	auto point = pTouch->getLocation();
	for (player = players.begin(); player!= players.end(); player++)
	{
		if ((*player)->nonSelected)
		{
			for (soldier = ((*player)->playerSoldier).begin(); soldier!=((*player)->playerSoldier).end(); soldier++)
			{
				if ((*soldier)->isActive)
				{
					(*soldier)->character->setPosition(point);
				}
			}
		}
	}
	return false;
}


void Manager::push_back(Player *player)
{
	players.push_back(player);
}