#include "Meteoro.h"
#include "AudioEngine.h"

//using namespace cocos2d::experimental;

void Meteoro::instanciarMeteoro(Node* rootNode, float velocidadMeteoro, int tipo)
{
	Sprite* meteoroSprite;
	switch (tipo)
	{
	case tipoGrande:
		if (RandomHelper::random_int(1,2)==1)
			meteoroSprite = Sprite::create("meteoros/meteor_big1.png");
		else
			meteoroSprite = Sprite::create("meteoros/meteor_big2.png");
		break;
	case tipoMediano:
		meteoroSprite = Sprite::create("meteoros/meteorBrown_med1.png");
		break;
	case tipoChico:
		meteoroSprite = Sprite::create("meteoros/meteorBrown_small1.png");
		break;
	default:
		return;
		break;
	}
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	int yPos = random(meteoroSprite->getContentSize().height/2 + 50, sizeScreen.height - meteoroSprite->getContentSize().height / 2 -50);
	meteoroSprite->setPosition(Vec2(sizeScreen.width + 150, yPos));
	meteoroSprite->setRotation(RandomHelper::random_int(0, 360));
	auto meteoroFisico = PhysicsBody::createCircle(meteoroSprite->getContentSize().height / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	rootNode->addChild(meteoroSprite);
	meteoroSprite->setPhysicsBody(meteoroFisico);
	meteoroFisico->setDynamic(true);
	meteoroFisico->setContactTestBitmask(true);
	auto mover = MoveTo::create(velocidadMeteoro, Vec2(-200, meteoroSprite->getPosition().y));
	meteoroFisico->setAngularVelocity(RandomHelper::random_int(-2, 2));
	auto secuencia = Sequence::create(mover, RemoveSelf::create(true), NULL);
	meteoroSprite->runAction(secuencia);
	meteoroSprite->setTag(Principal::tokenMeteoro + tipo);
	meteoroSprite->setLocalZOrder(-1);
	meteoroFisico->setVelocityLimit(0.f);
	
}
void Meteoro::instanciarEnergia(Node* rootNode, float velocidadMeteoro)
{
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	auto meteoroSprite = Sprite::create("powers/energia.png");
	int yPos = random(meteoroSprite->getContentSize().height / 2 + 50, sizeScreen.height - meteoroSprite->getContentSize().height / 2 - 50);
	meteoroSprite->setPosition(Vec2(sizeScreen.width + 150, yPos));
	auto meteoroFisico = PhysicsBody::createCircle(meteoroSprite->getContentSize().height / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	rootNode->addChild(meteoroSprite);
	meteoroSprite->setPhysicsBody(meteoroFisico);
	auto mover = MoveTo::create(velocidadMeteoro, Vec2(-200, meteoroSprite->getPosition().y));
	meteoroFisico->setContactTestBitmask(true);
	auto secuencia = Sequence::create(mover, RemoveSelf::create(true), NULL);
	meteoroSprite->runAction(secuencia);
	meteoroSprite->setTag(Principal::tokenEnergia);
}
void Meteoro::instanciarRandom(Node* rootNode, float velocidadMeteoro)
{
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	auto meteoroSprite = Sprite::create("powers/random.png");
	int yPos = random(meteoroSprite->getContentSize().height / 2 + 300, sizeScreen.height - meteoroSprite->getContentSize().height / 2 - 300);
	meteoroSprite->setPosition(Vec2(sizeScreen.width + 150, yPos));
	auto meteoroFisico = PhysicsBody::createCircle(meteoroSprite->getContentSize().height / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	rootNode->addChild(meteoroSprite);
	meteoroSprite->setPhysicsBody(meteoroFisico);
	auto mover = MoveTo::create(velocidadMeteoro*0.60f, Vec2(-200, meteoroSprite->getPosition().y));
	meteoroFisico->setContactTestBitmask(true);
	auto secuencia = Sequence::create(mover, RemoveSelf::create(true), NULL);
	meteoroSprite->runAction(secuencia);
	meteoroSprite->setTag(Principal::tokenRandom);
	
	//Arcoiris
	auto accion1 = TintTo::create(0.1f, Color3B(150, 250, 250));
	auto accion2 = TintTo::create(0.1f, Color3B(150, 250, 150));
	auto accion3 = TintTo::create(0.1f, Color3B(250, 250, 150));
	auto accion4 = TintTo::create(0.1f, Color3B(250, 250, 250));

	//oscilacion
	auto arri = EaseSineInOut::create(MoveBy::create(0.8f, Vec2(0, 200)));
	auto abaj = EaseSineInOut::create(MoveBy::create(0.8f, Vec2(0, -200)));
	Sequence* secuenciaOsci = Sequence::create(arri, abaj, NULL);
	RepeatForever* repeti = RepeatForever::create(secuenciaOsci);
	meteoroSprite->runAction(repeti);
	meteoroSprite->runAction(RepeatForever::create(Sequence::create(accion1, accion2, accion3,accion4, NULL)));
}
void Meteoro::instanciarMoneda(Node* rootNode, float velocidadMeteoro)
{
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	auto meteoroSprite = Sprite::create("powers/coin.png");
	int yPos = random(meteoroSprite->getContentSize().height / 2 + 50, sizeScreen.height - meteoroSprite->getContentSize().height / 2 - 50);
	meteoroSprite->setPosition(Vec2(sizeScreen.width + 150, yPos));
	auto meteoroFisico = PhysicsBody::createCircle(meteoroSprite->getContentSize().height / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	rootNode->addChild(meteoroSprite);
	meteoroSprite->setPhysicsBody(meteoroFisico);
	auto mover = MoveTo::create(velocidadMeteoro, Vec2(-200, meteoroSprite->getPosition().y));
	meteoroFisico->setContactTestBitmask(true);
	auto secuencia = Sequence::create(mover, RemoveSelf::create(true), NULL);
	meteoroSprite->runAction(secuencia);
	meteoroSprite->setTag(Principal::tokenMoneda);
}
void Meteoro::instanciarEnergiaBalas(Node* rootNode, float velocidadMeteoro)
{
	Size sizeScreen = Director::getInstance()->getVisibleSize();
	auto meteoroSprite = Sprite::create("powers/energiaBalas.png");
	int yPos = random(meteoroSprite->getContentSize().height / 2 + 50, sizeScreen.height - meteoroSprite->getContentSize().height / 2 - 50);
	meteoroSprite->setPosition(Vec2(sizeScreen.width + 150, yPos));
	auto meteoroFisico = PhysicsBody::createCircle(meteoroSprite->getContentSize().height / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	rootNode->addChild(meteoroSprite);
	meteoroSprite->setPhysicsBody(meteoroFisico);
	auto mover = MoveTo::create(velocidadMeteoro, Vec2(-200, meteoroSprite->getPosition().y));
	meteoroFisico->setContactTestBitmask(true);
	auto secuencia = Sequence::create(mover, RemoveSelf::create(true), NULL);
	meteoroSprite->runAction(secuencia);
	meteoroSprite->setTag(Principal::tokenEnergiaBalas);
}
void Meteoro::explotar(Sprite* meteo)
{
	meteo->setColor(Color3B::WHITE);
	Vector<SpriteFrame*> animFrames(9);
	char str[100] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		sprintf(str, "explosion/pixelExplosion0%d.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 96, 96)); //we assume that the sprites' dimentions are 96*96 rectangles.
		animFrames.pushBack(frame);
	}
	auto animacionExplocion = Animation::createWithSpriteFrames(animFrames, 0.07f);
	auto anima = Animate::create(animacionExplocion);
	meteo->runAction(anima);
	meteo->getPhysicsBody()->removeFromWorld();
		

	experimental::AudioEngine::play2d("explosion.ogg", false, 0.5);
}
void Meteoro::golpear(Sprite* meteo)
{
	meteo->setTag(meteo->getTag() - 1);
	Color3B color = meteo->getColor();
	meteo->setColor(Color3B(color.r, color.g - 127, color.b - 127));
	if (meteo->getTag() == Principal::tokenMeteoro)
		Meteoro::explotar(meteo);
	
	experimental::AudioEngine::play2d("audio/hit.ogg", false, 0.5);

}

Meteoro::Meteoro()
{
}
Meteoro::~Meteoro()
{
}
