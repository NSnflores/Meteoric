#include "MainMenu.h"
#include "PrincipalScene.h"
#include "Meteoro.h"
#include "AudioEngine.h"
#include "Servicios.h"
#include "NaveSelect.h"

USING_NS_CC;

using namespace cocostudio::timeline;
ui::Button* btn;
Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();


	
    // add layer as a child to scene
    scene->addChild(layer);


	scene->getPhysicsWorld()->setGravity(Vec2(0.f, 0.f));
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
	sdkbox::IAP::setListener(this);
	sdkbox::IAP::restore();
#endif
	Servicios::mostrarBarra();

    auto rootNode = CSLoader::createNode("MainMenu.csb");
	
	addChild(rootNode);

	Meteoro::InstanciarEstrellas(rootNode);
	experimental::AudioEngine::stopAll();

	experimental::AudioEngine::play2d("audio/musica2.mp3", true, 0.5f);
	rootNode->setName("rootNode");
	rootNode->runAction(Sequence::create(FadeOut::create(0), FadeIn::create(2), NULL));
	if (!UserDefault::getInstance()->getBoolForKey("ads",true))
		getChildByName("rootNode")->getChildByName("btnAds")->runAction(RemoveSelf::create(true));

	btn = rootNode->getChildByName<ui::Button*>("btnPlay");
	btn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::stopAll();
			experimental::AudioEngine::play2d("audio/woo.ogg", false, 0.7f);
			auto escena = Principal::createScene();
			getChildByName("rootNode")->runAction(FadeOut::create(0.3f));
			getChildByName("rootNode")->runAction(MoveBy::create(0.5f, Vec2(-2000, 0)));
			Director::getInstance()->replaceScene(TransitionMoveInL::create(1,escena));
			break;
		}
	});
	btn->runAction(RepeatForever::create(
		Sequence::create(RotateTo::create(0.6f,5.f), RotateTo::create(0.6f, -5.f),
			NULL)
	));


	////////////////////////BOTON BOARD
	auto btnBoard = rootNode->getChildByName<ui::Button*>("btnBoard");
	btnBoard->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::play2d("audio/click.ogg",false,0.7f);

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

	////////////////////BOTON ACHIEVMENTS
	auto btnAchiev = rootNode->getChildByName<ui::Button*>("btnAchiev");
	btnAchiev->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::play2d("audio/click.ogg", false, 0.7f);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			if (!sdkbox::PluginSdkboxPlay::isSignedIn())
				sdkbox::PluginSdkboxPlay::signin();
			
			sdkbox::PluginSdkboxPlay::showAchievements();
#endif
			break;
		}
	});


	//////////////////BOTON ADS
	auto btnAds = rootNode->getChildByName<ui::Button*>("btnAds");
	btnAds->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::play2d("audio/click.ogg", false, 0.4f);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
			sdkbox::IAP::purchase("noads");
#endif
			break;
		}
	});

	//////////////BOTON NAVE
	auto btnNave = rootNode->getChildByName<ui::Button*>("btnNave");
	btnNave->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			experimental::AudioEngine::play2d("audio/click.ogg", false, 0.4f);
			

			experimental::AudioEngine::play2d("audio/woo.ogg", false, 0.2f);
			auto escena = NaveSelect::createScene();
			//getChildByName("rootNode")->runAction(FadeOut::create(0.3f));
			getChildByName("rootNode")->runAction(MoveBy::create(0.5f, Vec2(-2000, 0)));
			Director::getInstance()->replaceScene(TransitionFade::create(1, escena));
			break;
		}
	});

	//////////////BOTON MUSICA
	/*auto btnMusic = rootNode->getChildByName<ui::Button*>("btnMusic");
	btnMusic->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			
			break;
		}
	});
*/
	char monedas[100] = { 0 };
	sprintf(monedas, "%i", Puntuador::getTotalCoins());
	rootNode->getChildByName("monedas")->getChildByName<ui::TextField*>("coins")->setString(monedas);
	schedule(schedule_selector(MainMenu::insta), 0.2f);
	return true;
}

void MainMenu::insta(float dt)
{
	
	Meteoro::instanciarMeteoro(getChildByName("rootNode"),3.f,random(1,3));
}