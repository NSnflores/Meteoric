#include "MainMenu.h"
#include "LoadingScene.h"
#include "AudioEngine.h"
#include "Meteoro.h"

USING_NS_CC;

using namespace cocostudio::timeline;
Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    auto rootNode = CSLoader::createNode("LoadingScene.csb");
	addChild(rootNode);
	rootNode->setName("rootNode");

	Meteoro::InstanciarEstrellas(rootNode);


	sdkbox::PluginChartboost::cache("inters");
	sdkbox::PluginSdkboxPlay::signin();

	auto loadbar = rootNode->getChildByName<ui::LoadingBar*>("barra");
	schedule(schedule_selector(LoadingScene::insta), 0.05f);
	auto cache = TextureCache::getInstance();
	cache->addImage("meteoros/meteor_big1.png");
	cache->addImage("meteoros/meteor_big2.png");
	cache->addImage("powers/coin.png");
	cache->addImage("powers/energia.png");
	cache->addImage("powers/energiaBalas.png");
	cache->addImage("explosion/pixelExplosion00.png");
	cache->addImage("explosion/pixelExplosion01.png");
	cache->addImage("explosion/pixelExplosion02.png");
	cache->addImage("explosion/pixelExplosion03.png");
	cache->addImage("explosion/pixelExplosion04.png");
	cache->addImage("explosion/pixelExplosion05.png");
	cache->addImage("explosion/pixelExplosion06.png");
	cache->addImage("explosion/pixelExplosion07.png");
	cache->addImage("explosion/pixelExplosion08.png");
	experimental::AudioEngine::preload("audio/click.ogg");
	experimental::AudioEngine::preload("audio/hit.ogg");
	experimental::AudioEngine::preload("audio/laser.ogg");
	experimental::AudioEngine::preload("audio/moneda.ogg");
	experimental::AudioEngine::preload("audio/tomoLaser.ogg");
	experimental::AudioEngine::preload("audio/vida.ogg");
	experimental::AudioEngine::preload("audio/woo.ogg");
	experimental::AudioEngine::preload("audio/musica1.mp3");
	experimental::AudioEngine::preload("audio/musica2.mp3");
	experimental::AudioEngine::preload("explosion.ogg");
	experimental::AudioEngine::preload("explosionLarga.ogg");
	
#endif
    auto scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	//schedule(schedule_selector(LoadingScene::insta), 0);
	return true;
}
void LoadingScene::insta(float dt)
{
	auto rootNode = getChildByName("rootNode");
	auto barrita = rootNode->getChildByName<ui::LoadingBar*>("barra");
	barrita->setPercent(barrita->getPercent() + 1);
	if (barrita->getPercent() >= 100 && !initia)
	{
		initia = true;
		//auto scene = MainMenu::createScene();
		//Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
	}
}
