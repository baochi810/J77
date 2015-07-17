#include "MainScene.h"
#include "AchiScene.h"
#include "ShopScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto achiItem = MenuItemImage::create(
                                           "achi.png",
                                           "achihi.png",
                                           CC_CALLBACK_1(MainScene::menuAchiCallback, this));
    
	achiItem->setPosition(Vec2(origin.x + visibleSize.width - achiItem->getContentSize().width / 2,
		origin.y + achiItem->getContentSize().height / 2));

	auto shopItem = MenuItemImage::create(
		"shop.png",
		"shophi.png",
		CC_CALLBACK_1(MainScene::menuShopCallback, this));

	shopItem->setPosition(Vec2(origin.x + visibleSize.width - shopItem->getContentSize().width / 2 - achiItem->getContentSize().width,
		origin.y + shopItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
	auto menu = Menu::create(achiItem, shopItem, NULL);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add "MainScene" splash screen"
    auto sprite = Sprite::create("gem.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void MainScene::menuAchiCallback(Ref* pSender)
{
	auto myscene = Achi::createScene();
	Director::getInstance()->replaceScene(myscene);
}

void MainScene::menuShopCallback(Ref* pSender)
{
	auto myscene = Shop::createScene();
	Director::getInstance()->replaceScene(myscene);
}
