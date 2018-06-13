#ifndef __Loading_SCENE_H__
#define __Loading_SCENE_H__

#include "cocos2d.h"

class Loading : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    //take  
	virtual bool init();

	void menuItemHelpCallback(cocos2d::Ref* pSender);
	void menuItemStartCallback(cocos2d::Ref* pSender);
	void menuItemSettingCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Loading);
};

#endif // __Loading_SCENE_H__
