//
//  RoomScene.hpp
//  gameover
//
//  Created by anonym_co on 2018/6/21.
//

#ifndef RoomScene_hpp
#define RoomScene_hpp

#include <stdio.h>
#include <cocos-ext.h>

USING_NS_CC_EXT;
USING_NS_CC;
class CreateRoom:public cocos2d::Scene
{
private:
    
public:
    virtual bool init();
    
    static cocos2d::Scene* createScene();
    
	void menuOkCallback(cocos2d::Ref* pSender);
    virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
    virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);
    CREATE_FUNC(CreateRoom);
};
#endif /* RoomScene_hpp */
