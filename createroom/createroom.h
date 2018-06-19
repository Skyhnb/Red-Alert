#ifndef __CREATEROOM_SCENE_H__
#define __CREATEROOM_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class CreateRoom : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void menuGoToMainScene(CCObject* pSender);
    
    void SceneCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(CreateRoom);
};

#endif //__GAMEOVER_SCENE_H
