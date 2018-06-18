#include "Player.h"
#include"SoldierSprite.h"

std::list<Soldier*> Player::playerSoldier = std::list<Soldier*>();
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
}
bool Player::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	nonSelected = true;
	for (iter = playerSoldier.begin(); iter != playerSoldier.end(); iter++)
	{
		nonSelected = nonSelected && !((*iter)->isSelected);
	}
	return false;
}


SoldierMenu* SoldierMenu::createSoldierMenu(Point position, Point SoldierPosition)
{
	SoldierMenu* menu = SoldierMenu::create();
	if (menu)
	{
		menu->initSoldierMenu(position, SoldierPosition);
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return NULL;
}

void SoldierMenu::initSoldierMenu(Point position, Point SoldierPosition)
{
	soldiermenu = Sprite::create("soldiermenu.png");
	soldiermenu->setScale(1.0);
	soldiermenu->setPosition(position);
	this->addChild(soldiermenu);

	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SoldierMenu::onTouchBegan, this, SoldierPosition);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool SoldierMenu::onTouchBegan(CCTouch* pTouch, CCEvent* pEvent, Point SoldierPosition)
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
		Soldier* soldier = Soldier::createSoldier(SoldierPosition);
		this->addChild(soldier);
		Player::playerSoldier.push_back(soldier);
	}

	return false;

}
