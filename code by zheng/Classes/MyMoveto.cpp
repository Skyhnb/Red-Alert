#include "MyMoveto.h"
#include "2d/CCActionInterval.h"



NS_CC_BEGIN

MyMoveto* MyMoveto::create(float duration, const Vec2& endPosition,int speed)
{
	MyMoveto *ret = new (std::nothrow) MyMoveto();

	if (ret)
	{
		if (ret->initWithDuration(duration, endPosition,speed))
		{
			ret->autorelease();
		}
		else
		{
			delete ret;
			ret = nullptr;
		}
	}

	return ret;
}

bool MyMoveto::initWithDuration(float duration, const Vec2& endPosition,float speed)
{
	bool ret = false;
	covered = false;
	_speed = speed;

	if (ActionInterval::initWithDuration(duration))
	{
		_endPosition = endPosition;
		ret = true;
	}

	return ret;
}

void MyMoveto::startWithTarget(Node *target)
{
	ActionInterval::startWithTarget(target);
	Soldier* soldier_target = static_cast<Soldier*>(target);
	_positionDelta = _endPosition - soldier_target->character->getPosition();
}


void MyMoveto::update(float t)
{
	Soldier* soldier_target=static_cast<Soldier*>(_target);
	if (_target)
	{
#if CC_ENABLE_STACKABLE_ACTIONS
		std::list<Soldier*>::iterator iter;
		covered = false;
		for (iter = Player::playerSoldier.begin(); iter != Player::playerSoldier.end(); iter++)
		{
			Vec2 another_soldier = (*iter)->character->getPosition();
			Vec2 another_soldier_size= (*iter)->character->getContentSize();
			if (another_soldier!=soldier_target->character->getPosition())
			{
				if (
					((another_soldier.x - soldier_target->character->getPositionX()) < (soldier_target->character->getContentSize().width/2+ another_soldier_size.x/2) )
					&& ((another_soldier.x - soldier_target->character->getPositionX() )>( -soldier_target->character->getContentSize().width/2- another_soldier_size.x/2) )
					&& ((another_soldier.y - soldier_target->character->getPositionY()) <( soldier_target->character->getContentSize().height/2+ another_soldier_size.y/2) )
					&& ((another_soldier.y - soldier_target->character->getPositionY()) > (-soldier_target->character->getContentSize().height/2- another_soldier_size.y/2) )
					)
				{
					if (
						((soldier_target->character->getPositionX()- _endPosition.x)*(soldier_target->character->getPositionX() - _endPosition.x) +
						(soldier_target->character->getPositionY() - _endPosition.y)*(soldier_target->character->getPositionY() - _endPosition.y))>
						((another_soldier.x - _endPosition.x)*(another_soldier.x - _endPosition.x)+
						(another_soldier.y - _endPosition.y)*(another_soldier.y - _endPosition.y))
						)
					{
						covered = true;
					}
				}
			}
		}

		if (covered)
		{

		}
		else
		{
			if(((soldier_target->character->getPositionX() - _endPosition.x)*(soldier_target->character->getPositionX() - _endPosition.x) +
				(soldier_target->character->getPositionY() - _endPosition.y)*(soldier_target->character->getPositionY() - _endPosition.y)) >200)
			{
				Vec2 currentPos = soldier_target->character->getPosition();
				Vec2 newPos = currentPos + (_positionDelta * _speed / sqrt(_positionDelta.x*_positionDelta.x + _positionDelta.y*_positionDelta.y));
				soldier_target->character->setPosition(newPos);
			}
		}
#else
		_target->setPosition(_startPosition + _positionDelta * t);
#endif // CC_ENABLE_STACKABLE_ACTIONS
	}
}


NS_CC_END