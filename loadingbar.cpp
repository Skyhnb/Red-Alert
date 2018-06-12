#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


    
    auto bar=Sprite::create("loadingbar.png");
    auto to1=ProgressTo::create(2,0);
    ProgressTimer *progress = ProgressTimer::create(bar);
    progress->setReverseDirection(true);
    progress->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    
    progress->setPercentage(100);
    progress->setType(cocos2d::ProgressTimer::Type::BAR);
    progress->setMidpoint(Vec2(1,0));
    progress->setBarChangeRate(Vec2(1,0));
    this->addChild(progress);
    
    progress->runAction(to1);
    auto label = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 label->getContentSize().height+visibleSize.height/2));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    
    return true;
}




}
