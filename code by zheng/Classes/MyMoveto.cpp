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
	_isDone = false;

	if (ActionInterval::initWithDuration(duration))
	{
		_endPosition = endPosition;
		_target_position = _endPosition;
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
	_positionDelta = _target_position - soldier_target->character->getPosition();
	if (_target)
	{
#if CC_ENABLE_STACKABLE_ACTIONS
		std::list<Soldier*>::iterator iter;
		std::list<Construction*>::iterator iter2;
		covered = false;
		for (iter2 = Player::playerConstruction.begin(); iter2 != Player::playerConstruction.end(); iter2++)
		{
			Vec2 target_construction= (*iter2)->character->getPosition();
			Vec2 target_construction_size = (*iter2)->character->getContentSize();
			if (
				(
				(((target_construction.x - soldier_target->character->getPositionX()) <=(soldier_target->character->getContentSize().width / 2 + target_construction_size.x / 2))
				&& ((target_construction.x - soldier_target->character->getPositionX()) >= (soldier_target->character->getContentSize().width / 2 + target_construction_size.x / 2)-_speed+1))

				|| 
					(((target_construction.x - soldier_target->character->getPositionX()) >= (-soldier_target->character->getContentSize().width / 2 - target_construction_size.x / 2))
				&& ((target_construction.x - soldier_target->character->getPositionX()) <= (-soldier_target->character->getContentSize().width / 2 - target_construction_size.x / 2)+_speed-1))
				)
				&& ((target_construction.y - soldier_target->character->getPositionY()) < (soldier_target->character->getContentSize().height / 2 + target_construction_size.y / 2))
				&& ((target_construction.y - soldier_target->character->getPositionY()) > (-soldier_target->character->getContentSize().height / 2 - target_construction_size.y / 2))
				)
			{
				if (_endPosition.y > target_construction.y)
				{
					_target_position = Point(soldier_target->character->getPositionX(), target_construction.y+target_construction_size.y  + 2);
				}
				else
				{
					_target_position = Point(soldier_target->character->getPositionX(), target_construction.y- target_construction_size.y  - 2);
				}
			}
			if (
				
				(((target_construction.x - soldier_target->character->getPositionX()) < (soldier_target->character->getContentSize().width / 2 + target_construction_size.x / 2))
				&& ((target_construction.x - soldier_target->character->getPositionX()) > (-soldier_target->character->getContentSize().width / 2 - target_construction_size.x / 2)))
					&&
				(
				(((target_construction.y - soldier_target->character->getPositionY()) <= (soldier_target->character->getContentSize().height / 2 + target_construction_size.y / 2))
				&& ((target_construction.y - soldier_target->character->getPositionY()) >= (soldier_target->character->getContentSize().height / 2 + target_construction_size.y / 2)-_speed+1))	
				
				||
				 ((target_construction.y - soldier_target->character->getPositionY()) >= (-soldier_target->character->getContentSize().height / 2 - target_construction_size.y / 2))
				&& ((target_construction.y - soldier_target->character->getPositionY()) <=(-soldier_target->character->getContentSize().height / 2 - target_construction_size.y / 2)+_speed-1)
				)
				)
			{

				if (_endPosition.x > target_construction.x)
				{
					_target_position = Point(target_construction.x + target_construction_size.x + 2, soldier_target->character->getPositionY());
				}
				else
				{
					_target_position = Point(target_construction.x - target_construction_size.x -  2, soldier_target->character->getPositionY());
				}
			}

		}

		_positionDelta = _target_position - soldier_target->character->getPosition();//根据建筑物碰撞结果改变目标位置

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
						if ((*iter)->isStop)
						{
							_isDone = true;
						}
					}
				}
			}//根据小兵间碰撞结果确认停止或暂停情况
		}

		if (covered)
		{

		}
		else
		{
			if(((soldier_target->character->getPositionX() - _endPosition.x)*(soldier_target->character->getPositionX() - _endPosition.x) +
				(soldier_target->character->getPositionY() - _endPosition.y)*(soldier_target->character->getPositionY() - _endPosition.y)) >50)
			{
				Vec2 currentPos = soldier_target->character->getPosition();
				Vec2 newPos = currentPos + (_positionDelta * _speed / sqrt(_positionDelta.x*_positionDelta.x + _positionDelta.y*_positionDelta.y));
				soldier_target->character->setPosition(newPos);
			}
			else
			{
				soldier_target->isStop=true;
				_isDone = true;
			}
			if (((soldier_target->character->getPositionX() - _target_position.x)*(soldier_target->character->getPositionX() - _target_position.x) +
				(soldier_target->character->getPositionY() - _target_position.y)*(soldier_target->character->getPositionY() - _target_position.y)) < 10)
			{
				_target_position = _endPosition;
			}
		}
#else
		_target->setPosition(_startPosition + _positionDelta * t);
#endif // CC_ENABLE_STACKABLE_ACTIONS
	}
}

bool MyMoveto::isDone(void) const
{
	return _isDone;
}


NS_CC_END