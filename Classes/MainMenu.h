#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Servicios.h"
#if SDKBOX_ENABLED
#include "PluginAdMob/PluginAdMob.h"
#include "PluginSdkboxPlay.h"
#include "PluginIAP/PluginIAP.h"
#endif

class MainMenu : public cocos2d::Layer
#if SDKBOX_ENABLED 
	, public sdkbox::IAPListener
#endif
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void sched(float dt);
	void insta(float dt);


	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);


private:
#if SDKBOX_ENABLE
	virtual void onInitialized(bool ok) override;
	virtual void onSuccess(sdkbox::Product const& p) override;
	virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
	virtual void onCanceled(sdkbox::Product const& p) override;
	virtual void onRestored(sdkbox::Product const& p) override;
	virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
	virtual void onProductRequestFailure(const std::string &msg) override;
	void onRestoreComplete(bool ok, const std::string &msg);

	//ADMOB

#endif 
public:

	void onInitialized(bool ok) {}
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	void onFailure(sdkbox::Product const& p, const std::string &msg) {}
	void onCanceled(sdkbox::Product const& p) {}
	void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) {}
	void onProductRequestFailure(const std::string &msg) {}
	void onRestoreComplete(bool ok, const std::string &msg) {}

	void onRestored(sdkbox::Product const& p) 
	{
		if (p.name == "noads")
		{
			UserDefault::getInstance()->setBoolForKey("ads", false);
			Servicios::ocultarBarra();
			//getChildByName("rootNode")->getChildByName("btnAds")->runAction(RemoveSelf::create(true));
		}
	}
	void onSuccess(sdkbox::Product const& p)
	{
		if (p.name == "noads")
		{
			UserDefault::getInstance()->setBoolForKey("ads", false);
			Servicios::ocultarBarra();
			getChildByName("rootNode")->getChildByName("btnAds")->runAction(RemoveSelf::create(true));
		}
	}
#endif
};


#endif
