#ifndef _INPUTNAMESCENE_H_
#define _INPUTNAMESCENE_H_
#include "cocos2d.h"  
#include "cocos-ext.h"
#include "ui/CocosGUI.h"


USING_NS_CC_EXT;

class InputNameScene : public cocos2d::Layer, public EditBoxDelegate
{
protected:
	std::string     _playerName;            //Íæ¼ÒÃû³Æ

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text);
	virtual void editBoxReturn(cocos2d::extension::EditBox *editBox);

	CREATE_FUNC(InputNameScene);

};


#endif /*_INPUTNAMESCENE_H_*/