#include "Servicios.h"

void Servicios::mostrarBarra()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	if (UserDefault::getInstance()->getBoolForKey("ads", true))
		sdkbox::PluginAdMob::show("banner1");
#endif
}
void Servicios::ocultarBarra()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		sdkbox::PluginAdMob::hide("banner1");
#endif
}
void Servicios::mostrarFull()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	if (UserDefault::getInstance()->getBoolForKey("ads", true))
		sdkbox::PluginChartboost::show("inters");
#endif
}

Servicios::Servicios()
{
}
Servicios::~Servicios()
{
}
