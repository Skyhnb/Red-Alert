#include<cocos2d.h>
#include<iostream>
#include"InputNameScene.h"
#include"PlayerData.h"

USING_NS_CC;

/*PlayerData Player;*//*这个玩家数据类应该定义在GameScene里面这里做测试用，用来储存玩家输入的姓名*/
//std::string myname;


Scene*InputNameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = InputNameScene::create();
	scene->addChild(layer);
	return scene;
}

bool InputNameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	Sprite *bg = Sprite::create("background1.jpg");

	// position the label on the center of the screen
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(bg);

	auto OKItem = MenuItemImage::create("NAMEButtonSelected.png", "NAMEButtonSelected.png", CC_CALLBACK_1(InputNameScene::menuOKCallback, this));
	OKItem->setPosition(Director::getInstance()->convertToGL(Vec2(540,640)));

	auto menu = Menu::create(OKItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	auto Name_Editbox = EditBox::create(CCSizeMake(250, 50), Scale9Sprite::create("NAMEButtonNormal.png"));
	Name_Editbox->setPosition(ccp(visibleSize.width / 4, visibleSize.height / 2));
	Name_Editbox->setFontColor(Color3B(255, 0, 0));//设置字体颜色
	Name_Editbox->setPlaceHolder("Name:");//设置预置文本 
	Name_Editbox->setMaxLength(30);//设置最大长度
	Name_Editbox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);//可以输入任何，但是不包括换行
	Name_Editbox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//设置输入标志位
	Name_Editbox->setReturnType(cocos2d::ui::EditBox::KeyboardReturnType::DONE);//设置返回类型
	Name_Editbox->setPlaceholderFontName("Arial");//设置字体
	this->addChild(Name_Editbox);

	return true;
}


void InputNameScene::editBoxEditingDidBegin(cocos2d::extension::EditBox* editBox) {}
void InputNameScene::editBoxEditingDidEnd(cocos2d::extension::EditBox* editBox) {}
void InputNameScene::editBoxTextChanged(cocos2d::extension::EditBox* editBox, const std::string &text)
{
	auto editbox = (EditBox*)editBox;
	/*myname = text;*/
}
void InputNameScene::editBoxReturn(cocos2d::extension::EditBox *editBox){}


void InputNameScene::menuOKCallback(Ref* pSender)
{

}
