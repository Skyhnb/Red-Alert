#ifndef __MYMOVETO_H__
#define __MYMOVETO_H__

#include <vector>

#include "2d/CCAction.h"
#include "2d/CCAnimation.h"
#include "base/CCProtocols.h"
#include "base/CCVector.h"
#include"2d\CCActionInterval.h"
#include"Player.h"
#include"SoldierSprite.h"

NS_CC_BEGIN


class  MyMoveto :public ActionInterval
{
public:
	static MyMoveto* create(float duration, const Vec2& endPosition,int speed);
	virtual void startWithTarget(Node *target) override;
	virtual void update(float time) override;

CC_CONSTRUCTOR_ACCESS:
	MyMoveto() {};
	virtual ~MyMoveto() {};

	bool initWithDuration(float duration, const Vec2& deltaPosition,float speed);
	bool covered;

protected:
	Vec2 _positionDelta;
	Vec2 _endPosition;

	float _speed;


private:
	CC_DISALLOW_COPY_AND_ASSIGN(MyMoveto);
};

NS_CC_END
#endif
