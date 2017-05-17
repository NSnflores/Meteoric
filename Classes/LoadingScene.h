#ifndef __LoadingScene_SCENE_H__
#define __LoadingScene_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "PluginAdMob/PluginAdMob.h"
#include "PluginChartboost/PluginChartboost.h"
#endif

class LoadingScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	bool initia = false;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void insta(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
};

#endif 
