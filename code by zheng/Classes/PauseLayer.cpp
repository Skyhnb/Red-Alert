#include "PauseLayer.h"
#include "SettingScene.h"

USING_NS_CC;
  
//把一个正在运行的游戏的截图作为这个暂停对话框的背景   

Scene* GamePause::scene(RenderTexture* sqr)
{

	Scene *scene = Scene::create();
	GamePause *layer = GamePause::create();
	scene->addChild(layer, 1);

	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite  
	//并将Sprite添加到GamePause场景层中  
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	Sprite *back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());

	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。  
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同  
	back_spr->setColor(Color3B(127.5, 127.5, 127.5)); //图片颜色变灰色   

	scene->addChild(back_spr,0);
	return scene;
}

bool GamePause::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::sharedDirector()->getVisibleSize(); 
	Point origin = Director::sharedDirector()->getVisibleOrigin();

	//继续游戏按钮  
	MenuItemImage *pContinueItem = MenuItemImage::create(
		"menu/backnormal.png",
		"menu/backdown.png",
		this,
		menu_selector(GamePause::menuContinueCallback));
	pContinueItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3 * 2));

	//设置
	MenuItemImage *settingMenuItem = MenuItemImage::create(
		"menu/settingsnormal.png",
		"menu/settingsdown.png",
		CC_CALLBACK_1(GamePause::menuSettingCallback, this));
	settingMenuItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 3));

	Menu* pMenu = Menu::create(pContinueItem, settingMenuItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 3);

	return true;
}

//回到游戏
void GamePause::menuContinueCallback(Object* pSender)
{
    Director::sharedDirector()->popScene();
}

//转到设置
void GamePause::menuSettingCallback(Object* pSender)
{
	auto sc = Setting::createScene();
	auto reScene = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(reScene);
}