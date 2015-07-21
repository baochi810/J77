//
//  MyAdsListener.h
//  J77
//
//  Created by Ngo Chi on 7/21/15.
//
//

#ifndef __J77__MyAdsListener__
#define __J77__MyAdsListener__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

// plugin-x(AdMob)
#include "ProtocolAds.h"
using namespace cocos2d::plugin;

USING_NS_CC;
using namespace ui;

class MyAdsListener : public cocos2d::plugin::AdsListener
{
public:
    MyAdsListener(){};
    virtual void onAdsResult(cocos2d::plugin::AdsResultCode code, const char* msg);
    virtual void onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points);
};

class TitleScene : public Layer {
public:
    static Scene* createScene();
    CREATE_FUNC(TitleScene);
    virtual bool init();
    
private:
    // plugin-x(AdMob)
    
    ProtocolAds *admob;
    MyAdsListener *listener;
    TAdsInfo adInfo;
};

#endif /* defined(__J77__MyAdsListener__) */
