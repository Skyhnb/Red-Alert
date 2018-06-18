#pragma once
#ifndef __CINNAME_SCENE_H__
#define __CINNAME_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;

class CinName : public cocos2d::Layer /*,public EditBoxDelegate*/
{
public:
	static cocos2d::Scene* createScene(); 
	virtual bool init();

	void menuOkCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(CinName);
};

#endif 
