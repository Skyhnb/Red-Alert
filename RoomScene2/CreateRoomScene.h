#ifndef RoomScene_h
#define RoomScene_h

#include<iostream>
#include"cocos2d.h"
#include"cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//房间界面 显示加入或创建房间

class RoomScene:public cocos2d::Layer
{
public:
    void menuGoToRoomScene(Ref* pSender);
    void menuGoToFindScene(Ref* pSender);
    
    static cocos2d::Scene* createScene(Client* c, int mode, std::string _playerName);
    
    virtual bool init();
    
    

    CREATE_FUNC(RoomScene);
};

#endif
