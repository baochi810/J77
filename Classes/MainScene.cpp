#include "MainScene.h"
#include "AchiScene.h"
#include "ShopScene.h"
#include "FacebookAgent.h"
#include "MyAdsListener.h"
#include "PluginManager.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "AdmobHelper.h"

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
	sdkbox::PluginGoogleAnalytics::logScreen("Main Menu");

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
    
    auto fbItem = MenuItemImage::create(
                                          "home.png",
                                          "homehi.png",
                                          CC_CALLBACK_1(MainScene::menuFBCallback, this));
    
    fbItem->setPosition(Vec2(origin.x + visibleSize.width - fbItem->getContentSize().width / 2 - achiItem->getContentSize().width  - achiItem->getContentSize().width ,
                               origin.y + fbItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
	auto menu = Menu::create(achiItem, shopItem, fbItem, NULL);

    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add "MainScene" splash screen"
    auto sprite = Sprite::create("gem.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    //////////////////////////////
    // admob
    //auto listener = new MyAdsListener();
//    auto admob = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
//    TAdsDeveloperInfo devInfo;
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//    devInfo["AdmobID"] = "ca-app-pub-3897960758510166/9409157531";
//#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    devInfo["AdmobID"] = "ca-app-pub-3897960758510166/6316090337";
//#endif
//    admob->configDeveloperInfo(devInfo);
//    //admob->setAdsListener(listener);
//    //admob->setDebugMode(true);
//    TAdsInfo adInfo;
//    adInfo[ "AdmobType" ] = "1" ;
//    adInfo["AdmobSizeEnum"] = "1";
//
//    admob->showAds(adInfo, ProtocolAds::kPosTop);

    //////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////
    //Toggle ad when touch the screen
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID	
            AdmobHelper::showAd();
#endif


    //////////////////////////////////////////////////////////////////////////



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

void MainScene::menuFBCallback(Ref* pSender)
{
    if (plugin::FacebookAgent::getInstance()->isLoggedIn() == false){
    std::string permissions = "user_friends,publish_actions,user_about_me";
    plugin::FacebookAgent::getInstance()->login(permissions, [=](int ret, std::string& msg){
        CCLOG("%s", msg.c_str());
    });
    } else {
        
       // std::string path = "/me/invitable_friends";
       // plugin::FacebookAgent::FBInfo params;
       // plugin::FacebookAgent::getInstance()->api(path, //plugin::FacebookAgent::HttpMethod::Get, params,[=](int ret ,std::string& msg)
       //                                          {
       //                                              CCLOG("%s", msg.c_str());
       //                                          });
    
        plugin::FacebookAgent::FBInfo params;
        params.insert(std::make_pair("name", "My Game"));
        params.insert(std::make_pair("caption", "New Coocs2dx game"));
        params.insert(std::make_pair("description", "My Game! Built buy cocos2dx."));
        params.insert(std::make_pair("link", "http://www.cocos2d-x.org"));
        params.insert(std::make_pair("picture", "http://your.game.icon.link"));
        if (plugin::FacebookAgent::getInstance()->canPresentDialogWithParams(params))
        {
            plugin::FacebookAgent::getInstance()->dialog(params, [=](int ret ,std::string& msg)
                                                 {
                                                     CCLOG("%s", msg.c_str());
                                                 });
        }
        else
        {
            plugin::FacebookAgent::getInstance()->share(params, [=](int ret ,std::string& msg)
                                                {
                                                    CCLOG("%s", msg.c_str());
                                                });
        }
    }
}
