#pragma once
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "PluginAdMob/PluginAdMob.h"
#include "PluginSdkboxPlay.h"
#include "PluginIAP/PluginIAP.h"
#include "PluginChartboost/PluginChartboost.h"
#include "proj.android\jni\pluginadmob\PluginAdMob.h"
#include "proj.android\jni\pluginsdkboxplay\PluginSdkboxPlay.h"
#include "proj.android\jni\pluginiap\PluginIAP.h"
#include "proj.android\jni\PluginChartboost/PluginChartboost.h"
#endif

using namespace cocos2d;
//using namespace experimental;
class Servicios
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS 
    : public sdkbox::AdMobListener
#endif
{
public:
	Servicios();
	~Servicios();
	static void mostrarBarra();
	static void ocultarBarra();
	static void mostrarFull();
	
};

