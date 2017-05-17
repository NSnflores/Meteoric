#include "MainMenu.h"
#include "PrincipalScene.h"
#include "GameOverScene.h"
#include "MainMenu.h"
#include "Servicios.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "PluginSdkboxPlay.h"
#include "PluginAdMob/PluginAdMob.h"
#include "PluginChartboost/PluginChartboost.h"
#endif

USING_NS_CC;

using namespace cocostudio::timeline;
ui::Button* boton;
Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
	Servicios::mostrarBarra();
    auto rootNode = CSLoader::createNode("GameOverScene.csb");
	addChild(rootNode);

	int puntuacion = Puntuador::getLastPuntuacion();
	int high = Puntuador::getHighPuntuacion();
	Meteoro::InstanciarEstrellas(rootNode);
	ui::Text* texto = rootNode->getChildByName<ui::Text*>("lblScore");
	char str[100] = { 0 };
	sprintf(str, "score: %d", puntuacion);
	texto->setString(str);

	if (puntuacion > high)
	{
		Puntuador::setHighPuntuacion();
		texto->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.35f, 1.3f), ScaleTo::create(0.35f, 1.f), NULL)));
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
		if (sdkbox::PluginSdkboxPlay::isSignedIn())
		{
			UserDefault::getInstance()->setBoolForKey("NeedsToPublish", false);
			sdkbox::PluginSdkboxPlay::submitScore("boardnormal", puntuacion);
		}
		else
		{
			UserDefault::getInstance()->setBoolForKey("NeedsToPublish", true);
		}
#endif

	}
	high = Puntuador::getHighPuntuacion();
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	if(high>=0)
		sdkbox::PluginSdkboxPlay::unlockAchievement("new");
	if (high >= 10)
		sdkbox::PluginSdkboxPlay::unlockAchievement("10");
	if (high >= 20)
		sdkbox::PluginSdkboxPlay::unlockAchievement("20");
	if (high >= 30)
		sdkbox::PluginSdkboxPlay::unlockAchievement("30");
	if (high >= 50)
		sdkbox::PluginSdkboxPlay::unlockAchievement("50");

#endif

	///////////////////////Boton replay
	boton = rootNode->getChildByName<ui::Button*>("btnAgain");
	boton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::stopAll();
			experimental::AudioEngine::play2d("audio/woo.ogg", false, 0.7f);
			//experimental::AudioEngine::play2d("audio/musica1.mp3", true);
			auto escena = Principal::createScene();
			boton->getParent()->runAction(FadeOut::create(0.2f));
			boton->getParent()->runAction(MoveBy::create(0.2f, Vec2(-700, 0)));
			Director::getInstance()->replaceScene(TransitionMoveInL::create(1,escena));
			break;
		}
	});

	//////////////////////Boton board
	auto btnBoard = rootNode->getChildByName<ui::Button*>("btnBoard");
	btnBoard->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::play2d("audio/click.ogg", false, 0.7f);
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS


			if (!sdkbox::PluginSdkboxPlay::isSignedIn())
				sdkbox::PluginSdkboxPlay::signin();
			if (UserDefault::getInstance()->getBoolForKey("NeedsToPublish", false))
			{
				if (sdkbox::PluginSdkboxPlay::isSignedIn())
				{
					UserDefault::getInstance()->setBoolForKey("NeedsToPublish", false);
					sdkbox::PluginSdkboxPlay::submitScore("boardnormal", Puntuador::getHighPuntuacion());
				}
			}
			sdkbox::PluginSdkboxPlay::showLeaderboard("boardnormal");
#endif
			break;
		}
	});

	///////////////////Boton home 
	auto btnHome = rootNode->getChildByName<ui::Button*>("btnHome");
	btnHome->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//if (RandomHelper::random_int(1, 2) == 2)
				Servicios::mostrarFull();


			auto escenaa = MainMenu::createScene();
			//boton->getParent()->runAction(FadeOut::create(0.2f));
			//boton->getParent()->runAction(MoveBy::create(0.2f, Vec2(-700, 0)));
			Director::getInstance()->replaceScene(TransitionFade::create(0.5f, escenaa));
			break;
		}
	});
	scheduleOnce(schedule_selector(GameOverScene::sched), 1.f);
	
	return true;
}
void GameOverScene::sched(float dt)
{
	if (RandomHelper::random_int(1, 3) == 3)
		Servicios::mostrarFull();
}